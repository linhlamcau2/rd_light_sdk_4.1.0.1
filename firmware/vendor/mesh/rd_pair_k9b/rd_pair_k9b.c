#include"rd_pair_k9b.h"
#include "../rd_type_dev/rd_type_dev.h"

remote_k9b_save_t remote_k9b_save;
Sw_Working_Stt_Str Sw_Working_Stt_Val = {0};

static void flash_save_remote_k9b()
{
	flash_erase_sector(RD_K9B_FLASH_AREA);
	flash_write_page(RD_K9B_FLASH_AREA, sizeof(remote_k9b_save_t), (uint8_t *) &remote_k9b_save.factory_check );
	uart_CSend("flash k9b\n");
}

void rd_flash_k9b_default(void)
{
	memset((void *)&remote_k9b_save,0,sizeof(remote_k9b_save_t));
	flash_save_remote_k9b();
}
void rd_flash_init_k9b()  //
{
	flash_read_page(RD_K9B_FLASH_AREA, sizeof(remote_k9b_save_t),(uint8_t *) &remote_k9b_save.factory_check);
	if (remote_k9b_save.factory_check == 0xFF) // fist time to read reset memory
	{
		memset((void *)&remote_k9b_save,0,sizeof(remote_k9b_save_t));
	}
}

void RD_K9B_PairHCSet(uint8_t pairStt, uint16_t K9BAdd)
{
	Sw_Working_Stt_Val.Add_K9B_HCSet = K9BAdd;
	Sw_Working_Stt_Val.Pair_K9BHc_Flag = pairStt;
	Sw_Working_Stt_Val.ClockTimeSetHc_ms = clock_time_ms();
}

void RD_Handle_ScanK9BHc(uint8_t par[8], uint16_t Gw_Add_Buff)
{
	uart_CSend("Start waiting K9B HC \n");
	uint8_t  K9BPairHc_Stt = par[2];
	RD_K9B_PairHCSet(K9BPairHc_Stt, 0x0000); // turn on K9B pair Hc
}

static int idx_mac_appear(uint32_t mac)
{
	for(int i=0; i<remote_k9b_save.numK9b; i++)
	{
		if(mac == remote_k9b_save.remoteK9b_sence[i].macK9b)
			return i;
	}
	return -1;
}
static int id_but_appear(uint8_t id_mac)
{

}

static u8 is_full_save_k9b()
{
	return (remote_k9b_save.numK9b < MAX_NUM_K9BHC) ? 0:1;
}

uint8_t RD_Flash_SaveK9BHc(u32 macDevice, u8 Num_Of_Button, u16 K9BAdd)
{
	int idx_save = idx_mac_appear(macDevice);
	if(idx_save == -1 && is_full_save_k9b())
		return 0;
	if(idx_save == -1 )
		remote_k9b_save.numK9b ++;
	idx_save = (idx_save == -1) ? remote_k9b_save.numK9b -1 : idx_save;

	remote_k9b_save.remoteK9b_sence[idx_save].addrK9b = K9BAdd;
	remote_k9b_save.remoteK9b_sence[idx_save].macK9b = macDevice;
	remote_k9b_save.remoteK9b_sence[idx_save].num_but_max = Num_Of_Button;

	flash_save_remote_k9b();
	return 1;
}

void RD_Handle_SaveK9BHc(uint8_t par[8], uint16_t Gw_Add_Buff)
{
	uint32_t MacK9B_Buff = (uint32_t) ( (par[5]<<24) | (par[4]<<16) | (par[3]<<8) | (par[2]));
	uint16_t K9BAdd	 	 = (uint16_t) ((par[7] << 8) | par[6]  );
	uint8_t SaveK9B_Stt = RD_Flash_SaveK9BHc(MacK9B_Buff, 3, K9BAdd);// save max button

	uint8_t MessRsp[7];
	for(int i=0; i<6; i++) MessRsp[i] =  par[i];

	MessRsp[6] = SaveK9B_Stt;

	mesh_tx_cmd2normal_primary(RD_OPCODE_SCENE_RSP , &MessRsp[0], 7, Gw_Add_Buff, RD_MAXRESPONESEND);
	uart_CSend("Save Mac K9BHC \n");
}

