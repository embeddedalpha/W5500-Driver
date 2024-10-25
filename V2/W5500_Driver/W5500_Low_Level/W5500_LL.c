/*
 * W5500_LL.c
 *
 *  Created on: Oct 18, 2024
 *      Author: ksalvi
 */


#include <W5500_Low_Level/W5500_LL.h>


SPI_Config *w5500_spi;

void LL_W5500_Init_Link(SPI_Config *_spi_)
{
	w5500_spi = _spi_;
	SPI_Init(w5500_spi);
}

bool LL_W5500_Write_Common_Register(uint16_t Control_Register, uint8_t data[], uint16_t len)
{
	if(len)
	{
		uint8_t control_phase = 0;
		control_phase = W5500_Control_Register.Common_Register_Base << 3 | (1 << 2);

		SPI_NSS_Low(w5500_spi);
		SPI_TRX_Byte(w5500_spi, (0xFF00 & Control_Register)>>8);
		SPI_TRX_Byte(w5500_spi, (0x00FF & Control_Register)>>0);
		SPI_TRX_Byte(w5500_spi, control_phase);

		for(int i =0; i < len; i++)
		{
			SPI_TRX_Byte(w5500_spi, data[i]);
		}

		SPI_NSS_High(w5500_spi);
		return 1;
	}
	return 0;
}




bool LL_W5500_Read_Common_Register(uint16_t Control_Register, uint8_t *data, uint16_t len)
{
	if(len)
	{
		uint8_t control_phase = 0;
		control_phase = W5500_Control_Register.Common_Register_Base << 3 | (0 << 2);

		SPI_NSS_Low(w5500_spi);
		SPI_TRX_Byte(w5500_spi, (0xFF00 & Control_Register)>>8);
		SPI_TRX_Byte(w5500_spi, (0x00FF & Control_Register)>>0);
		SPI_TRX_Byte(w5500_spi, control_phase);

		for(int i =0; i < len; i++)
		{
			*data++ = SPI_TRX_Byte(w5500_spi, 0xAA);
		}

		SPI_NSS_High(w5500_spi);
		return 1;
	}
	return 0;
}

bool LL_W5500_Write_Socket_Configuration_Register(uint16_t Socket_Register, uint8_t socket_number, uint8_t data[], uint16_t len)
{
	if(socket_number > 7) return 0;
	if(len)
	{
		uint8_t control_phase = 0;

		control_phase = ((socket_number + (socket_number*3) + 1) << 3 ) | (1 << 2);

		SPI_NSS_Low(w5500_spi);
		SPI_TRX_Byte(w5500_spi, (0xFF00 & Socket_Register)>>8);
		SPI_TRX_Byte(w5500_spi, (0x00FF & Socket_Register)>>0);
		SPI_TRX_Byte(w5500_spi, control_phase);

		for(int i =0; i < len; i++)
		{
			SPI_TRX_Byte(w5500_spi, data[i]);
		}

		SPI_NSS_High(w5500_spi);
		return 1;
	}
	return 0;
}

bool LL_W5500_Read_Socket_Configuration_Register(uint16_t Socket_Register, uint8_t socket_number, uint8_t *data, uint16_t len)
{
	if(socket_number > 7) return 0;
	if(len)
	{
		uint8_t control_phase = 0;

		control_phase = ((socket_number + (socket_number*3) + 1) << 3 ) | (0 << 2);

		SPI_NSS_Low(w5500_spi);
		SPI_TRX_Byte(w5500_spi, (0xFF00 & Socket_Register)>>8);
		SPI_TRX_Byte(w5500_spi, (0x00FF & Socket_Register)>>0);
		SPI_TRX_Byte(w5500_spi, control_phase);

		for(int i =0; i < len; i++)
		{
			*data++ = SPI_TRX_Byte(w5500_spi, 0xAA);
		}

		SPI_NSS_High(w5500_spi);
		return 1;
	}
	return 0;
}

bool LL_W5500_Write_Socket_Buffer(uint16_t address, uint8_t socket_number, uint8_t tx_data[], uint16_t len)
{
	if(socket_number > 7) return 0;
	if(len)
	{
		uint8_t control_phase = 0;

		control_phase = ((socket_number + (socket_number*3) + 2) << 3 ) | (1 << 2);

		SPI_NSS_Low(w5500_spi);
		SPI_TRX_Byte(w5500_spi, (0xFF00 & address)>>8);
		SPI_TRX_Byte(w5500_spi, (0x00FF & address)>>0);
		SPI_TRX_Byte(w5500_spi, control_phase);

//		for(int i =0; i < len; i++)
//		{
//			SPI_TRX_Byte(w5500_spi, 0xAA);
//		}

		SPI_TRX_Buffer(w5500_spi, (uint16_t *)tx_data, NULL, len, 0);

		SPI_NSS_High(w5500_spi);
		return 1;
	}
	return 0;
}


bool LL_W5500_Write_Socket_0_Buffer( uint8_t *tx_data[], uint16_t len)
{
	uint8_t temp_buffer[2];

	LL_W5500_Read_Socket_Configuration_Register(W5500_Control_Register.Socket_Register.Sn_TX_FSR0, 0, temp_buffer, 2);

}

bool LL_W5500_Read_Socket_Buffer(uint16_t address, uint8_t socket_number, uint8_t *rx_data[], uint16_t len)
{


	if(socket_number > 7) return 0;
	if(len)
	{
		uint8_t control_phase = 0;

		control_phase = ((socket_number + (socket_number*3) + 3) << 3 ) | (0 << 2);

		SPI_NSS_Low(w5500_spi);
		SPI_TRX_Byte(w5500_spi, (0xFF00 & address)>>8);
		SPI_TRX_Byte(w5500_spi, (0x00FF & address)>>0);
		SPI_TRX_Byte(w5500_spi, control_phase);

//		for(int i =0; i < len; i++)
//		{
//			SPI_TRX_Byte(w5500_spi, 0xAA);
//		}

		SPI_TRX_Buffer(w5500_spi, NULL, (uint16_t *)rx_data, 0, len);

		SPI_NSS_High(w5500_spi);
		return 1;
	}
	return 0;
}
