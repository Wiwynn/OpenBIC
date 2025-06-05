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
		shell_print(shell, "Route Entry 2 EID: %d (CXL1 SetEID done)",
			    plat_mctp_route_tbl[2].endpoint);
	} else {
		shell_print(shell, "Route Entry 2 EID: %d (CXL1 not set)",
			    plat_mctp_route_tbl[2].endpoint);
	}

	// CXL2
	if (get_eid_set_done(CXL_ID_2)) {
		shell_print(shell, "Route Entry 3 EID: %d (CXL2 SetEID done)",
			    plat_mctp_route_tbl[3].endpoint);
	} else {
		shell_print(shell, "Route Entry 3 EID: %d (CXL2 not set)",
			    plat_mctp_route_tbl[3].endpoint);
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

static int cmd_mctp_query_cxl_eid(const struct shell *shell, size_t argc, char **argv)
{
	if (argc != 2) {
		shell_error(shell, "Usage: mctp query_cxl_eid <0|1>");
		return -EINVAL;
	}

	uint8_t cxl_id = strtoul(argv[1], NULL, 10);
	if (cxl_id != CXL_ID_1 && cxl_id != CXL_ID_2) {
		shell_error(shell, "Invalid CXL ID: %d", cxl_id);
		return -EINVAL;
	}

	mctp *mctp_inst = NULL;
	mctp_ext_params ext_params = { 0 };
	uint8_t eid = plat_get_cxl_eid(cxl_id);

	if (get_mctp_info(eid, &mctp_inst, &ext_params) != MCTP_SUCCESS) {
		shell_error(shell, "Failed to get MCTP info for CXL%d", cxl_id + 1);
		return -EIO;
	}

	mctp_ctrl_msg msg = { 0 };
	msg.hdr.rq = 1;
	msg.hdr.cmd = MCTP_CTRL_CMD_GET_ENDPOINT_ID;
	msg.ext_params = ext_params;

	uint8_t resp_buf[8] = { 0 };
	if (mctp_ctrl_read(mctp_inst, &msg, resp_buf, sizeof(resp_buf)) != MCTP_SUCCESS) {
		shell_error(shell, "Failed to query CXL%d EID", cxl_id + 1);
		return -EIO;
	}

	// Response[0] = completion code, Response[1] = EID
	shell_print(shell, "CXL%d device reports EID: %d", cxl_id + 1, resp_buf[1]);

	return 0;
}

static int cmd_mctp_print_eid_reset_count(const struct shell *shell, size_t argc, char **argv)
{
	shell_print(shell, "CXL1 EID reset count: %u", cxl1_eid_reset_count);
	shell_print(shell, "CXL2 EID reset count: %u", cxl2_eid_reset_count);
	return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(
	mctp_cmds, SHELL_CMD(print_eid, NULL, "Print MCTP EID", cmd_mctp_print_eid),
	// SHELL_CMD(set_eid, NULL, "Set MCTP EID", cmd_mctp_set_eid),
	// SHELL_CMD(send, NULL, "Send MCTP message", cmd_mctp_send_msg),
	SHELL_CMD(print_plat_eid, NULL, "Print platform MCTP EID", cmd_mctp_print_plat_eids),
	SHELL_CMD(set_cxl_eid, NULL, "Trigger setting CXL EIDs", cmd_mctp_set_cxl_eid),
	SHELL_CMD(query_cxl_eid, NULL, "Query actual EID from CXL1 or CXL2",
		  cmd_mctp_query_cxl_eid),
	SHELL_CMD(print_eid_reset_count, NULL, "Print CXL1/CXL2 EID reset count",
		  cmd_mctp_print_eid_reset_count),
	SHELL_SUBCMD_SET_END);

SHELL_CMD_REGISTER(mctp, &mctp_cmds, "MCTP shell commands", NULL);