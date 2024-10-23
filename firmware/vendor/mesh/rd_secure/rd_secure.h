
#ifndef RD_SECURE_H_
#define RD_SECURE_H_


#include "proj/tl_common.h"
#include "proj/mcu/watchdog_i.h"
#include "vendor/common/user_config.h"
#include "proj_lib/rf_drv.h"
#include "proj_lib/pm.h"
#include "proj_lib/ble/blt_config.h"
#include "proj_lib/ble/ll/ll.h"
#include "proj_lib/sig_mesh/app_mesh.h"
#include "../../common/light.h"

extern unsigned char RD_key[16];

#define TIME_UOT_SECURE     120000    // 120s factory reset
#define TIME_UOT_KEY_FAIL 	5000		// 5s factory reset if key fail
typedef struct
{
    uint8_t Check_Secure_Ready;    // call after Provisioned
    uint8_t Secure_Pass;
    uint32_t Time_Start_check;     // time ms in provisiones
    uint8_t  Check_Key_Fail;
    uint32_t Time_Check_Key_Fail;
} Secure_Stt_Str;

typedef enum
{
	RD_DIS =0,
	RD_EN,
}rd_setup_t;
void rd_set_ota_flasg(u8 stt);

unsigned char RD_Secure_AesreCheck(uint8_t key[16], uint8_t mac[6], uint16_t unicast, uint8_t compare_key[6]);

void RD_Secure_CheckLoop(void);

void RD_Secure_CheckInit(void);

void RD_Secure_Set(uint8_t Secure_Pass_Stt);

void RD_set_check_secure(u8 stt);

void RD_Secure_Check_Key_Fail(void);

#endif /* RD_SECURE_H_ */