uint8_t RD_Flash_DeleteK9BHC(uint16_t K9BAdd)
{
	if(0xFFFF != K9BAdd)
	{
		for(int i=0; i<remote_k9b_save.numK9b; i++)
		{
			if(remote_k9b_save.remoteK9b_sence[i].addrK9b == K9BAdd)
			{
				for(int j=i; j<remote_k9b_save.numK9b -1; j++)
				{
					memcpy((void*)&remote_k9b_save.remoteK9b_sence[j], (void*)&remote_k9b_save.remoteK9b_sence[j+1],sizeof(remoteK9b_sence_t));
				}
				remote_k9b_save.numK9b --;
				flash_save_remote_k9b();
				uart_CSend("delete K9B HC\n");
				return 1;
			}
		}
		uart_CSend("don't have  K9B HC to delete");
		return 0; // no data to delete
	}
	else
	{
		memset((void*)&remote_k9b_save,0,sizeof(remote_k9b_save_t));
		flash_save_remote_k9b();
		uart_CSend("delete all remote K9B HC");
		return 1;
	}
}

void RD_Handle_DeleteK9BHC(uint8_t par[8], uint16_t Gw_Add_Buff)
{
	uint16_t K9BAdd	 	 = (uint16_t) ((par[3] << 8) | par[2]  );
	uint8_t SaveK9B_Stt = RD_Flash_DeleteK9BHC(K9BAdd);

	uint8_t Mess_RspBuff[5] ={0};
	Mess_RspBuff[0]	= RD_HEADER_SW_DELETEK9BHC 				& 0xFF;
	Mess_RspBuff[1]	= (RD_HEADER_SW_DELETEK9BHC >> 8) 		& 0xFF;
	Mess_RspBuff[2]	= K9BAdd 				& 0xFF;
	Mess_RspBuff[3]	= (K9BAdd >> 8) 		& 0xFF;
	Mess_RspBuff[4] =  SaveK9B_Stt;

	mesh_tx_cmd2normal_primary(RD_OPCODE_SCENE_RSP , &Mess_RspBuff[0], 5, Gw_Add_Buff, RD_MAXRESPONESEND);
	uart_CSend("Delete K9BHC \n");
}
static int get_idx_but(u8 idx_addr, u8 but)
{
	for(int i=0; i<remote_k9b_save.remoteK9b_sence[idx_addr].num_but;i++)
	{
		if(remote_k9b_save.remoteK9b_sence[idx_addr].call_sence[i].but == but)
		{
			return i;
		}
	}
	return -1;
}

static int is_full_sence(u8 idx_addr)
{
	return (remote_k9b_save.remoteK9b_sence[idx_addr].num_but < MAX_MUM_K9BPRESSTYPE) ? 0 : 1;
}
uint8_t RD_Flash_SaveSceneK9BHC(uint16_t K9BAdd, uint8_t ButtonID, uint16_t SceneID)
{
	for(int i=0; i<remote_k9b_save.numK9b; i++)
	{
		if(remote_k9b_save.remoteK9b_sence[i].addrK9b == K9BAdd)		// task memory is ready for new
		{
			int idx_but = get_idx_but(i,ButtonID);
			if(idx_but == -1 && is_full_sence(i))
				return 0;
			if(idx_but == -1)
				remote_k9b_save.remoteK9b_sence[i].num_but ++;
			idx_but = ((idx_but == -1)) ? (remote_k9b_save.remoteK9b_sence[i].num_but -1) : idx_but ;

			remote_k9b_save.remoteK9b_sence[i].call_sence[idx_but].but = ButtonID;
			remote_k9b_save.remoteK9b_sence[i].call_sence[idx_but].sence = SceneID;

			flash_save_remote_k9b();
			uart_CSend("Save K9B HC scene \n");
			return 1;
		}
	}
	return 0;
}

