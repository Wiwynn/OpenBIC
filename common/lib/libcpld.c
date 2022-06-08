#include <zephyr.h>
#include "libcpld.h"

__weak int pal_get_cpld_bus_addr(uint8_t *bus, uint8_t *addr) {
	return -1;
}
