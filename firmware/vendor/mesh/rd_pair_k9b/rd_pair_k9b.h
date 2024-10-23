#ifndef RD_PAIR_K9B_H
#define RD_PAIR_K9B_H


#include "tl_common.h"
#include "proj/mcu/watchdog_i.h"
#include "vendor/common/user_config.h"
#include "proj_lib/rf_drv.h"
#include "proj_lib/pm.h"
#include "proj_lib/ble/blt_config.h"
#include "proj_lib/ble/ll/ll.h"
#include "proj_lib/sig_mesh/app_mesh.h"


#include "../rd_type_dev/rd_type_dev.h"

typedef struct
{
	u8 but;
	u16 sence;
}call_sence_t;

typedef struct
{
	u32 macK9b;
	u16	addrK9b;
	call_sence_t call_sence[MAX_MUM_K9BPRESSTYPE];
	u8 num_but;
	u8 num_but_max;
}remoteK9b_sence_t;

typedef struct
{
	u8 factory_check;
	remoteK9b_sence_t remoteK9b_sence[MAX_NUM_K9BHC];
	u8 numK9b;
}remote_k9b_save_t;

typedef struct
{
	uint8_t Pair_K9BOnOff_Flag;
	uint8_t Button_K9BOnOff_Pair;
	uint8_t Pair_K9BHc_Flag;
	uint16_t Add_K9B_HCSet;			// HC set add for K9B remote
	uint32_t ClockTimeSetHc_ms;
	uint32_t Clock_BtK9BStartPress_ms[3];
	uint8_t  Bt_K9B_CountPress[3];
    uint32_t Clock_time_start_pair_onOff_ms;
} Sw_Working_Stt_Str;

void rd_flash_k9b_default(void);
void rd_flash_init_k9b();


void RD_Handle_SaveK9BHc(uint8_t par[8], uint16_t Gw_Add_Buff);
void RD_Handle_ScanK9BHc(uint8_t par[8], uint16_t Gw_Add_Buff);
void RD_Handle_DeleteK9BHC(uint8_t par[8], uint16_t Gw_Add_Buff);
void RD_Handle_K9BSaveScene(uint8_t par[8], uint16_t Gw_Add_Buff);
void RD_Handle_K9BDeleteScene(uint8_t par[8], uint16_t Gw_Add_Buff);

#endif
