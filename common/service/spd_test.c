#include <shell/shell.h>
#include <stdlib.h>
#include <string.h>
#include "hal_i2c.h"
#include <stdio.h>
#include <string.h>  
#include "./../meta-facebook/yv4-sd/src/platform/plat_i2c.h"
#include "./../meta-facebook/yv4-sd/src/platform/plat_dimm.h"


#define SPD_DEFAULT_LEN 640
// #define SPD_MAX_LEN     640
#define I2C_RETRY       3
#define PART_NUM_OFFSET 0x209
#define PART_NUM_LEN    32
typedef struct _dimm_mfg {
	uint16_t id;
	const char *name;
} dimm_mfg;

static dimm_mfg dimm_manufacturer[] = {
	{ 0x8980, "Intel" },    { 0x1080, "NEC" },      { 0xb380, "IDT" },
	{ 0x9780, "TI" },       { 0xad80, "SK Hynix" }, { 0x2c80, "Micron" },
	{ 0xc180, "Infineon" }, { 0xce80, "Samsung" },  { 0x3d80, "Tek" },
	{ 0x9801, "Kingston" }, { 0x9401, "Smart" },    { 0xfe02, "Elpida" },
	{ 0xc802, "Agilent" },  { 0x9e02, "Corsair" },  { 0x0b83, "Nanya" },
	{ 0x9483, "Mushkin" },  { 0xb304, "Inphi" },    { 0xcb04, "ADATA" },
	{ 0x2304, "Renesas" },  { 0x5185, "Qimonda" },  { 0xba85, "Virtium" },
	{ 0x3286, "Montage" },  { 0xd086, "Silego" },   { 0x9d86, "Rambus" },
	{ 0x2a0b, "MPS" },      { 0x8c8a, "Richtek" },
};

///////////////////////////////////////////
// ===== helpers for DDR5 size/speed decoding =====

#define CHANNEL_NUM(x) ((x) + 1)
#ifndef PKG_RANK
// placeholder; 用你原本 implementation 的 PKG_RANK 替代。 
#define PKG_RANK(x) (x)
#endif

static const uint16_t die_capacity_mb[] = {
    256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 12288, 24576,
};
static const uint16_t bus_width_bits[] = { 8, 16, 32, 64 };
static const uint16_t device_width[] = { 4, 8, 16, 32 };
static const uint16_t sdram_size_gb[] = {
    0, 4, 8, 12, 16, 24, 32, 48, 64,
};
static const uint16_t logical_rank[] = { 1, 1, 2, 4, 8, 16 };

static void rstrip(char *s)
{
    size_t len = strlen(s);
    while (len > 0 && (s[len-1] == ' ' || s[len-1] == '\t')) {
        s[len-1] = '\0';
        len--;
    }
}

static __attribute__((unused)) int get_die_capacity(uint8_t data) {
    if (data >= ARRAY_SIZE(die_capacity_mb) || die_capacity_mb[data] == 0)
        return -1;
    return die_capacity_mb[data];
}
static int get_bus_width_bits(uint8_t data) {
    if (data >= ARRAY_SIZE(bus_width_bits) || bus_width_bits[data] == 0)
        return -1;
    return bus_width_bits[data];
}
static int get_device_width_bits(uint8_t data) {
    if (data >= ARRAY_SIZE(device_width) || device_width[data] == 0)
        return -1;
    return device_width[data];
}
static int get_sdram_size_gb(uint8_t data) {
    if (data >= ARRAY_SIZE(sdram_size_gb) || data == 0)
        return -1;
    return sdram_size_gb[data];
}
static int get_logical_rank(uint8_t data) {
    if (data >= ARRAY_SIZE(logical_rank))
        return -1;
    return logical_rank[data];
}

typedef struct {
    uint16_t max_cycle;
    uint16_t speed;
} spd5_speed_entry;

/* smaller cycle -> faster. thresholds in ascending order so min_cycle <= max_cycle picks speed */
static const spd5_speed_entry spd5_dimm_speed[] = {
    { 0x0ee, 8400 },
    { 0x0fa, 8000 },
    { 0x107, 7600 },
    { 0x115, 7200 },
    { 0x126, 6800 },
    { 0x138, 6400 },
    { 0x14d, 6000 },
    { 0x165, 5600 },
    { 0x180, 5200 },
    { 0x1a0, 4800 },
    { 0x1c6, 4400 },
    { 0x1f4, 4000 },
    { 0x22b, 3600 },
    { 0x271, 3200 },
};

