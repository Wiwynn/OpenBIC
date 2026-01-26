#include <device.h>
#include <toolchain.h>

/* 1 : /soc/syscon@7e6e2000/pinmux:
 * - (/soc/syscon@7e6e2000)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_syscon_7e6e2000_S_pinmux[] = { DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS,
							DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };

/* 2 : /soc/syscon@7e6e2000/sysclk/adc_clk:
 * - /soc/syscon@7e6e2000/sysclk
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_syscon_7e6e2000_S_sysclk_S_adc_clk[] = { 3, DEVICE_HANDLE_ENDS,
								  DEVICE_HANDLE_ENDS,
								  DEVICE_HANDLE_ENDS };

/* 3 : /soc/syscon@7e6e2000/sysclk:
 * - (/soc/syscon@7e6e2000)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_syscon_7e6e2000_S_sysclk[] = { DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS,
							DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };

/* 4 : /soc/syscon@7e6e2000/sysrst:
 * - (/soc/syscon@7e6e2000)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_syscon_7e6e2000_S_sysrst[] = { DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS,
							DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };

/* 5 : /soc/serial@7e784000:
 * - (/soc)
 * - (/soc/interrupt-controller@e000e100)
 * - /soc/syscon@7e6e2000/sysclk
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_serial_7e784000[] = { 3,
					       DEVICE_HANDLE_ENDS,
					       DEVICE_HANDLE_ENDS,
					       DEVICE_HANDLE_ENDS,
					       DEVICE_HANDLE_ENDS,
					       DEVICE_HANDLE_ENDS };

/* 6 : sysinit:
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_sys_init_sys_clock_driver_init0[] = { DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS,
						  DEVICE_HANDLE_ENDS };

/* 7 : /soc/espi@7e6ee000:
 * - (/soc)
 * - (/soc/interrupt-controller@e000e100)
 * - (/soc/syscon@7e6e2000)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_espi_7e6ee000[] = { DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS,
					     DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS,
					     DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };

/* 8 : /soc/gpio@7e780000/gpio0_u_v:
 * - /soc/gpio@7e780000
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_gpio_7e780000_S_gpio0_u_v[] = { 37, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS,
							 DEVICE_HANDLE_ENDS };

/* 9 : /soc/gpio@7e780000/gpio0_q_t:
 * - /soc/gpio@7e780000
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_gpio_7e780000_S_gpio0_q_t[] = { 37, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS,
							 DEVICE_HANDLE_ENDS };

/* 10 : /soc/gpio@7e780000/gpio0_m_p:
 * - /soc/gpio@7e780000
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_gpio_7e780000_S_gpio0_m_p[] = { 37, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS,
							 DEVICE_HANDLE_ENDS };

/* 11 : /soc/gpio@7e780000/gpio0_i_l:
 * - /soc/gpio@7e780000
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_gpio_7e780000_S_gpio0_i_l[] = { 37, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS,
							 DEVICE_HANDLE_ENDS };

/* 12 : /soc/gpio@7e780000/gpio0_e_h:
 * - /soc/gpio@7e780000
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_gpio_7e780000_S_gpio0_e_h[] = { 37, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS,
							 DEVICE_HANDLE_ENDS };

/* 13 : /soc/gpio@7e780000/gpio0_a_d:
 * - /soc/gpio@7e780000
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_gpio_7e780000_S_gpio0_a_d[] = { 37, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS,
							 DEVICE_HANDLE_ENDS };

/* 14 : /soc/udc@7e6a2000:
 * - (/soc)
 * - (/soc/interrupt-controller@e000e100)
 * - /soc/syscon@7e6e2000/sysrst
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_udc_7e6a2000[] = { 4,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS };

/* 15 : /soc/peci@7e78b000:
 * - (/soc)
 * - (/soc/interrupt-controller@e000e100)
 * - /soc/syscon@7e6e2000/sysclk
 * - /soc/syscon@7e6e2000/sysrst
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_peci_7e78b000[] = { 4,
					     3,
					     DEVICE_HANDLE_ENDS,
					     DEVICE_HANDLE_ENDS,
					     DEVICE_HANDLE_ENDS,
					     DEVICE_HANDLE_ENDS,
					     DEVICE_HANDLE_ENDS };

/* 16 : sysinit:
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_cdc_acm_0[] = { DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };

/* 17 : /soc/lpc@7e789000/snoop:
 * - (/soc/interrupt-controller@e000e100)
 * - (/soc/lpc@7e789000)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_lpc_7e789000_S_snoop[] = { DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS,
						    DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS,
						    DEVICE_HANDLE_ENDS };

/* 18 : /soc/adc@7e6e9100:
 * - (/soc)
 * - (/soc/interrupt-controller@e000e100)
 * - (/soc/syscon@7e6e2000)
 * - /soc/syscon@7e6e2000/sysrst
 * - (/soc/syscon@7e6e2000/pinmux/adc10_default)
 * - (/soc/syscon@7e6e2000/pinmux/adc11_default)
 * - (/soc/syscon@7e6e2000/pinmux/adc12_default)
 * - (/soc/syscon@7e6e2000/pinmux/adc13_default)
 * - (/soc/syscon@7e6e2000/pinmux/adc14_default)
 * - (/soc/syscon@7e6e2000/pinmux/adc15_default)
 * - (/soc/syscon@7e6e2000/pinmux/adc8_default)
 * - (/soc/syscon@7e6e2000/pinmux/adc9_default)
 * - /soc/syscon@7e6e2000/sysclk/adc_clk
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_adc_7e6e9100[] = { 1,
					    2,
					    4,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS };

/* 19 : /soc/adc@7e6e9000:
 * - (/soc)
 * - (/soc/interrupt-controller@e000e100)
 * - (/soc/syscon@7e6e2000)
 * - /soc/syscon@7e6e2000/sysrst
 * - (/soc/syscon@7e6e2000/pinmux/adc0_default)
 * - (/soc/syscon@7e6e2000/pinmux/adc1_default)
 * - (/soc/syscon@7e6e2000/pinmux/adc2_default)
 * - (/soc/syscon@7e6e2000/pinmux/adc3_default)
 * - (/soc/syscon@7e6e2000/pinmux/adc4_default)
 * - (/soc/syscon@7e6e2000/pinmux/adc5_default)
 * - (/soc/syscon@7e6e2000/pinmux/adc6_default)
 * - (/soc/syscon@7e6e2000/pinmux/adc7_default)
 * - /soc/syscon@7e6e2000/sysclk/adc_clk
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_adc_7e6e9000[] = { 1,
					    2,
					    4,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS };

/* 20 : /soc/i2c-global-regs@7e7b0000:
 * - (/soc)
 * - /soc/syscon@7e6e2000/sysclk
 * - /soc/syscon@7e6e2000/sysrst
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_i2c_global_regs_7e7b0000[] = {
	4, 3, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS
};

/* 21 : /soc/i2c@7e7b0500:
 * - (/soc)
 * - (/soc/interrupt-controller@e000e100)
 * - /soc/syscon@7e6e2000/sysclk
 * - (/soc/syscon@7e6e2000/pinmux/i2c9_default)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_i2c_7e7b0500[] = { 1,
					    3,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS };

/* 22 : /soc/i2c@7e7b0480:
 * - (/soc)
 * - (/soc/interrupt-controller@e000e100)
 * - /soc/syscon@7e6e2000/sysclk
 * - (/soc/syscon@7e6e2000/pinmux/i2c8_default)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_i2c_7e7b0480[] = { 1,
					    3,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS };

/* 23 : /soc/i2c@7e7b0400:
 * - (/soc)
 * - (/soc/interrupt-controller@e000e100)
 * - /soc/syscon@7e6e2000/sysclk
 * - (/soc/syscon@7e6e2000/pinmux/i2c7_default)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_i2c_7e7b0400[] = { 1,
					    3,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS };

/* 24 : /soc/i2c@7e7b0380:
 * - (/soc)
 * - (/soc/interrupt-controller@e000e100)
 * - /soc/syscon@7e6e2000/sysclk
 * - (/soc/syscon@7e6e2000/pinmux/i2c6_default)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_i2c_7e7b0380[] = { 1,
					    3,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS };

/* 25 : /soc/i2c@7e7b0300:
 * - (/soc)
 * - (/soc/interrupt-controller@e000e100)
 * - /soc/syscon@7e6e2000/sysclk
 * - (/soc/syscon@7e6e2000/pinmux/i2c5_default)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_i2c_7e7b0300[] = { 1,
					    3,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS };

/* 26 : /soc/i2c@7e7b0280:
 * - (/soc)
 * - (/soc/interrupt-controller@e000e100)
 * - /soc/syscon@7e6e2000/sysclk
 * - (/soc/syscon@7e6e2000/pinmux/i2c4_default)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_i2c_7e7b0280[] = { 1,
					    3,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS };

/* 27 : /soc/i2c@7e7b0200:
 * - (/soc)
 * - (/soc/interrupt-controller@e000e100)
 * - /soc/syscon@7e6e2000/sysclk
 * - (/soc/syscon@7e6e2000/pinmux/i2c3_default)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_i2c_7e7b0200[] = { 1,
					    3,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS };

/* 28 : /soc/i2c@7e7b0180:
 * - (/soc)
 * - (/soc/interrupt-controller@e000e100)
 * - /soc/syscon@7e6e2000/sysclk
 * - (/soc/syscon@7e6e2000/pinmux/i2c2_default)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_i2c_7e7b0180[] = { 1,
					    3,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS };

/* 29 : /soc/i2c@7e7b0100:
 * - (/soc)
 * - (/soc/interrupt-controller@e000e100)
 * - /soc/syscon@7e6e2000/sysclk
 * - (/soc/syscon@7e6e2000/pinmux/i2c1_default)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_i2c_7e7b0100[] = { 1,
					    3,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS };

/* 30 : /soc/i2c@7e7b0080:
 * - (/soc)
 * - (/soc/interrupt-controller@e000e100)
 * - /soc/syscon@7e6e2000/sysclk
 * - (/soc/syscon@7e6e2000/pinmux/i2c0_default)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_i2c_7e7b0080[] = { 1,
					    3,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS };

/* 31 : /soc/lpc@7e789000/kcs3:
 * - (/soc/interrupt-controller@e000e100)
 * - (/soc/lpc@7e789000)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_lpc_7e789000_S_kcs3[] = { DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS,
						   DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS,
						   DEVICE_HANDLE_ENDS };

/* 32 : /soc/jtag@7e6e4100:
 * - (/soc)
 * - (/soc/interrupt-controller@e000e100)
 * - /soc/syscon@7e6e2000/sysclk
 * - /soc/syscon@7e6e2000/sysrst
 * - (/soc/syscon@7e6e2000/pinmux/jtagm1_default)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_jtag_7e6e4100[] = { 1,
					     4,
					     3,
					     DEVICE_HANDLE_ENDS,
					     DEVICE_HANDLE_ENDS,
					     DEVICE_HANDLE_ENDS,
					     DEVICE_HANDLE_ENDS,
					     DEVICE_HANDLE_ENDS };

/* 33 : /soc/bus@7e7a0000/i3c-global-regs@0:
 * - (/soc/bus@7e7a0000)
 * - /soc/syscon@7e6e2000/sysrst
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_bus_7e7a0000_S_i3c_global_regs_0[] = {
	4, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS
};

/* 34 : /soc/bus@7e7a0000/i3c3@5000:
 * - (/soc/bus@7e7a0000)
 * - (/soc/interrupt-controller@e000e100)
 * - /soc/syscon@7e6e2000/sysclk
 * - /soc/syscon@7e6e2000/sysrst
 * - (/soc/syscon@7e6e2000/pinmux/i3c3_default)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_bus_7e7a0000_S_i3c3_5000[] = { 1,
							4,
							3,
							DEVICE_HANDLE_ENDS,
							DEVICE_HANDLE_ENDS,
							DEVICE_HANDLE_ENDS,
							DEVICE_HANDLE_ENDS,
							DEVICE_HANDLE_ENDS };

/* 35 : /soc/i2c@7e7b0380/ipmb@20:
 * - /soc/i2c@7e7b0380
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_i2c_7e7b0380_S_ipmb_20[] = { 24, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS,
						      DEVICE_HANDLE_ENDS };

/* 36 : /soc/i2c@7e7b0180/ipmb@20:
 * - /soc/i2c@7e7b0180
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_i2c_7e7b0180_S_ipmb_20[] = { 28, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS,
						      DEVICE_HANDLE_ENDS };

/* 37 : /soc/gpio@7e780000:
 * - (/soc)
 * - (/soc/interrupt-controller@e000e100)
 * - /soc/syscon@7e6e2000/sysclk
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_gpio_7e780000[] = { 3,
					     DEVICE_HANDLE_ENDS,
					     DEVICE_HANDLE_ENDS,
					     DEVICE_HANDLE_ENDS,
					     DEVICE_HANDLE_ENDS,
					     DEVICE_HANDLE_ENDS };

/* 38 : /soc/spi@7e630000:
 * - (/soc)
 * - (/soc/interrupt-controller@e000e100)
 * - /soc/syscon@7e6e2000/sysclk
 * - (/soc/syscon@7e6e2000/pinmux/spi1_quad)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_spi_7e630000[] = { 1,
					    3,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS };

/* 39 : /soc/spi@7e620000:
 * - (/soc)
 * - (/soc/interrupt-controller@e000e100)
 * - /soc/syscon@7e6e2000/sysclk
 * - (/soc/syscon@7e6e2000/pinmux/fmc_quad)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_spi_7e620000[] = { 1,
					    3,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS,
					    DEVICE_HANDLE_ENDS };

/* 40 : sysinit:
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_PRE_DEF_PROJ_GPIO[] = { DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };

/* 41 : /soc/wdt_common@7e785000:
 * - (/soc)
 * - (/soc/interrupt-controller@e000e100)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_wdt_common_7e785000[] = { DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS,
						   DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS,
						   DEVICE_HANDLE_ENDS };

/* 42 : /soc/spi@7e630000/flash@0:
 * - /soc/spi@7e630000
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_spi_7e630000_S_flash_0[] = { 38, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS,
						      DEVICE_HANDLE_ENDS };

/* 43 : /soc/spi@7e620000/flash@0:
 * - /soc/spi@7e620000
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_spi_7e620000_S_flash_0[] = { 39, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS,
						      DEVICE_HANDLE_ENDS };

/* 44 : /soc/wdt_common@7e785000/wdt@4:
 * - (/soc/syscon@7e6e2000)
 * - /soc/wdt_common@7e785000
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_wdt_common_7e785000_S_wdt_4[] = { 41, DEVICE_HANDLE_ENDS,
							   DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS,
							   DEVICE_HANDLE_ENDS };

/* 45 : /soc/wdt_common@7e785000/wdt@3:
 * - (/soc/syscon@7e6e2000)
 * - /soc/wdt_common@7e785000
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_wdt_common_7e785000_S_wdt_3[] = { 41, DEVICE_HANDLE_ENDS,
							   DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS,
							   DEVICE_HANDLE_ENDS };

/* 46 : /soc/wdt_common@7e785000/wdt@2:
 * - (/soc/syscon@7e6e2000)
 * - /soc/wdt_common@7e785000
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_wdt_common_7e785000_S_wdt_2[] = { 41, DEVICE_HANDLE_ENDS,
							   DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS,
							   DEVICE_HANDLE_ENDS };

/* 47 : /soc/wdt_common@7e785000/wdt@1:
 * - (/soc/syscon@7e6e2000)
 * - /soc/wdt_common@7e785000
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_wdt_common_7e785000_S_wdt_1[] = { 41, DEVICE_HANDLE_ENDS,
							   DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS,
							   DEVICE_HANDLE_ENDS };
