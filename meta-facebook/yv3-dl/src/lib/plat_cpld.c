#include "libcpld.h"
#include "plat_i2c.h"

int pal_get_cpld_bus_addr(uint8_t *bus, uint8_t *addr) {
	*bus = I2C_BUS_CPLD;
	*addr = CPLD_ADDR;
	return 0;
}
