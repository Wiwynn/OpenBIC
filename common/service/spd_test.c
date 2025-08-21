#include <shell/shell.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../meta-facebook/yv4-sd/src/platform/plat_dimm.h"

/* ---------- Helpers ---------- */

#ifndef ARRAY_LEN
#define ARRAY_LEN(a) ((int)(sizeof(a)/sizeof((a)[0])))
#endif

#define CHANNEL_NUM(x) ((x) + 1)
#ifndef PKG_RANK
#define PKG_RANK(x) (x)
#endif

/* ---------- Manufacturer table & lookup ---------- */
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

static const char *mfg_string(uint16_t id)
{
    for (int i = 0; i < ARRAY_LEN(dimm_manufacturer); i++) {
        if (dimm_manufacturer[i].id == id)
            return dimm_manufacturer[i].name;
    }
    return "Unknown";
}

/* Utility to trim trailing whitespace */
static void rstrip(char *s)
{
    size_t len = strlen(s);
    while (len > 0 && (s[len-1] == ' ' || s[len-1] == '\t'))
        s[--len] = '\0';
}

static uint8_t bcd_to_u8(uint8_t v)
{
    return (uint8_t)(((v >> 4) & 0xF) * 10 + (v & 0xF));
}

/* ---------- Decode helpers (DDR5, COMPACT CACHE) ---------- */
/* Tables per compact interpretation */
static const uint16_t bus_width_bits[] = { 8, 16, 32, 64 };
static const uint16_t device_width[]   = { 4, 8, 16, 32 };
static const uint16_t sdram_size_gb[]  = { 0, 4, 8, 12, 16, 24, 32, 48, 64 };
static const uint16_t logical_rank[]   = { 1, 1, 2, 4, 8, 16 };

static int get_bus_width_bits(uint8_t v) {
    if (v >= ARRAY_LEN(bus_width_bits)) return -1;
    return bus_width_bits[v];
}
static int get_device_width_bits(uint8_t v) {
    if (v >= ARRAY_LEN(device_width)) return -1;
    return device_width[v];
}
static int get_sdram_size_gb(uint8_t v) {
    if (v >= ARRAY_LEN(sdram_size_gb) || v == 0) return -1;
    return sdram_size_gb[v];
}
static int get_logical_rank(uint8_t v) {
    if (v >= ARRAY_LEN(logical_rank)) return -1;
    return logical_rank[v];
}

/* SPD5 tCKmin -> speed map */
typedef struct { uint16_t max_cycle; uint16_t speed; } spd5_speed_entry;
static const spd5_speed_entry spd5_dimm_speed[] = {
    { 0x0ee, 8400 }, { 0x0fa, 8000 }, { 0x107, 7600 }, { 0x115, 7200 },
    { 0x126, 6800 }, { 0x138, 6400 }, { 0x14d, 6000 }, { 0x165, 5600 },
    { 0x180, 5200 }, { 0x1a0, 4800 }, { 0x1c6, 4400 }, { 0x1f4, 4000 },
    { 0x22b, 3600 }, { 0x271, 3200 },
};

static int decode_ddr5_size_from_compact(const uint8_t *spd, char *out, size_t out_len)
{
    if (!spd) return -1;

    /* Use compact cache indices from plat_dimm.h */
    uint8_t b4  = spd[SPD_SZ_B4];
    uint8_t b6  = spd[SPD_SZ_B6];
    uint8_t bea = spd[SPD_SZ_BEA];
    uint8_t beb = spd[SPD_SZ_BEB];

    uint8_t size_gb_raw   =  b4 & 0xF;          /* byte4[3:0]   */
    uint8_t log_rank_raw  = (b4 >> 5) & 0x7;    /* byte4[7:5]   */
    uint8_t dev_width_raw = (b6 >> 5) & 0x7;    /* byte6[7:5]   */
    uint8_t pack_rank_raw = (bea >> 3) & 0x7;   /* byte234[5:3] */
    uint8_t bus_width_raw =  beb & 0x7;         /* byte235[2:0] */
    uint8_t ch_num_raw    = (beb >> 5) & 0x3;   /* byte235[6:5] */

    int size_gb   = get_sdram_size_gb(size_gb_raw);
    int bus_width = get_bus_width_bits(bus_width_raw);
    int dev_width = get_device_width_bits(dev_width_raw);
    int logical   = get_logical_rank(log_rank_raw);
    int pkg_rank  = PKG_RANK(pack_rank_raw);
    int ranks     = (logical > 0 && pkg_rank > 0) ? (logical * pkg_rank) : -1;
    int channels  = CHANNEL_NUM(ch_num_raw);

    if (size_gb < 0 || bus_width < 0 || dev_width < 0 || ranks <= 0 || channels <= 0)
        return -1;

    /* Size formula in MB */
    unsigned long long dimm_size_mb =
        (unsigned long long)size_gb * 1024ULL * (unsigned long long)ranks *
        (unsigned long long)channels * (unsigned long long)bus_width /
        (8ULL * (unsigned long long)dev_width);

    snprintf(out, out_len, "%llu MB", dimm_size_mb);
    return 0;
}

