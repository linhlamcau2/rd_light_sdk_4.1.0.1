#include "rd_mesh_data.h"
#include "../rd_type_dev/rd_type_dev.h"
#include "../rd_mesh_data/rd_mesh_data.h"
#include "../rd_log/rd_log.h"
#include "../rd_lib.h"
#include "../rd_secure/rd_secure.h"
#include "../rd_gw/rd_gw.h"

static uint16_t rd_gw_addr  = GW_ADD_DEFAULT;
static u8 Kick_all_Flag = 0;

u16 get_rd_gw_addr()
{
	return rd_gw_addr;
}

void set_rd_gw_addr(u16 addr)
{
	rd_gw_addr = addr;
}

void RD_ScanKickAll(void)
{
	if(Kick_all_Flag==1)
	{
		static uint32_t countDownt =0;
		static uint8_t check_reset_Flag=0;
		if(check_reset_Flag == 0)
		{
			check_reset_Flag =1;
			countDownt = clock_time_ms();
		}
		if( (check_reset_Flag == 1) && ((clock_time_ms() - countDownt) >= TIME_RESET_ALL) )
		{
			uart_CSend("\nFactory Reset\n");
			rd_lighting_factory_reset();
		}
	}
}

static void RD_Mess_RspSecure(uint8_t Secure_Rsp_Stt, uint16_t Gw_Add_Buff)
{
	uint8_t Mess_buff[8] = {0};

	if(Secure_Rsp_Stt == RD_EN)
	{
		Mess_buff[0]	= RD_HEADER_RSP_TYPE_DEVICE & 0xff;
		Mess_buff[1]	= (RD_HEADER_RSP_TYPE_DEVICE >> 8) & 0xff;
		Mess_buff[2]	= Device_BROADCRARD_0;
		Mess_buff[3]	= Device_BROADCRARD_1;
		Mess_buff[4]	= Device_BROADCRARD_2;
		Mess_buff[5]	= 0x00;
		Mess_buff[6] 	= VERSION_FIRM_H;
		Mess_buff[7]	= VERSION_FIRM_L;
		mesh_tx_cmd2normal_primary(RD_OPCODE_TYPE_RSP, Mess_buff, 8, Gw_Add_Buff, RD_MAXRESPONESEND);
		uart_CSend("Rsp Secure success \n");
	}
	else
	{
		Mess_buff[0]	= RD_HEADER_RSP_TYPE_DEVICE & 0xff;
		Mess_buff[1]	= (RD_HEADER_RSP_TYPE_DEVICE >> 8) & 0xff;
		Mess_buff[2]	= 0xFF;
		Mess_buff[3]	= 0xFE;
		Mess_buff[4]	= 0xFF;
		Mess_buff[5]	= 0xFE;
		Mess_buff[6] 	= 0xFF;
		Mess_buff[7]	= 0xFE;
		mesh_tx_cmd2normal_primary(RD_OPCODE_TYPE_RSP, Mess_buff, 8, Gw_Add_Buff, RD_MAXRESPONESEND);
		uart_CSend("Rsp Secure failed \n");
	}
}

static void RD_Handle_MessType(uint8_t par[8], uint16_t Gw_Add_Buff)
{
	uint8_t Secure_return =0;
	#if(SECURE_ON ==1)

		if(get_provision_state() == STATE_DEV_PROVED)
		{
			Secure_return = RD_Secure_AesreCheck(&RD_key[0], &tbl_mac[0], ele_adr_primary, &par[2]);

			rd_ev_log("Secure key Pass; %d \n",Secure_return);
			RD_Flash_Save_Secure(Secure_return);
			RD_Secure_Set(Secure_return);
			RD_Mess_RspSecure(Secure_return,Gw_Add_Buff);
			RD_set_check_secure(Secure_return);
		}
		else
		{
			RD_Mess_RspSecure(RD_EN, Gw_Add_Buff);
		}
	#else
	Secure_return =1;
	RD_Flash_Save_Secure(RD_EN);			// save secure pass to flash memory
	RD_Mess_RspSecure(RD_EN, Gw_Add_Buff);
	#endif
}

static void RD_Handle_SaveGw(uint8_t par[8], uint16_t Gw_Add_Buff)
{
	uint16_t GwAddToSave = par[3]<<8 | par[2];

	rd_gw_addr = GwAddToSave ? GwAddToSave:Gw_Add_Buff;

	char UART_TempSend[64];
	sprintf(UART_TempSend,"Save GWAdd:%x \n", rd_gw_addr);
	uart_CSend(UART_TempSend);
	if(get_provision_state() == STATE_DEV_PROVED)
	{
		RD_Flash_SaveGwAdd(rd_gw_addr);
		rd_ev_log("Save GWAdd to Flash :%x \n",rd_gw_addr);
	}
	else
	{
		rd_ev_log("Save GWAdd to Ram for test :%x \n",rd_gw_addr);
	}
	uint8_t Mess_buff[8] = {0};
	u16 gw_addr = rd_get_gw_addr();
	Mess_buff[0]	= RD_HEADER_SAVE_GW_ADD 				& 0xff;
	Mess_buff[1]	= (RD_HEADER_SAVE_GW_ADD >> 8) 			& 0xff;
	Mess_buff[2]	= gw_addr		 						& 0xff;
	Mess_buff[3]	= (gw_addr >> 8) 						& 0xff;
	Mess_buff[4]	= PROVIDER_ID  							& 0xff;
	Mess_buff[5]	= (PROVIDER_ID >> 8) 					& 0xff;
	Mess_buff[6] 	= 0x00;
	Mess_buff[7]	= 0x00;

	mesh_tx_cmd2normal_primary(RD_OPCODE_TYPE_RSP, Mess_buff, 8, Gw_Add_Buff, RD_MAXRESPONESEND); // rsp to Gw send mess
//	RD_SwitchAc4Ch_BlinkSet(5, 100);
}


