#ifndef PLAT_FUNC_H
#define PLAT_FUNC_H

void ISR_CL_DC_ON();
void ISR_DC_ON();
void control_power_sequence();
void init_power_on_thread();
void init_power_off_thread();
void abort_power_thread();

#endif
