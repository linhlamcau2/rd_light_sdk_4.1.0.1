#ifndef RD_FLASH_H
#define RD_FLASH_H

#include "../rd_type_dev/rd_type_dev.h"

#include "tl_common.h"
#include "proj/mcu/watchdog_i.h"
#include "vendor/common/user_config.h"
#include "proj_lib/rf_drv.h"
#include "proj_lib/pm.h"
#include "proj_lib/ble/blt_config.h"
#include "proj_lib/ble/ll/ll.h"
#include "proj_lib/sig_mesh/app_mesh.h"
typedef struct
{
	u8 Factory_Check;
	u8 Future[3];
	u8 Secure_RD;
	u16 Gw_Add;
} Sw_Flash_Data;

u16 rd_get_gw_addr();
u8 rd_get_secure();

void RD_Flash_Save_DataDefault(void);
void RD_Flash_Data_Init(void);
void RD_Flash_Save_Secure(uint8_t Secure_Stt);
void RD_Flash_SaveGwAdd(uint16_t Gw_Add);

#endif
