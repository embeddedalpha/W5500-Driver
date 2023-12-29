/*
 * W5500.c
 *
 *  Created on: Nov 14, 2023
 *      Author: kunal
 */


#include "W5500.h"
#include "W5500_LL.h"
#include "W5500_HAL.h"

int counter_reset = 0;
int counter = 0;
int counter_overflow = 100;







int W5500_Init(W5500_Config *config)
{
	SPI_Init(&config->SPI);
	SPI_Enable(&config->SPI);
	SPI_NSS_High(&config->SPI);
	// Read ID
	counter = counter_reset;
	while(counter < counter_overflow)
	{
		uint8_t ID = W5500_Read_ID(config);
		if(ID == 4) break;
		counter ++;
		Delay_ms(10);
	}
	if(counter >= counter_overflow) return -2;
/***************************************************************************************************************/
	// Check Up Link
	counter = counter_reset;
	while(counter < counter_overflow)
	{
		uint8_t Link ;
		Read_1_Byte(config, W5500_Common_Register.PHY_Configuration, W5500_Control_Register.Common_Register, &Link);
		if(Link & 0x01) break;
		counter ++;
		Delay_ms(10);
	}
	if(counter >= counter_overflow) return -3;
#if W5500_DEBUG_FLAG
// Print Speed, Status, Mode
#endif
/***************************************************************************************************************/
	counter = counter_reset;
	W5500_Setup_Source_Hardware_Address(config);
	W5500_Setup_Gateway_Address(config);
	W5500_Setup_Source_IP_Address(config);
	W5500_Setup_Subnet_Mask_Address(config);





	return 0;
}







uint8_t W5500_Socket_UDP_Setup(W5500_Config *config, W5500_Socket_Config *socket_config)
{
	if(socket_config->Hardware_Socket_Number == W5500_Hardware_Socket.Socket_1)
	{
		if(socket_config->client_server == W5500_Socket_Type.Client)
		{
			uint8_t data[2];
			Write_1_Byte(config, W5500_Socket_Register.Sn_TXBUF_SIZE, W5500_Control_Register.Socket_0_Control, 16);
			Write_1_Byte(config, W5500_Socket_Register.Sn_RXBUF_SIZE, W5500_Control_Register.Socket_0_Control, 16);


			data[0] = socket_config->Source_Port >> 8;
			data[1] = socket_config->Source_Port;
			Write_1_Byte(config, W5500_Socket_Register.Sn_MR, W5500_Control_Register.Socket_0_Control, W5500_Socket_Mode.UDP);
			Write_2_Byte(config, W5500_Socket_Register.Sn_PORT_0, W5500_Control_Register.Socket_0_Control, &data[0]);



			// Set Destination IP
			Write_4_Byte(config, W5500_Socket_Register.Sn_DIPR0, W5500_Control_Register.Socket_0_Control, socket_config->Destination_IP_Address);
			// Set Destinaiton Port
			data[0] = socket_config->Destination_Port >> 8;
			data[1] = socket_config->Destination_Port;
			Write_2_Byte(config, W5500_Socket_Register.Sn_DPORT0, W5500_Control_Register.Socket_0_Control, &data[0]);
		}
		else if(socket_config->client_server == W5500_Socket_Type.Server)
		{
			Write_1_Byte(config, W5500_Socket_Register.Sn_MR, W5500_Control_Register.Socket_0_Control, 0x20 | W5500_Socket_Type.Server);
		}
		else
		{
			return -1;
		}
	}


	else
	{
		return -1;
	}

	return 1;
}


uint8_t W5500_Socket_UDP_Send_Data(W5500_Config *config, W5500_Socket_Config *socket_config)
{
	if(socket_config->Hardware_Socket_Number == W5500_Hardware_Socket.Socket_1)
	{
		if(socket_config->client_server == W5500_Socket_Type.Client)
		{
			// Open Socket
			counter = counter_reset;
			Write_1_Byte(config, W5500_Socket_Register.Sn_CR, W5500_Control_Register.Socket_0_Control, W5500_Socket_Commands.OPEN);
			while(counter < counter_overflow)
			{
				uint8_t socket_response = 0x01;
				Read_1_Byte(config, W5500_Socket_Register.Sn_SR, W5500_Control_Register.Socket_0_Control, &socket_response);
				if(socket_response == W5500_Socket_Status.SOCK_UDP) break;
				counter ++;
				Delay_ms(10);
			}
			if(counter >= counter_overflow) return -1;

			Write_1_Byte(config, W5500_Socket_Register.Sn_TX_WR_0, W5500_Control_Register.Socket_0_Control, socket_config->data_len >> 8);
			Write_1_Byte(config, W5500_Socket_Register.Sn_TX_WR_1, W5500_Control_Register.Socket_0_Control, socket_config->data_len);
			Write_Multiple_Bytes(config, 0x0000, W5500_Control_Register.Socket_0_TX_Buffer, socket_config->data, socket_config->data_len);

			counter = counter_reset;
			Write_1_Byte(config, W5500_Socket_Register.Sn_CR, W5500_Control_Register.Socket_0_Control, W5500_Socket_Commands.SEND);
			while(counter < counter_overflow)
			{
				uint8_t socket_response = 0x01;
				Read_1_Byte(config, W5500_Socket_Register.Sn_IR, W5500_Control_Register.Socket_0_Control, &socket_response);
				if(socket_response == 0x10) break;
				counter ++;
				Delay_ms(10);
			}
			if(counter >= counter_overflow) return -1;
			counter = counter_reset;
			Write_1_Byte(config, W5500_Socket_Register.Sn_CR, W5500_Control_Register.Socket_0_Control, W5500_Socket_Commands.CLOSE);
			while(counter < counter_overflow)
			{
				uint8_t socket_response = 0x01;
				Read_1_Byte(config, W5500_Socket_Register.Sn_SR, W5500_Control_Register.Socket_0_Control, &socket_response);
				if(socket_response == W5500_Socket_Status.SOCK_CLOSED) break;
				counter ++;
				Delay_ms(10);
			}
			if(counter >= counter_overflow) return -1;
		}
	}
	else
	{
		return -1;
	}

	return -1;
}


