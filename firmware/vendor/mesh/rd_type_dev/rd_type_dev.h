#ifndef RD_TYPE_DEV_H
#define RD_TYPE_DEV_H

#define VERSION_FIRM_H				0x01   // sw new cover
#define VERSION_FIRM_L				0x01

#define RD_PROVIDER					0x0001
#define VHT_PROVIDER				0x0200
#define HUE_PROVIDER				0x0201
#define PROVIDER_ID					RD_PROVIDER

#define	Device_BROADCRARD_0		0x02	//Switch
#define	Device_BROADCRARD_3		0x00
#define	Device_BROADCRARD_4		((PROVIDER_ID >>8) & 0xFF) // khong dao
#define	Device_BROADCRARD_5		(PROVIDER_ID       & 0xFF) // khong dao
#define	Device_BROADCRARD_6		VERSION_FIRM_H
#define	Device_BROADCRARD_7		VERSION_FIRM_L
#define	Device_BROADCRARD_2		0x07
#define	Device_BROADCRARD_1     0x04

#define UART_ON					 1
#define CONFIG_POWUP_EN				1
#define GW_ADD_DEFAULT				0x0001

#define SECURE_ON					1
#define FLASH_SAVE_SECURE_SIZE   8
#define RD_SECURE_FLASH_AREA (0x7a000)		//RD_EDIT: SEC : AREA SAVE FLASH NOTE CCT-RGB !!!!!
#define ENABLE_SECURE 		0	//RD_EDIT: ENA OR DIS SER
//--------------------------------------------------------------------

#define FLASH_SAVE_TYPE_SIZE   		 16
#define FLASH_SAVE_TRAINING_SIZE     6
#define RD_GATEWAY_FLASH_AREA  		(0x78000)
#define RD_TRAINING_FLASH_AREA 		(0x79000)
#define RD_K9B_FLASH_AREA 			(0x7b000)
#define RD_CHECK_FLASH_H	0x55
#define RD_CHECK_FLASH_L	0xAA

#define MAX_MUM_K9BPRESSTYPE		12
#define MAX_NUM_K9BHC				5


#endif
