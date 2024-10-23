#include "rd_training_cct.h"


typedef struct{
	u8 used;
	u8 step;
	u8 cnt_cycle;
}Flash_Save_Training;

Flash_Save_Training Flash_Save_Training_Val;

u8 Flag_Factory_Mode = 1;

u8 RD_get_flag_fac_mode()
{
	return Flag_Factory_Mode;
}


void RD_Flash_CleanTraining(void)
{
	Flash_Save_Training_Val.used = 0;

#if(ENABLE_TRAINING_1)		//RD_EDIT: 0.THANH : SPM: TRAINING
		Flash_Save_Training_Val.step			=  0;
		Flash_Save_Training_Val.cnt_cycle		=  0;
#else
		Flash_Save_Training_Val.step			=  6;
		Flash_Save_Training_Val.cnt_cycle		=  6;
#endif

	unsigned char *Flash_Data_Buff;
	Flash_Data_Buff = (unsigned char *) (&Flash_Save_Training_Val.used);

   	flash_erase_sector(RD_TRAINING_FLASH_AREA);
	flash_write_page(RD_TRAINING_FLASH_AREA, sizeof(Flash_Save_Training), Flash_Data_Buff );

	flash_read_page(RD_TRAINING_FLASH_AREA, sizeof(Flash_Save_Training), (unsigned char *) (&Flash_Save_Training_Val.used));
}

void RD_Flash_Training_Init(void)
{
	flash_read_page(RD_TRAINING_FLASH_AREA, sizeof(Flash_Save_Training), (unsigned char *) (&Flash_Save_Training_Val.used));

	if(Flash_Save_Training_Val.used == 0xff)														// fist time to read reset memory
	{
		RD_Flash_CleanTraining();
	}
	else{
#if(!ENABLE_TRAINING_1)		//RD_EDIT: 0.THANH : SPM: TRAINING
		if((Flash_Save_Training_Val.step != 6)||(Flash_Save_Training_Val.cnt_cycle != 6)){
			RD_Flash_CleanTraining();
		}
#endif
	}
}


void RD_Flash_SaveTraining(unsigned char step, unsigned char cycle )
{
	Flash_Save_Training_Val.step		=  step;
	Flash_Save_Training_Val.cnt_cycle	=  cycle;

	unsigned char *Flash_Data_Buff;
	Flash_Data_Buff = (unsigned char *) (&Flash_Save_Training_Val.used);

   	flash_erase_sector(RD_TRAINING_FLASH_AREA);
	flash_write_page(RD_TRAINING_FLASH_AREA, sizeof(Flash_Save_Training), Flash_Data_Buff );

	flash_read_page(RD_TRAINING_FLASH_AREA, sizeof(Flash_Save_Training), (unsigned char *)(&Flash_Save_Training_Val.used));
}

void Init_Training_1()
{
	u8 step 	   = Flash_Save_Training_Val.step;
	u8 cnt_cycle  = Flash_Save_Training_Val.cnt_cycle;

	if (get_provision_state() == STATE_DEV_PROVED) {
		if (step != 6) {
			Flag_Factory_Mode = 1;
			step = 6;
			cnt_cycle = 6;
			RD_Flash_SaveTraining(step, cnt_cycle);
		}
	} else if ((get_provision_state() == STATE_DEV_UNPROV) && (step < 6)) {
		gatt_adv_send_flag = 0;
		beacon_send.en = 0;
		Flag_Factory_Mode = 0;
	}

	else if((get_provision_state() == STATE_DEV_UNPROV) && (step > 5)){
		Flag_Factory_Mode = 1;
	}

	if (step == 0 || step == 1 || step == 2 || step == 3) {
		step = 5;
	}

	if (step == 4) {
		Flag_Factory_Mode = 1;
		gatt_adv_send_flag = 1;
		beacon_send.en = 1;
		step = 6;
		cnt_cycle = 6;
		RD_Flash_SaveTraining(step, cnt_cycle);
		st_pub_list_t pub_list = { { 0 } };
		mesh_cmd_light_ctl_set_t p_set;
		mesh_cmd_lightness_set_t p_set_light;
		p_set_light.lightness = 0xffff;
		lightness_set(&p_set_light, 3, 0, 0, 0, &pub_list);
		p_set.temp = 0x4e20;
		light_ctl_temp_set(&p_set, 7, 0, 0, 0, &pub_list);
		sleep_ms(10);
		factory_reset();
		start_reboot();
	}
}

