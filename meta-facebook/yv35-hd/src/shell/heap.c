#include <zephyr.h>
#include <shell/shell.h>
#include <sys/sys_heap.h>

extern struct sys_heap _system_heap;
static int cmd_system(const struct shell *shell, size_t argc, char **argv)
{
	sys_heap_print_info(&_system_heap, false);
	return 0;
}

// Remove **static** modifier of z_malloc_heap at zephyr/lib/libc/minimal/source/stdlib/malloc.c:34.
extern struct sys_heap z_malloc_heap;
static int cmd_libc(const struct shell *shell, size_t argc, char **argv)
{
	sys_heap_print_info(&z_malloc_heap, false);
	return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(
	sub_heap, SHELL_CMD(system, NULL, "Show system::k_malloc heap statistic", cmd_system),
	SHELL_CMD(libc, NULL, "Show libc::malloc heap statistic", cmd_libc), SHELL_SUBCMD_SET_END);
SHELL_CMD_REGISTER(heap, &sub_heap, "Heap Statistic", NULL);