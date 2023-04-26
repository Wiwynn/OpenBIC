
#ifndef PLAT_I3C_h
#define PLAT_I3C_h

#include "hal_i3c.h"

/* i3c 8-bit addr */
#define I3C_STATIC_ADDR_BIC     0x40
#define I3C_STATIC_ADDR_BMC     0x20
#define I3C_STATIC_ADDR_EXPA_BIC         0x9
#define I3C_STATIC_ADDR_EXPB_BIC         0xA

#define I3C_HUB_ADDR 0x70

/* i3c dev bus */
#define I3C_BUS_BMC 0 
#define I3C_BUS_CONTROLLER 1
#define I3C_BUS_HUB 1
#define I3C_ADDR_HUB 0x70

#endif