static void RD_Handle_KickAll(uint8_t par[8], uint16_t Gw_Add_Buff)
{
	if((par[2]==0x01) && (par[3]==0x02) && (par[4]==0x03) && (par[5]==0x04) && (par[6]==0x05) && (par[7]==0x06))
	{
		uart_CSend("Reset All device. countdown 60s to reset \n");
		Kick_all_Flag=1;
		mesh_tx_cmd2normal_primary(RD_OPCODE_TYPE_RSP, par, 8, Gw_Add_Buff, RD_MAXRESPONESEND);
//		RD_SwitchAc4Ch_BlinkSet(5, 100);
	}
}

int RD_Messenger_ProcessCommingProcess_Type(u8 *par, int par_len, mesh_cb_fun_par_t *cb_par)
{
	#if UART_ON
		uart_CSend("Co ban tin");
		char UART_TempSend[128];
		sprintf(UART_TempSend,"Messenger type:%d-Content:%x-%x-%x-%x-%x-%x-%x-%x\n",par_len,par[0],par[1],par[2],par[3],par[4],par[5],par[6],par[7]);
		uart_CSend(UART_TempSend);
		uart_CSend("..\n");
	#endif

	uint16_t Gw_Add_Buff =0x00;
	Gw_Add_Buff = cb_par->adr_src;

	uint16_t header_Buff = 0x0000;
	header_Buff = (par[1] << 8 | par[0]);
	switch (header_Buff)
	{
		case(RD_HEADER_RSP_TYPE_DEVICE):
			RD_Handle_MessType(par, Gw_Add_Buff);
			break;
		case(RD_HEADER_SAVE_GW_ADD):
			RD_Handle_SaveGw(par, Gw_Add_Buff);
			break;
//		case(RD_HEADER_FACTORY_TEST_END):
//			RD_Hanlde_FactoryTestEnd( Gw_Add_Buff);
//			break;
		case(RD_HEADER_KICK_ALL):
			RD_Handle_KickAll(par, Gw_Add_Buff);
			break;
		default:
			uart_CSend("Wrong header E0 \n");
			break;
	}
	return 0;
}





int RD_Messenger_ProcessCommingProcess_SCENE(u8 *par, int par_len, mesh_cb_fun_par_t *cb_par)
{
	uart_CSend("co ban tin E2\n");

	uint16_t Header_buff =0x00;
	uint16_t Gw_Add_Buff =0x01;
	uint16_t Add_Receiver = ele_adr_primary;

	Header_buff = ((par[1]<<8) | par[0]);
	Gw_Add_Buff = cb_par->adr_src;
	Add_Receiver = cb_par->adr_dst;
	char UART_Buff[128];
	switch (Header_buff)
	{
		case RD_AUTO_CREATE_GR:
		{
			RD_Handle_AutoCreateGr(par, Gw_Add_Buff, cb_par );
			break;
		}
		case RD_AUTO_DELETE_GR:
		{
			RD_Handle_AutoDeleteGr(par, Gw_Add_Buff, cb_par );
			break;
		}
//		case RD_HEADER_CONTROL_SW_TOUCH:
//			RD_Handle_CTR_SW(par, Gw_Add_Buff);
//			break;
//		case RD_HEADER_SWITCH_TOUCH_STT:
//			Send_Relay_Stt_Message_RALL(Gw_Add_Buff);
//			break;
//		case RD_HEADER_SW_SETUP_LINKCTR:
//			RD_Handle_SetUp_LinkControl2(par, Gw_Add_Buff, Add_Receiver);
//			break;
//		case RD_HEADER_SW_SETUP_COUNT_DOWN:
//			#if(COUNT_DOWN_EN == 1)
//				RD_Handle_SetUp_CountDown(par, Gw_Add_Buff, Add_Receiver);
//			#else
//				uart_CSend("This function only on Switch x1\n");
//			#endif
//			break;
		case RD_HEADER_SW_PAIR_K9BREMOTE:
			//RD_Handle_PairK9BHc(par, Gw_Add_Buff);
			RD_Handle_ScanK9BHc(par, Gw_Add_Buff);
			break;
		case RD_HEADER_SW_SAVEK9BHC:
			RD_Handle_SaveK9BHc(par, Gw_Add_Buff);
			break;
		case RD_HEADER_SW_DELETEK9BHC:
			RD_Handle_DeleteK9BHC(par, Gw_Add_Buff);
			break;
		case RD_HEADER_SW_SAVESCENE_K9BREMOTE:
			RD_Handle_K9BSaveScene(par, Gw_Add_Buff);
			break;
		case RD_HEADER_SW_DELETESCENE_K9BREMOTE:
			RD_Handle_K9BDeleteScene(par, Gw_Add_Buff);
			break;


//		case RD_HEADER_SW_POWUP_CONFIG:
//			RD_Handle_PowUpConfig(par, Gw_Add_Buff);
//			break;
//		case RD_HEADER_SET_K9B_LOCAL_MODE:
//			RD_Handle_K9BLocalModeConfig(par, Gw_Add_Buff);
//			break;
//		case RD_AUTO_DELETE_GR:
//			RD_Handle_AutoDeleteGr(par, Gw_Add_Buff, cb_par );
//			break;
		default:
			sprintf(UART_Buff,"wrong header:  %x \n",Header_buff);
			uart_CSend(UART_Buff);
			break;
	}

	return 0;
}