// raw DDR5 SPD read with JEDEC two-byte offset encoding
static int spd5_read(uint8_t i2c_addr, uint16_t offset, uint8_t *buf, size_t len)
{
    while (len) {
        size_t chunk = (len > 16) ? 16 : len;
        I2C_MSG msg = {0};
        msg.bus = I2C_BUS13;
        msg.target_addr = i2c_addr;
        msg.tx_len = 2;
        msg.rx_len = chunk;

        uint16_t enc = ((offset & 0x780) << 1) | (0x80 | (offset & 0x7F));
        msg.data[0] = enc & 0xFF;
        msg.data[1] = enc >> 8;

        if (i2c_master_read(&msg, I2C_RETRY) != 0)
            return -1;

        memcpy(buf, msg.data, chunk);
        offset += chunk;
        buf += chunk;
        len -= chunk;
    }
    return 0;
}

static int decode_ddr5_size(uint8_t i2c_addr, char *size_str, size_t size_str_len)
{
    uint8_t buf1[3] = {0};
    uint8_t buf2[2] = {0};

    if (spd5_read(i2c_addr, 0x4, buf1, sizeof(buf1)) != 0)
        return -1;
    if (spd5_read(i2c_addr, 0xEA, buf2, sizeof(buf2)) != 0)
        return -1;

    uint8_t size_gb_raw   = buf1[0] & 0xF;           // byte4[3:0]
    uint8_t log_rank_raw  = (buf1[0] >> 5) & 0x7;    // byte4[7:5]
    uint8_t dev_width_raw = (buf1[2] >> 5) & 0x7;    // byte6[7:5]

    uint8_t pack_rank_raw = (buf2[0] >> 3) & 0x7;    // byte234[5:3]
    uint8_t bus_width_raw = buf2[1] & 0x7;          // byte235[2:0]
    uint8_t ch_num_raw    = (buf2[1] >> 5) & 0x3;    // byte235[6:5]

    int size_gb   = get_sdram_size_gb(size_gb_raw);
    int bus_width = get_bus_width_bits(bus_width_raw);
    int dev_width = get_device_width_bits(dev_width_raw);
    int logical   = get_logical_rank(log_rank_raw);
    int pkg_rank  = PKG_RANK(pack_rank_raw);
    int ranks     = (logical > 0 && pkg_rank > 0) ? (logical * pkg_rank) : -1;
    int channels  = CHANNEL_NUM(ch_num_raw);

    if (size_gb < 0 || bus_width < 0 || dev_width < 0 || ranks <= 0 || channels <= 0)
        return -1;

    uint64_t dimm_size_mb = (uint64_t)size_gb * 1024ULL /* GB->MB */ *
                            (uint64_t)ranks *
                            (uint64_t)channels *
                            (uint64_t)bus_width /
                            (8ULL * (uint64_t)dev_width);

    if (dimm_size_mb > UINT32_MAX)
        dimm_size_mb = UINT32_MAX;

    snprintf(size_str, size_str_len, "%llu MB", (unsigned long long)dimm_size_mb);
    return 0;
}

static int decode_ddr5_speed(uint8_t i2c_addr, char *speed_str, size_t speed_str_len)
{
    uint8_t buf[2] = {0};
    if (spd5_read(i2c_addr, 0x14, buf, 2) != 0)
        return -1;
    uint16_t min_cycle = (buf[1] << 8) | buf[0];

    for (size_t i = 0; i < ARRAY_SIZE(spd5_dimm_speed); i++) {
        if (min_cycle <= spd5_dimm_speed[i].max_cycle) {
            snprintf(speed_str, speed_str_len, "%u MT/s", spd5_dimm_speed[i].speed);
            return 0;
        }
    }
    snprintf(speed_str, speed_str_len, "Unknown");
    return -1;
}

