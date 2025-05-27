#include <shell/shell.h>
#include <kernel.h>
#include <logging/log.h>
#include "mctp.h"
#include "mctp_ctrl.h"
#include "plat_mctp.h"
#include <stdlib.h>

LOG_MODULE_REGISTER(mctp_shell, LOG_LEVEL_INF);
extern uint8_t plat_eid;
extern mctp_route_entry plat_mctp_route_tbl[];

static int cmd_mctp_print_eid(const struct shell *shell, size_t argc, char **argv)
{
    uint8_t eid = plat_get_eid();
    shell_print(shell, "Current MCTP EID: %d", eid);
    return 0;
}

static int cmd_mctp_print_plat_eids(const struct shell *shell, size_t argc, char **argv)
{
    shell_print(shell, "Platform MCTP EID: %d", plat_eid);
    for (int i = 1; i <= 3; i++) {
        shell_print(shell, "Route Entry %d EID: %d", i, plat_mctp_route_tbl[i].endpoint);
    }
    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(mctp_cmds,
    SHELL_CMD(print_eid, NULL, "Print MCTP EID", cmd_mctp_print_eid),
    // SHELL_CMD(set_eid, NULL, "Set MCTP EID", cmd_mctp_set_eid),
    // SHELL_CMD(send, NULL, "Send MCTP message", cmd_mctp_send_msg),
    SHELL_CMD(print_plat_eid, NULL, "Print platform MCTP EID", cmd_mctp_print_plat_eids),
    SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(mctp, &mctp_cmds, "MCTP shell commands", NULL);