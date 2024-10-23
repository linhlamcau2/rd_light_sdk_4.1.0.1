#ifndef RD_MESH_DATA_H
#define RD_MESH_DATA_H


#include "tl_common.h"
#include "proj/mcu/watchdog_i.h"
#include "vendor/common/user_config.h"
#include "proj_lib/rf_drv.h"
#include "proj_lib/pm.h"
#include "proj_lib/ble/blt_config.h"
#include "proj_lib/ble/ll/ll.h"
#include "proj_lib/sig_mesh/app_mesh.h"

#define mesh_cmd_sig_RD_respone_status_type      	(0)

#define RD_OPCODE_TYPE_SEND				(0xE0)
#define RD_OPCODE_TYPE_RSP				(0xE1)
#define RD_OPCODE_SCENE_SEND			(0xE2)
#define RD_OPCODE_SCENE_RSP				(0xE3)

#define RD_HEADER_SET_TYPE_DEVICE		(0x0001)
#define RD_HEADER_SAVE_GW_ADD			(0x0002)
#define RD_HEADER_RSP_TYPE_DEVICE		(0x0003)
#define RD_HEADER_FACTORY_TEST_END		(0x0004)
#define RD_HEADER_KICK_ALL				(0xFFFF)


#define ALL_NODE			0xFFFF
#define MAX_TEMP			0x4e20
#define MIN_TEMP			0x0320

#define RD_VENDOR_EN							1

#define RD_MAXRESPONESEND 				(2)

#define RD_AUTO_CREATE_GR					(0x0C0A)
#define RD_AUTO_DELETE_GR					(0x0D0A)


#define TIME_RESET_ALL					60000


#define RD_HEADER_SW_PAIR_K9BREMOTE			(0x0A0B)
#define RD_HEADER_SW_SAVESCENE_K9BREMOTE	(0x0C0B)
#define RD_HEADER_SW_K9B_PRESS				(0x0B0B)
#define RD_HEADER_SW_SAVEK9BHC				(0x0D0B)
#define RD_HEADER_SW_DELETEK9BHC			(0x0E0B)
#define RD_HEADER_SW_DELETESCENE_K9BREMOTE	(0x0F0B)


u16 get_rd_gw_addr();
void set_rd_gw_addr(u16 addr);
void RD_ScanKickAll(void);

int RD_Messenger_ProcessCommingProcess_Type(u8 *par, int par_len, mesh_cb_fun_par_t *cb_par);
int RD_Messenger_ProcessCommingProcess_SCENE(u8 *par, int par_len, mesh_cb_fun_par_t *cb_par);


void RD_Handle_AutoCreateGr(u8 *par, uint16_t Gw_Add_Buff, mesh_cb_fun_par_t *cb_par);
void RD_Handle_AutoDeleteGr(u8 *par, uint16_t Gw_Add_Buff, mesh_cb_fun_par_t *cb_par);


#endif
