#include <zephyr.h>
#include <stdio.h>
#include <string.h>
#include "plat_isr.h"
#include "power_status.h"
#include "plat_gpio.h"

#define POWER_SEQ_CTRL_STACK_SIZE 1000

K_THREAD_STACK_DEFINE(power_thread, POWER_SEQ_CTRL_STACK_SIZE);
struct k_thread power_thread_handler;
k_tid_t power_tid;

