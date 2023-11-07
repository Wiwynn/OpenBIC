#include <stdio.h>
#include <stdlib.h>
#include <zephyr.h>
#include <logging/log.h>
#include <errno.h>

#include "plat_dimm.h"

LOG_MODULE_REGISTER(plat_dimm);

static bool dimm_prsnt_inited = false;

bool is_dimm_prsnt_inited()
{
	return dimm_prsnt_inited;
}