static int decode_ddr5_speed_from_compact(const uint8_t *spd, char *out, size_t out_len)
{
    if (!spd) return -1;
    uint16_t min_cycle = ((uint16_t)spd[SPD_SPEED_H] << 8) | spd[SPD_SPEED_L];
    for (int i = 0; i < ARRAY_LEN(spd5_dimm_speed); i++) {
        if (min_cycle <= spd5_dimm_speed[i].max_cycle) {
            snprintf(out, out_len, "%u MT/s", spd5_dimm_speed[i].speed);
            return 0;
        }
    }
    snprintf(out, out_len, "Unknown");
    return -1;
}

static const char *dimm_label_str(uint8_t dimm_id)
{
    static const char *labels[] = { "A0","A1","A2","A3","A4","A5","A6","A7","A8","A9","A10","A11" };
    return (dimm_id < ARRAY_LEN(labels)) ? labels[dimm_id] : "?";
}

/* ---------- Commands ---------- */

/* spd_raw <dimm_id> : dump the compact cache (50 bytes) */
static int cmd_spd_raw(const struct shell *shell, size_t argc, char **argv)
{
    if (argc != 2) {
        shell_print(shell, "Usage: spd_raw <dimm_id>");
        return -1;
    }
    char *endptr;
    uint8_t dimm_id = (uint8_t)strtol(argv[1], &endptr, 0);
    if (*endptr || dimm_id >= DIMM_ID_MAX) {
        shell_error(shell, "Invalid DIMM ID: %s", argv[1]);
        return -1;
    }

    uint8_t *raw; bool ready;
    int ret = plat_get_spd_raw(dimm_id, &raw, &ready);
    if (ret == -2) {
        shell_print(shell, "Status: No DIMM present");
        return 0;
    }
    if (ret != 0) {
        shell_print(shell, "Status: SPD read error");
        return 0;
    }
    if (!ready) {
        shell_print(shell, "Status: SPD not ready");
        return 0;
    }

    shell_print(shell, "SPD Compact Cache DIMM %u (0x00..0x%02X):", dimm_id, SPD_RAW_LEN-1);
    for (int offs = 0; offs < SPD_RAW_LEN; offs += 16) {
        shell_fprintf(shell, SHELL_NORMAL, "%02X: ", offs);
        for (int i = 0; i < 16 && offs + i < SPD_RAW_LEN; i++)
            shell_fprintf(shell, SHELL_NORMAL, "%02X ", raw[offs + i]);
        shell_fprintf(shell, SHELL_NORMAL, "\n");
    }
    return 0;
}