const char *mfg_string(uint16_t id)
{
	for (size_t i = 0; i < sizeof(dimm_manufacturer) / sizeof(dimm_manufacturer[0]); i++) {
		if (dimm_manufacturer[i].id == id) {
			return dimm_manufacturer[i].name;
		}
	}
	return "Unknown";
}
static int cmd_spd_read(const struct shell *shell, size_t argc, char **argv)
{
	if (argc != 2) {
		shell_print(shell, "Usage: spd_read <i2c_addr>");
		return -1;
	}

	char *endptr;
	uint8_t i2c_addr = (uint8_t)strtol(argv[1], &endptr, 0);
	if (*endptr != '\0') {
		shell_error(shell, "Invalid I2C address: %s", argv[1]);
		return -1;
	}

	I2C_MSG mr11_msg = { 0 };
	mr11_msg.bus = I2C_BUS13;
	mr11_msg.target_addr = i2c_addr;
	mr11_msg.tx_len = 2;
	mr11_msg.rx_len = 0;
	mr11_msg.data[0] = 0x0B;   // Offset 0x0B
	mr11_msg.data[1] = 0x08;   // Set MR11[3] = 1b

	if (i2c_master_write(&mr11_msg, I2C_RETRY) != 0) {
		shell_warn(shell, "Warning: failed to enable 2-byte offset mode via MR11 (0x0B)");
	} else {
		shell_print(shell, "Enabled 2-byte offset mode (MR11[3]=1)");
	}

	static uint8_t spd_buf[0x27] = {0}; // exactly 0x200~0x226 = 0x27 bytes
	uint16_t offset = 0x200;
	uint8_t length = 0x27;

	I2C_MSG msg = { 0 };
	msg.bus = I2C_BUS13;
	msg.target_addr = i2c_addr;
	msg.rx_len = length;

	// JEDEC encoded offset for DDR5
	uint16_t enc = ((offset & 0x780) << 1) | (0x80 | (offset & 0x7F));
	msg.tx_len = 2;
	msg.data[0] = enc & 0xFF;
	msg.data[1] = enc >> 8;

	if (i2c_master_read(&msg, I2C_RETRY) != 0) {
		shell_error(shell, "SPD read failed at offset 0x%03X", offset);
		return -1;
	}

	memcpy(spd_buf, msg.data, length);

	// Print hex dump
	shell_print(shell, "SPD Data from 0x%02X (0x200~0x226):", i2c_addr);
	for (int i = 0; i < length; i++) {
		if (i % 16 == 0)
			shell_fprintf(shell, SHELL_NORMAL, "\n%03X: ", offset + i);
		shell_fprintf(shell, SHELL_NORMAL, "%02X ", spd_buf[i]);
	}

	// Print vendor info
	shell_print(shell, "\nSPD Vendor Info:");
	uint16_t mfg_id = (spd_buf[0x01] << 8) | spd_buf[0x00];
	shell_fprintf(shell, SHELL_NORMAL, "\nMFG ID    : %02X %02X (%s)", spd_buf[0x00], spd_buf[0x01], mfg_string(mfg_id));
	shell_fprintf(shell, SHELL_NORMAL, "\nDate Code : %02X %02X", spd_buf[0x03], spd_buf[0x04]);
	shell_fprintf(shell, SHELL_NORMAL, "\nSerial Num: %02X%02X%02X%02X%02X%02X%02X%02X%02X",
				     spd_buf[0x00],spd_buf[0x01],spd_buf[0x02], spd_buf[0x03],
				     spd_buf[0x04],spd_buf[0x05], spd_buf[0x06], spd_buf[0x07], spd_buf[0x08]);

	shell_fprintf(shell, SHELL_NORMAL, "\nPart Num  : ");

	for (int i = 9; i < length; i++) { // 0x209開始 (0x200偏移9 bytes)
		char c = spd_buf[i];
		if (c >= 32 && c <= 126) {
			shell_fprintf(shell, SHELL_NORMAL, "%c", c);
		}
	}
	shell_fprintf(shell, SHELL_NORMAL, "\n");
	shell_print(shell, "");

	return 0;
}

