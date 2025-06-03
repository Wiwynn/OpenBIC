#include <shell/shell.h>
#include <kernel.h>
#include <logging/log.h>
#include "mctp.h"
#include "mctp_ctrl.h"
#include "plat_mctp.h"
#include "plat_power_seq.h"
#include <stdlib.h>

LOG_MODULE_REGISTER(mctp_shell, LOG_LEVEL_INF);
extern uint8_t plat_eid;
extern mctp_route_entry plat_mctp_route_tbl[];
extern bool get_eid_set_done(uint8_t cxl_id);

static int cmd_mctp_print_eid(const struct shell *shell, size_t argc, char **argv)
{
    uint8_t eid = plat_get_eid();
    shell_print(shell, "Current MCTP EID: %d", eid);
    return 0;
}

static int cmd_mctp_print_plat_eids(const struct shell *shell, size_t argc, char **argv)
{
    shell_print(shell, "Platform MCTP EID: %d", plat_eid);

	// SD-BIC entry (idx 1)
	shell_print(shell, "Route Entry 1 EID: %d", plat_mctp_route_tbl[1].endpoint);

	// CXL1
	if (get_eid_set_done(CXL_ID_1)) {
		shell_print(shell, "Route Entry 2 EID: %d (CXL1 SetEID done)", plat_mctp_route_tbl[2].endpoint);
	} else {
		shell_print(shell, "Route Entry 2 EID: %d (CXL1 not set)", plat_mctp_route_tbl[2].endpoint);
	}

	// CXL2
	if (get_eid_set_done(CXL_ID_2)) {
		shell_print(shell, "Route Entry 3 EID: %d (CXL2 SetEID done)", plat_mctp_route_tbl[3].endpoint);
	} else {
		shell_print(shell, "Route Entry 3 EID: %d (CXL2 not set)", plat_mctp_route_tbl[3].endpoint);
	}

	return 0;
}

static int cmd_mctp_set_cxl_eid(const struct shell *shell, size_t argc, char **argv)
{
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    shell_print(shell, "Triggering CXL EID setting...");
    create_set_dev_endpoint_thread();
    shell_print(shell, "Set CXL EID thread triggered.");

    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(mctp_cmds,
    SHELL_CMD(print_eid, NULL, "Print MCTP EID", cmd_mctp_print_eid),
    // SHELL_CMD(set_eid, NULL, "Set MCTP EID", cmd_mctp_set_eid),
    // SHELL_CMD(send, NULL, "Send MCTP message", cmd_mctp_send_msg),
    SHELL_CMD(print_plat_eid, NULL, "Print platform MCTP EID", cmd_mctp_print_plat_eids),
    SHELL_CMD(set_cxl_eid, NULL, "Trigger setting CXL EIDs", cmd_mctp_set_cxl_eid),
    SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(mctp, &mctp_cmds, "MCTP shell commands", NULL);