/* spd_config <dimm_id|all> : decode the compact cache */
static int cmd_spd_config(const struct shell *shell, size_t argc, char **argv)
{
    if (argc != 2) {
        shell_print(shell, "Usage: spd_config <dimm_id(0~%d)|all>", DIMM_ID_MAX-1);
        return -1;
    }

    bool list_all = (strcmp(argv[1], "all") == 0);
    uint8_t start_id = 0, end_id = DIMM_ID_MAX - 1;

    if (!list_all) {
        char *endptr;
        uint8_t dimm_id = (uint8_t)strtol(argv[1], &endptr, 0);
        if (*endptr != '\0' || dimm_id >= DIMM_ID_MAX) {
            shell_error(shell, "Invalid DIMM ID: %s", argv[1]);
            return -1;
        }
        start_id = end_id = dimm_id;
    }

    for (uint8_t dimm_id = start_id; dimm_id <= end_id; dimm_id++) {
        const char *lbl = dimm_label_str(dimm_id);
        shell_print(shell, "\nDIMM %s:", lbl);

        uint8_t *spd;
        bool ready;
        int rc = plat_get_spd_raw(dimm_id, &spd, &ready);
        if (rc == -2) {
            shell_print(shell, "  Status: No DIMM present");
            continue;
        }
        if (rc != 0) {
            shell_print(shell, "  Status: SPD read error");
            continue;
        }
        if (!ready) {
            shell_print(shell, "  Status: SPD not ready");
            continue;
        }

        char size_str[64]  = {0};
        char speed_str[64] = {0};
        if (decode_ddr5_size_from_compact(spd, size_str, sizeof(size_str)) != 0)
            snprintf(size_str, sizeof(size_str), "Unknown");
        if (decode_ddr5_speed_from_compact(spd, speed_str, sizeof(speed_str)) != 0)
            snprintf(speed_str, sizeof(speed_str), "Unknown");

        /* Manufacturer/vendor info from compact cache */
        uint16_t dimm_mfg_id = ((uint16_t)spd[SPD_MFG_ID_H] << 8) | spd[SPD_MFG_ID_L];
        uint8_t  mloc        = spd[SPD_MFG_LOC];
        uint8_t  myy         = spd[SPD_MFG_YY];
        uint8_t  mww         = spd[SPD_MFG_WW];

        char mfg_str[64]; snprintf(mfg_str, sizeof(mfg_str), "%s", mfg_string(dimm_mfg_id));
        char mfg_date[32]; snprintf(mfg_date, sizeof(mfg_date), "20%02u Week%02u", bcd_to_u8(myy), bcd_to_u8(mww));

        char mfg_loc[32];
        /* Optional vendor-specific decoding of location codes */
        if (strcmp(mfg_str, "Samsung") == 0) {
            switch (mloc) {
                case 1:  strcpy(mfg_loc, "South Korea");  break;
                case 2:  strcpy(mfg_loc, "China");        break;
                case 3:  strcpy(mfg_loc, "Philippines");  break;
                case 4:  strcpy(mfg_loc, "Vietnam");      break;
                default: snprintf(mfg_loc, sizeof(mfg_loc), "0x%02X", mloc);
            }
        } else if (strcmp(mfg_str, "Micron") == 0) {
            switch (mloc) {
                case  1: strcpy(mfg_loc, "SIG (USA)");        break;
                case  2: strcpy(mfg_loc, "MTB (Taiwan)");     break;
                case  5: strcpy(mfg_loc, "MNG (Malaysia)");   break;
                case  6: strcpy(mfg_loc, "MMP (Malaysia)");   break;
                case  7: strcpy(mfg_loc, "MNI (India)");      break;
                case  8: strcpy(mfg_loc, "SING (Singapore)"); break;
                case 10: strcpy(mfg_loc, "MSI (India)");      break;
                case 15: strcpy(mfg_loc, "MXA (China)");      break;
                case 26: strcpy(mfg_loc, "Hotayi (Malaysia)");break;
                case 37: strcpy(mfg_loc, "TSMT (Taiwan)");    break;
                default: snprintf(mfg_loc, sizeof(mfg_loc), "0x%02X", mloc);
            }
        } else {
            snprintf(mfg_loc, sizeof(mfg_loc), "0x%02X", mloc);
        }

        /* Serial number: compact bytes SPD_SN_OFF.. + SPD_SN_LEN */
        char sn[16] = {0};
        int pos = 0;
        for (int i = 0; i < SPD_SN_LEN; i++)
            pos += snprintf(sn + pos, sizeof(sn) - pos, "%02X", spd[SPD_SN_OFF + i]);

        /* Part number: SPD_PN_OFF.. + SPD_PN_LEN (ASCII) */
        char pn[64] = {0};
        for (int i = 0; i < SPD_PN_LEN && (int)strlen(pn) + 1 < (int)sizeof(pn); i++) {
            char c = (char)spd[SPD_PN_OFF + i];
            if (c >= 32 && c <= 126) {
                size_t l = strlen(pn);
                pn[l] = c;
                pn[l+1] = '\0';
            }
        }
        rstrip(pn);

        /* Register vendor & PMIC vendor from compact cache */
        uint16_t reg_id  = ((uint16_t)spd[SPD_REGVEN_H]  << 8) | spd[SPD_REGVEN_L];
        uint16_t pmic_id = ((uint16_t)spd[SPD_PMICVEN_H] << 8) | spd[SPD_PMICVEN_L];

        /* Output */
        shell_print(shell, "  Type: DDR5 SDRAM");
        shell_print(shell, "  Size: %s", size_str);
        shell_print(shell, "  Speed: %s", speed_str);
        shell_print(shell, "  Manufacturer: %s", mfg_str);
        shell_print(shell, "  Manufacturing Date: %s", mfg_date);
        shell_print(shell, "  Manufacturing Location: %s", mfg_loc);
        shell_print(shell, "  Part Number: %s", pn[0] ? pn : "N/A");
        shell_print(shell, "  Serial Number: %s", sn);
        shell_print(shell, "  Register Vendor: %s", mfg_string(reg_id));
        shell_print(shell, "  PMIC Vendor: %s", mfg_string(pmic_id));
    }

    return 0;
}

/* Register shell commands */
SHELL_CMD_REGISTER(spd_raw, NULL,
    "Dump compact SPD cache: spd_raw <dimm_id>", cmd_spd_raw);
SHELL_CMD_REGISTER(spd_config, NULL,
    "Decode DDR5 SPD (compact cache): spd_config <dimm_id|all>", cmd_spd_config);