static int cmd_spd_manuf(const struct shell *shell, size_t argc, char **argv)
{
	if (argc != 2) {
		shell_print(shell, "Usage: spd_manuf <dimm_id(0~11)>");
		return -1;
	}

	char *endptr;
	uint8_t dimm_id = (uint8_t)strtol(argv[1], &endptr, 0);
	if (*endptr != '\0' || dimm_id >= DIMM_ID_MAX) {
		shell_error(shell, "Invalid DIMM ID: %s", argv[1]);
		return -1;
	}

	uint8_t spd_data[SPD_MANUF_INFO_LEN];

	if (pal_get_spd_manuf_info(dimm_id, spd_data) != 0) {
		shell_error(shell, "SPD manufacturer data not available for DIMM %d", dimm_id);
		return -1;
	}

	// Print hex dump
	shell_print(shell, "SPD Manufacturer Data DIMM %d (0x200~0x226):", dimm_id);
	for (int i = 0; i < SPD_MANUF_INFO_LEN; i++) {
		if (i % 16 == 0)
			shell_fprintf(shell, SHELL_NORMAL, "\n%03X: ", 0x200 + i);
		shell_fprintf(shell, SHELL_NORMAL, "%02X ", spd_data[i]);
	}

	// 解析資訊
	uint16_t mfg_id = (spd_data[1] << 8) | spd_data[0];
	shell_fprintf(shell, SHELL_NORMAL, "\n\nMFG ID    : %02X %02X (%s)", spd_data[0], spd_data[1], mfg_string(mfg_id));
	shell_fprintf(shell, SHELL_NORMAL, "\nDate Code : %02X %02X", spd_data[3], spd_data[4]);
	shell_fprintf(shell, SHELL_NORMAL, "\nSerial Num: ");
	for (int i = 0; i < 9; i++)
		shell_fprintf(shell, SHELL_NORMAL, "%02X", spd_data[i]);

	shell_fprintf(shell, SHELL_NORMAL, "\nPart Num  : ");
	for (int i = 9; i < SPD_MANUF_INFO_LEN; i++) {
		char c = spd_data[i];
		if (c >= 32 && c <= 126) {
			shell_fprintf(shell, SHELL_NORMAL, "%c", c);
		}
	}
	shell_fprintf(shell, SHELL_NORMAL, "\n");

	return 0;
}

