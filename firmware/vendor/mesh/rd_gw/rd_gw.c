#include "rd_gw.h"
#include "../rd_mesh_data/rd_mesh_data.h"

static Sw_Flash_Data Sw_Flash_Data_Val = { 0 };

u16 rd_get_gw_addr()
{
	return Sw_Flash_Data_Val.Gw_Add;
}

u8 rd_get_secure()
{
	return Sw_Flash_Data_Val.Secure_RD;
}

void RD_Flash_Save_DataDefault(void) {
	Sw_Flash_Data Flash_Data_Buff = { 0 };
	Flash_Data_Buff.Factory_Check = 0x00;
	Flash_Data_Buff.Gw_Add = GW_ADD_DEFAULT;
	Flash_Data_Buff.Secure_RD = 0;
	flash_erase_sector(RD_GATEWAY_FLASH_AREA);
	flash_write_page(RD_GATEWAY_FLASH_AREA, sizeof(Flash_Data_Buff),
			(uint8_t *) &Flash_Data_Buff.Factory_Check);
	flash_read_page(RD_GATEWAY_FLASH_AREA, sizeof(Sw_Flash_Data_Val),
			(uint8_t *) &Sw_Flash_Data_Val.Factory_Check);

#if UART_ON

	uart_CSend("Save Data default\n");

#endif
}

void RD_Flash_Data_Init(void) {
	flash_read_page(RD_GATEWAY_FLASH_AREA, sizeof(Sw_Flash_Data_Val),
			(uint8_t *) &Sw_Flash_Data_Val.Factory_Check);
	if (Sw_Flash_Data_Val.Factory_Check == 0xFF) // fist time to read reset memory
	{
		RD_Flash_Save_DataDefault();
	}
	u16 addr = (Sw_Flash_Data_Val.Gw_Add == 0x0000) ? 0x0001 : Sw_Flash_Data_Val.Gw_Add;
	set_rd_gw_addr(addr);
}

void RD_Flash_Save_Secure(uint8_t Secure_Stt)
{
	Sw_Flash_Data_Val.Secure_RD = Secure_Stt;

	flash_erase_sector(RD_GATEWAY_FLASH_AREA);
	flash_write_page(RD_GATEWAY_FLASH_AREA, sizeof(Sw_Flash_Data_Val), (uint8_t *) &Sw_Flash_Data_Val.Factory_Check );
}

void RD_Flash_SaveGwAdd(uint16_t Gw_Add)
{
	Sw_Flash_Data_Val.Gw_Add = Gw_Add;
	flash_erase_sector(RD_GATEWAY_FLASH_AREA);
	flash_write_page(RD_GATEWAY_FLASH_AREA, sizeof(Sw_Flash_Data_Val), (uint8_t *) &Sw_Flash_Data_Val.Factory_Check );
#if UART_ON
	char UART_TempSend[128];
	sprintf(UART_TempSend,"Save GW Address: 0x%x\n", Sw_Flash_Data_Val.Gw_Add);
	uart_CSend(UART_TempSend);
#endif
}