void RD_Handle_K9BSaveScene(uint8_t par[8], uint16_t Gw_Add_Buff)
{
	uint16_t K9BAdd = (uint16_t) ((par[3] << 8) | par[2] );
	uint8_t ButtonID = par[4];
	uint8_t ModeID = par[5];
	uint16_t Scene_ID	= (uint16_t) ((par[7] << 8) | par[6] );

	//uart_CSend("save Scene add:%x  BID:%d Scene ID: 0x%x\n",K9BAdd,  ButtonID, Scene_ID);
	uart_CSend("save Scene K9B\n");
	uint8_t SaveStt = RD_Flash_SaveSceneK9BHC(K9BAdd, ButtonID, Scene_ID);

	uint8_t Mess_RspBuff[3] ={0};
	Mess_RspBuff[0]	= RD_HEADER_SW_SAVESCENE_K9BREMOTE 				& 0xFF;
	Mess_RspBuff[1]	= (RD_HEADER_SW_SAVESCENE_K9BREMOTE >> 8) 		& 0xFF;
	Mess_RspBuff[2]	= SaveStt;

	mesh_tx_cmd2normal_primary(RD_OPCODE_SCENE_RSP , &Mess_RspBuff[0], 3, Gw_Add_Buff, RD_MAXRESPONESEND);

}

static void rd_copy_k9b(u8 id_but_1, u8 id_but_2, u8 idx_addr)
{
	memcpy((void *)&remote_k9b_save.remoteK9b_sence[idx_addr].call_sence[id_but_1],\
			(void *)&remote_k9b_save.remoteK9b_sence[idx_addr].call_sence[id_but_2],sizeof(call_sence_t));
}

static uint8_t RD_Flash_DeleteSceneK9BHC(u16 k9b_addr, u8 but)
{
	if(0xFFFF != k9b_addr)
	{
		for(int i=0; i<remote_k9b_save.numK9b; i++)
		{
			if(remote_k9b_save.remoteK9b_sence[i].addrK9b == k9b_addr)
			{
				if(but != 0xFF)
				{
					int idx_but = get_idx_but(i,but);
					if(idx_but == -1)
						return 0;
					for(int j=idx_but; j < remote_k9b_save.remoteK9b_sence[i].num_but -1; j++)
					{
						rd_copy_k9b(j,j+1,i);
					}
					remote_k9b_save.remoteK9b_sence[i].num_but --;
					flash_save_remote_k9b();
					return 1;
				}
				else
				{
					remote_k9b_save.remoteK9b_sence[i].num_but = 0;
					return 1;
				}
			}
		}

		uart_CSend("don't have  K9B HC to delete Scene");
		return 0; // no data to delete
	}
	else
	{
		for(int i =0; i<remote_k9b_save.numK9b; i++)
		{
			remote_k9b_save.remoteK9b_sence[i].num_but = 0;
		}
		flash_save_remote_k9b();
		uart_CSend("delete all scene of all K9B \n");
		return 1;
	}
}


void RD_Handle_K9BDeleteScene(uint8_t par[8], uint16_t Gw_Add_Buff)
{
	uint16_t K9BAdd 	= (uint16_t) ((par[3] << 8) | par[2] );
	uint8_t ButtonID 	= par[4];
	uint8_t ModeID 		= par[5];
	uint8_t deleteStt= RD_Flash_DeleteSceneK9BHC(K9BAdd,ButtonID);

	uint8_t Mess_RspBuff[3] ={0};
	Mess_RspBuff[0]	= RD_HEADER_SW_DELETESCENE_K9BREMOTE 				& 0xFF;
	Mess_RspBuff[1]	= (RD_HEADER_SW_DELETESCENE_K9BREMOTE >> 8) 		& 0xFF;
	Mess_RspBuff[2]	= deleteStt;

	mesh_tx_cmd2normal_primary(RD_OPCODE_SCENE_RSP , &Mess_RspBuff[0], 3, Gw_Add_Buff, RD_MAXRESPONESEND);
}