static int cmd_spd_dump(const struct shell *shell, size_t argc, char **argv)
{
    if (argc != 2) {
        shell_print(shell, "Usage: spd_dump <i2c_addr>");
        return -1;
    }

    char *endptr;
    uint8_t i2c_addr = (uint8_t)strtol(argv[1], &endptr, 0);
    if (*endptr != '\0') {
        shell_error(shell, "Invalid I2C address: %s", argv[1]);
        return -1;
    }

    // Optional: enable MR11[3] = 1b for DDR5 SPD 2-byte offset
    I2C_MSG mr11_msg = { 0 };
    mr11_msg.bus = I2C_BUS13;
    mr11_msg.target_addr = i2c_addr;
    mr11_msg.tx_len = 2;
    mr11_msg.rx_len = 0;
    mr11_msg.data[0] = 0x0B;
    mr11_msg.data[1] = 0x08;

    if (i2c_master_write(&mr11_msg, I2C_RETRY) != 0) {
        shell_warn(shell, "Warning: failed to enable 2-byte offset mode via MR11");
    } else {
        shell_print(shell, "Enabled 2-byte offset mode (MR11[3]=1)");
        k_msleep(2); // [ADDED] 等 MR11 設定穩定
    }

    // Dump from 0x000 ~ 0x27F
    const uint16_t start = 0x000;
    const uint16_t end = 0x280;
    uint8_t buf[16];
    static uint8_t spd0[256]; // [MODIFIED] 改為 static 避免 stack overflow，保留前 0x100 bytes
    memset(spd0, 0, sizeof(spd0));

    shell_print(shell, "Full SPD Dump from 0x%02X (0x000~0x27F):", i2c_addr);

    for (uint16_t offset = start; offset < end; offset += 16) {
        I2C_MSG msg = { 0 };
        msg.bus = I2C_BUS13;
        msg.target_addr = i2c_addr;
        msg.tx_len = 2;
        msg.rx_len = 16;

        // JEDEC DDR5 offset encoding
        uint16_t enc = ((offset & 0x780) << 1) | (0x80 | (offset & 0x7F));
        msg.data[0] = enc & 0xFF;
        msg.data[1] = enc >> 8;

        if (i2c_master_read(&msg, I2C_RETRY) != 0) {
            shell_error(shell, "Read failed at offset 0x%03X", offset);
            continue;
        }

        memcpy(buf, msg.data, 16);
        if (offset < 0x100) {
            memcpy(&spd0[offset], buf, 16);
        }

        shell_fprintf(shell, SHELL_NORMAL, "%03X: ", offset);
        for (int i = 0; i < 16; i++) {
            shell_fprintf(shell, SHELL_NORMAL, "%02X ", buf[i]);
        }
        shell_fprintf(shell, SHELL_NORMAL, "\n");
    }

    // ----- summary decode (DDR5) -----
	static char size_str[64] = {0};
	static char speed_str[64] = {0};
	static char mfg_str[64] = {0};
	static char mfg_date[64] = {0};
	static char sn[64] = {0};
	static char pn[64] = {0};

	// clear leftovers to avoid residue across invocations
	pn[0] = '\0';
	sn[0] = '\0';
	mfg_str[0] = '\0';
	mfg_date[0] = '\0';

	// Size & Speed
	if (decode_ddr5_size(i2c_addr, size_str, sizeof(size_str)) != 0)
		snprintf(size_str, sizeof(size_str), "Unknown");
	if (decode_ddr5_speed(i2c_addr, speed_str, sizeof(speed_str)) != 0)
		snprintf(speed_str, sizeof(speed_str), "Unknown");

	// Manufacturer / serial / part number / date: 讀 SPD5 manufacturer block 0x200
	uint8_t manuf_blk[0x27] = {0};
	if (spd5_read(i2c_addr, 0x200, manuf_blk, sizeof(manuf_blk)) == 0) {
		uint16_t dimm_mfg_id = (manuf_blk[1] << 8) | manuf_blk[0];
		snprintf(mfg_str, sizeof(mfg_str), "%s", mfg_string(dimm_mfg_id));
		snprintf(mfg_date, sizeof(mfg_date), "20%02x Week%02x", manuf_blk[3], manuf_blk[4]);

		// Serial
		int pos = 0;
		for (int i = 0; i < 9; i++) {
			pos += snprintf(sn + pos, sizeof(sn) - pos, "%02X", manuf_blk[i]);
		}

		// Part number (safe append + null terminate)
		pn[0] = '\0';
		for (int i = 9; i < (int)sizeof(manuf_blk); i++) {
			char c = manuf_blk[i];
			if (c >= 32 && c <= 126) {
				size_t cur = strlen(pn);
				if (cur + 1 < sizeof(pn)) {
					pn[cur] = c;
					pn[cur+1] = '\0';
				}
			}
		}
		rstrip(pn);
	} else {
		snprintf(mfg_str, sizeof(mfg_str), "Unknown");
		snprintf(mfg_date, sizeof(mfg_date), "Unknown");
		snprintf(sn, sizeof(sn), "Unknown");
		snprintf(pn, sizeof(pn), "Unknown");
	}

    
    

    // Register Vendor & PMIC Vendor
    uint8_t reg_buf[2] = {0};
    uint8_t pmic_buf[2] = {0};
    uint16_t reg_id = 0, pmic_id = 0;
    char reg_vendor_display[64] = {0};
    char pmic_vendor_display[64] = {0};

    if (spd5_read(i2c_addr, 0xF0, reg_buf, 2) == 0) {
        reg_id = (reg_buf[1] << 8) | reg_buf[0];
        shell_print(shell, "Raw Register Vendor bytes: %02X %02X -> 0x%04X", reg_buf[0], reg_buf[1], reg_id);
        snprintf(reg_vendor_display, sizeof(reg_vendor_display), "%s (raw 0x%04X)", mfg_string(reg_id), reg_id);
    } else {
        snprintf(reg_vendor_display, sizeof(reg_vendor_display), "Unknown");
        shell_error(shell, "Failed to read register vendor");
    }

    if (spd5_read(i2c_addr, 0xC6, pmic_buf, 2) == 0) {
        pmic_id = (pmic_buf[1] << 8) | pmic_buf[0];
        shell_print(shell, "Raw PMIC Vendor bytes: %02X %02X -> 0x%04X", pmic_buf[0], pmic_buf[1], pmic_id);
        snprintf(pmic_vendor_display, sizeof(pmic_vendor_display), "%s (raw 0x%04X)", mfg_string(pmic_id), pmic_id);
    } else {
        snprintf(pmic_vendor_display, sizeof(pmic_vendor_display), "Unknown");
        shell_error(shell, "Failed to read PMIC vendor");
    }

    // Output summary like screenshot
    shell_print(shell, ""); // spacer
    shell_print(shell, "Type: DDR5 SDRAM");
    shell_print(shell, "Size: %s", size_str);
    shell_print(shell, "Speed: %s", speed_str);
    shell_print(shell, "Manufacturer: %s", mfg_str);
    shell_print(shell, "Manufacturing Date: %s", mfg_date);
    shell_print(shell, "Part Number: %s", pn);
    shell_print(shell, "Serial Number: %s", sn);
    shell_print(shell, "Register Vendor: %s", reg_vendor_display);
    shell_print(shell, "PMIC Vendor: %s", pmic_vendor_display);

    return 0;
}




// ===== new command: spd_config =====

