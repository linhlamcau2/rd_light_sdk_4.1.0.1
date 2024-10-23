#include"rd_lib.h"
#include "rd_gw/rd_gw.h"
#include "rd_training_cct/rd_training_cct.h"
#include "rd_pair_k9b/rd_pair_k9b.h"

#include "tl_common.h"
#include "proj/mcu/watchdog_i.h"
#include "vendor/common/user_config.h"
#include "vendor/common/light.h"
#include "proj_lib/rf_drv.h"
#include "proj_lib/pm.h"
#include "proj_lib/ble/blt_config.h"
#include "proj_lib/ble/ll/ll.h"
#include "proj_lib/sig_mesh/app_mesh.h"

void rd_lighting_init(void)
{
	RD_Flash_Data_Init();

	RD_Flash_Training_Init();

	rd_flash_init_k9b();
}

void rd_lighting_loop(void )
{
	RD_Secure_CheckLoop();
}

void rd_lighting_factory_reset(void) {
	uart_CSend("Factory reset \n");
	RD_Flash_Save_DataDefault();
	RD_Flash_CleanTraining();
//	rd_flash_k9b_default();
	sleep_ms(200);
	factory_reset();
	start_reboot();
}