// static int cmd_spd_config(const struct shell *shell, size_t argc, char **argv)
// {
//     if (argc != 2) {
//         shell_print(shell, "Usage: spd_config <i2c_addr>");
//         return -1;
//     }

//     char *endptr;
//     uint8_t i2c_addr = (uint8_t)strtol(argv[1], &endptr, 0);
//     if (*endptr != '\0') {
//         shell_error(shell, "Invalid I2C address: %s", argv[1]);
//         return -1;
//     }

//     // Enable DDR5 two-byte offset mode
//     I2C_MSG mr11_msg = {0};
//     mr11_msg.bus = I2C_BUS13;
//     mr11_msg.target_addr = i2c_addr;
//     mr11_msg.tx_len = 2;
//     mr11_msg.rx_len = 0;
//     mr11_msg.data[0] = 0x0B;
//     mr11_msg.data[1] = 0x08;
//     if (i2c_master_write(&mr11_msg, I2C_RETRY) != 0) {
//         shell_warn(shell, "Warning: failed to enable 2-byte offset mode via MR11");
//     }

//     // Read manufacturer block (DDR5) at 0x200
//     uint8_t manuf_blk[0x27] = {0};
//     if (spd5_read(i2c_addr, 0x200, manuf_blk, sizeof(manuf_blk)) != 0) {
//         shell_error(shell, "Failed to read SPD5 manufacturer block");
//         return -1;
//     }

//     // Parse fields
//     uint16_t mfg_id = (manuf_blk[1] << 8) | manuf_blk[0];
//     char mfg_name[64];
//     snprintf(mfg_name, sizeof(mfg_name), "%s", mfg_string(mfg_id));

//     // Manufacturing date: [3],[4] (example: year = 2000 + byte3, week = byte4)
//     char mfg_date[64];
//     snprintf(mfg_date, sizeof(mfg_date), "20%02x Week%02x", manuf_blk[3], manuf_blk[4]);

//     // Serial number: bytes 0..8 as hex
//     char sn[64] = {0};
//     {
//         int pos = 0;
//         for (int i = 0; i < 9; i++) {
//             pos += snprintf(sn + pos, sizeof(sn) - pos, "%02X", manuf_blk[i]);
//         }
//     }

//     // Part number: starts at offset 0x209 relative to SPD5 base (i.e., manuf_blk[9..])
//     char pn[64] = {0};
//     for (int i = 9; i < (int)sizeof(manuf_blk); i++) {
//         char c = manuf_blk[i];
//         if (c >= 32 && c <= 126) {
//             size_t cur = strlen(pn);
//             if (cur + 1 < sizeof(pn))
//                 pn[cur] = c;
//         }
//     }

//     // Size & Speed decode
//     char size_str[64] = {0};
//     char speed_str[64] = {0};
//     if (decode_ddr5_size(i2c_addr, size_str, sizeof(size_str)) != 0)
//         snprintf(size_str, sizeof(size_str), "Unknown");
//     if (decode_ddr5_speed(i2c_addr, speed_str, sizeof(speed_str)) != 0)
//         snprintf(speed_str, sizeof(speed_str), "Unknown");

//     // Output like screenshot
//     shell_print(shell, "Type: DDR5 SDRAM");
//     shell_print(shell, "Size: %s", size_str);
//     shell_print(shell, "Speed: %s", speed_str);
//     shell_print(shell, "Manufacturer: %s", mfg_name);
//     shell_print(shell, "Manufacturing Date: %s", mfg_date);
//     shell_print(shell, "Part Number: %s", pn);
//     shell_print(shell, "Serial Number: %s", sn);
//     shell_print(shell, "Register Vendor: Unknown");
//     shell_print(shell, "PMIC Vendor: Unknown");

//     return 0;
// }
// SHELL_CMD_REGISTER(spd_config, NULL,
//     "Show decoded DDR5 SPD config (like dimm-util --config): spd_config <i2c_addr>",
//     cmd_spd_config);


SHELL_CMD_REGISTER(spd_dump, NULL, "Dump full SPD data (DDR4/DDR5) via I2C address. Usage: spd_dump <i2c_addr>", cmd_spd_dump);
SHELL_CMD_REGISTER(spd_read, NULL, "Read DIMM SPD (DDR4/DDR5) via offset. Usage: spd_read <i2c_addr> [length]", cmd_spd_read);
SHELL_CMD_REGISTER(spd_manuf, NULL, "Read cached SPD manuf info: spd_manuf <dimm_id>", cmd_spd_manuf);