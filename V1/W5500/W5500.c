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
int counter_overflow = 1000;







int W5500_Init(W5500_Config *config)
{
	SPI_Init(&config->SPI);
	SPI_Enable(&config->SPI);
	SPI_NSS_High(&config->SPI);

	Write_1_Byte(config, W5500_Common_Register.Mode, W5500_Control_Register.Common_Register , 1<<7);
	Delay_s(1);


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
	uint8_t data[2];
	data[0] = config->Source_Port >> 8;
	data[1] = config->Source_Port;
	Write_2_Byte(config, W5500_Socket_Register.Sn_PORT_0, W5500_Control_Register.Socket_0_Control, &data[0]);


	data[0] = 0xFF;
	data[1] = 0xFE;
	Write_1_Byte(config, W5500_Common_Register.Retry_Time_0, W5500_Control_Register.Common_Register, data[0]);
	Write_1_Byte(config, W5500_Common_Register.Retry_Time_1, W5500_Control_Register.Common_Register, data[1]);
	data[0] = 0xF5;
	Write_1_Byte(config, W5500_Common_Register.Retry_Count, W5500_Control_Register.Common_Register, data[0]);
	Write_1_Byte(config, W5500_Socket_Register.Sn_TXBUF_SIZE, W5500_Control_Register.Socket_0_Control, 16);
	Write_1_Byte(config, W5500_Socket_Register.Sn_RXBUF_SIZE, W5500_Control_Register.Socket_0_Control, 16);

	return 0;
}

void W5500_Socket_Mutlticast_UDP_Init(W5500_Config *config, W5500_Socket_Config *socket_config)
{
	Write_1_Byte(config, W5500_Socket_Register.Sn_TXBUF_SIZE, W5500_Control_Register.Socket_0_Control, 16);
	Write_1_Byte(config, W5500_Socket_Register.Sn_RXBUF_SIZE, W5500_Control_Register.Socket_0_Control, 16);

	uint8_t data[2];
	data[0] = config->Source_Port >> 8;
	data[1] = config->Source_Port;

	Write_1_Byte(config, W5500_Common_Register.Mode, W5500_Control_Register.Common_Register, 1 << 1 );

	Write_1_Byte(config, W5500_Socket_Register.Sn_MR, W5500_Control_Register.Socket_0_Control, W5500_Socket_Mode.UDP | (1 << 7) );
	Write_2_Byte(config, W5500_Socket_Register.Sn_PORT_0, W5500_Control_Register.Socket_0_Control, &data[0]);


	// Set Destination IP
	Write_4_Byte(config, W5500_Socket_Register.Sn_DIPR0, W5500_Control_Register.Socket_0_Control, socket_config->Destination_IP_Address);
	// Set Destinaiton Port
	data[0] = socket_config->Destination_Port >> 8;
	data[1] = socket_config->Destination_Port;
	Write_2_Byte(config, W5500_Socket_Register.Sn_DPORT0, W5500_Control_Register.Socket_0_Control, &data[0]);
}

int8_t W5500_Socket_Multicast_UDP_Send_Packet(W5500_Config *config, W5500_Socket_Config *socket_config)
{
	// Check if the link is up
	uint8_t Link;
	Read_1_Byte(config, W5500_Common_Register.PHY_Configuration, W5500_Control_Register.Common_Register, &Link);
	if(!(Link & 0x01)) return -1;

	// If link is UP, Open Socket
	counter = counter_reset;
	while(counter < counter_overflow)
	{
		uint8_t socket_response = 0x01;
		Write_1_Byte(config, W5500_Socket_Register.Sn_CR, W5500_Control_Register.Socket_0_Control, W5500_Socket_Commands.OPEN);
		Read_1_Byte(config, W5500_Socket_Register.Sn_SR, W5500_Control_Register.Socket_0_Control, &socket_response);
		if(socket_response == W5500_Socket_Status.SOCK_UDP) break;
		else{
			counter = counter_reset;
			Write_1_Byte(config, W5500_Socket_Register.Sn_CR, W5500_Control_Register.Socket_0_Control, W5500_Socket_Commands.CLOSE);
			while(counter < counter_overflow)
			{
				uint8_t socket_response = 0x01;
				Read_1_Byte(config, W5500_Socket_Register.Sn_SR, W5500_Control_Register.Socket_0_Control, &socket_response);
				if(socket_response == W5500_Socket_Status.SOCK_CLOSED) break;
				else{
					Write_1_Byte(config, W5500_Socket_Register.Sn_MR, W5500_Control_Register.Socket_0_Control, W5500_Socket_Mode.UDP);
				}
				counter ++;
				Delay_ms(10);
			}
			 return -4;
		}
		counter ++;
		Delay_ms(10);
	}
	if(counter >= counter_overflow) return -2;

	// Send Data
	Write_1_Byte(config, W5500_Socket_Register.Sn_TX_WR_0, W5500_Control_Register.Socket_0_Control, socket_config->data_len >> 8);
	Write_1_Byte(config, W5500_Socket_Register.Sn_TX_WR_1, W5500_Control_Register.Socket_0_Control, socket_config->data_len);

	socket_config->data_len = 100;
	for(int i = 0; i < 100; i++)
	{
		socket_config->data[i] = i;
	}


	Write_Multiple_Bytes(config, 0x0000, W5500_Control_Register.Socket_0_TX_Buffer, socket_config->data, socket_config->data_len);

	counter = counter_reset;
	while(counter < counter_overflow)
	{
		uint8_t socket_response = 0x01;
		Write_1_Byte(config, W5500_Socket_Register.Sn_CR, W5500_Control_Register.Socket_0_Control, W5500_Socket_Commands.SEND);
		Read_1_Byte(config, W5500_Socket_Register.Sn_IR, W5500_Control_Register.Socket_0_Control, &socket_response);
		if(socket_response && 0x10) break;
		counter ++;
		Delay_ms(10);
	}
	if(counter >= counter_overflow) return -3;

	// Close Socket
	counter = counter_reset;
	Write_1_Byte(config, W5500_Socket_Register.Sn_CR, W5500_Control_Register.Socket_0_Control, W5500_Socket_Commands.CLOSE);
	while(counter < counter_overflow)
	{
		uint8_t socket_response = 0x01;
		Read_1_Byte(config, W5500_Socket_Register.Sn_SR, W5500_Control_Register.Socket_0_Control, &socket_response);
		if(socket_response == W5500_Socket_Status.SOCK_CLOSED) break;
		else{
			Write_1_Byte(config, W5500_Socket_Register.Sn_MR, W5500_Control_Register.Socket_0_Control, W5500_Socket_Mode.UDP);
		}
		counter ++;
		Delay_ms(10);
	}
	if(counter >= counter_overflow) return -4;

	return 1;

}


int8_t W5500_Socket_TCP_Open(W5500_Config *config, W5500_Socket_Config *socket_config)
{
	uint8_t data[2];
	Write_1_Byte(config, W5500_Socket_Register.Sn_MR, W5500_Control_Register.Socket_0_Control, W5500_Socket_Mode.TCP);

	// Open Socket
	counter = counter_reset;

	data[0] = socket_config->Destination_Port >> 8;
	data[1] = socket_config->Destination_Port;
	Write_2_Byte(config, W5500_Socket_Register.Sn_DPORT0, W5500_Control_Register.Socket_0_Control, &data[0]);
	Write_4_Byte(config, W5500_Socket_Register.Sn_DIPR0, W5500_Control_Register.Socket_0_Control, socket_config->Destination_IP_Address);
	while(counter < counter_overflow)
	{
		uint8_t socket_response = 0x00;
		Write_1_Byte(config, W5500_Socket_Register.Sn_CR, W5500_Control_Register.Socket_0_Control, W5500_Socket_Commands.OPEN);
		Read_1_Byte(config, W5500_Socket_Register.Sn_SR, W5500_Control_Register.Socket_0_Control, &socket_response);
		if(socket_response == W5500_Socket_Status.SOCK_INIT) break;
		counter ++;
		Delay_ms(10);
	}
	if(counter >= counter_overflow) return -1;
	counter = counter_reset;
	while(counter < counter_overflow)
	{
		uint8_t socket_response1, socket_response2;
		Write_1_Byte(config, W5500_Socket_Register.Sn_CR, W5500_Control_Register.Socket_0_Control, W5500_Socket_Commands.CONNECT);

		Read_1_Byte(config, W5500_Socket_Register.Sn_SR, W5500_Control_Register.Socket_0_Control, &socket_response1);
		Read_1_Byte(config, W5500_Socket_Register.Sn_IR, W5500_Control_Register.Socket_0_Control, &socket_response2);
		if((socket_response1 == W5500_Socket_Status.SOCK_ESTABLISHED) || (socket_response2 == 0x01) ) break;
		counter ++;
		Delay_ms(10);
	}
	if(counter >= counter_overflow) return -2;
	return 1;
}



int8_t W5500_Socket_TCP_Send_Data(W5500_Config *config, W5500_Socket_Config *socket_config)
{
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
	else return 1;
}


int8_t W5500_Socket_TCP_Close(W5500_Config *config, W5500_Socket_Config *socket_config)
{
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

int8_t W5500_Socket_TCP_Disconnect(W5500_Config *config, W5500_Socket_Config *socket_config)
{
	counter = counter_reset;
	Write_1_Byte(config, W5500_Socket_Register.Sn_CR, W5500_Control_Register.Socket_0_Control, W5500_Socket_Commands.DISCON);
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















int8_t W5500_Socket_UDP_Setup(W5500_Config *config, W5500_Socket_Config *socket_config)
{
	if(socket_config->client_server == W5500_Socket_Type.Client)
	{


		uint8_t data[2];
		data[0] = config->Source_Port >> 8;
		data[1] = config->Source_Port;

//		Write_1_Byte(config, W5500_Common_Register.Mode, W5500_Control_Register.Common_Register,  (1 << 1) );
		Write_1_Byte(config, W5500_Socket_Register.Sn_MR, W5500_Control_Register.Socket_0_Control, W5500_Socket_Mode.UDP);
		Write_2_Byte(config, W5500_Socket_Register.Sn_PORT_0, W5500_Control_Register.Socket_0_Control, &data[0]);



	}
	else if(socket_config->client_server == W5500_Socket_Type.Server)
	{
		Write_1_Byte(config, W5500_Socket_Register.Sn_MR, W5500_Control_Register.Socket_0_Control, 0x20 | W5500_Socket_Type.Server);
	}
	else
	{
		return -1;
	}

	return 1;
}

int8_t W5500_Socket_UDP_Send_Packet(W5500_Config *config, W5500_Socket_Config *socket_config)
{
	// Check if the link is up
//	uint8_t Link;
//	Read_1_Byte(config, W5500_Common_Register.PHY_Configuration, W5500_Control_Register.Common_Register, &Link);
//	if(!(Link & 0x01)) return -1;

	// If link is UP, Open Socket
	counter = counter_reset;
	while(counter < counter_overflow)
	{
		uint8_t socket_response = 0x01;
		Write_1_Byte(config, W5500_Socket_Register.Sn_CR, W5500_Control_Register.Socket_0_Control, W5500_Socket_Commands.OPEN);
		Read_1_Byte(config, W5500_Socket_Register.Sn_SR, W5500_Control_Register.Socket_0_Control, &socket_response);
		if(socket_response == W5500_Socket_Status.SOCK_UDP) break;
		else{
			counter = counter_reset;
			Write_1_Byte(config, W5500_Socket_Register.Sn_CR, W5500_Control_Register.Socket_0_Control, W5500_Socket_Commands.CLOSE);
			while(counter < counter_overflow)
			{
				uint8_t socket_response = 0x01;
				Read_1_Byte(config, W5500_Socket_Register.Sn_SR, W5500_Control_Register.Socket_0_Control, &socket_response);
				if(socket_response == W5500_Socket_Status.SOCK_CLOSED) break;
				else{
					Write_1_Byte(config, W5500_Socket_Register.Sn_MR, W5500_Control_Register.Socket_0_Control, W5500_Socket_Mode.UDP);
				}
				counter ++;
				Delay_ms(10);
			}
//			 return -4;
		}
		counter ++;
		Delay_ms(10);
	}
	if(counter >= counter_overflow) return -2;


	// Send Data
	Write_1_Byte(config, W5500_Socket_Register.Sn_TX_WR_0, W5500_Control_Register.Socket_0_Control, socket_config->data_len >> 8);
	Write_1_Byte(config, W5500_Socket_Register.Sn_TX_WR_1, W5500_Control_Register.Socket_0_Control, socket_config->data_len);
	Write_Multiple_Bytes(config, 0x0000, W5500_Control_Register.Socket_0_TX_Buffer, socket_config->data, socket_config->data_len);

	counter = counter_reset;
	while(counter < counter_overflow)
	{
		uint8_t socket_response = 0x01;
		Write_1_Byte(config, W5500_Socket_Register.Sn_CR, W5500_Control_Register.Socket_0_Control, W5500_Socket_Commands.SEND);
		Read_1_Byte(config, W5500_Socket_Register.Sn_IR, W5500_Control_Register.Socket_0_Control, &socket_response);
		if(socket_response && 0x10) break;
		counter ++;
		Delay_ms(10);
	}
	if(counter >= counter_overflow) return -3;

	// Close Socket
	counter = counter_reset;
	Write_1_Byte(config, W5500_Socket_Register.Sn_CR, W5500_Control_Register.Socket_0_Control, W5500_Socket_Commands.CLOSE);
	while(counter < counter_overflow)
	{
		uint8_t socket_response = 0x01;
		Read_1_Byte(config, W5500_Socket_Register.Sn_SR, W5500_Control_Register.Socket_0_Control, &socket_response);
		if(socket_response == W5500_Socket_Status.SOCK_CLOSED) break;
		else{
			Write_1_Byte(config, W5500_Socket_Register.Sn_MR, W5500_Control_Register.Socket_0_Control, W5500_Socket_Mode.UDP);
		}
		counter ++;
		Delay_ms(10);
	}
	if(counter >= counter_overflow) return -4;

	return 1;

}

int8_t Send_Packet(W5500_Config *config, W5500_Socket_Config *socket_config)
{
	counter = counter_reset;
	Write_1_Byte(config, W5500_Socket_Register.Sn_MR, W5500_Control_Register.Socket_0_Control, W5500_Socket_Mode.UDP);
	while(counter < counter_overflow)
	{
		uint8_t socket_response = 0x01;

		Write_1_Byte(config, W5500_Socket_Register.Sn_CR, W5500_Control_Register.Socket_0_Control, 0x01);
		Read_1_Byte(config, W5500_Socket_Register.Sn_SR, W5500_Control_Register.Socket_0_Control, &socket_response);
		if(socket_response == W5500_Socket_Status.SOCK_UDP)
		{
			break;
		}
		counter ++;
		Delay_ms(10);
	}
	if(counter >= counter_overflow) return -1;

	// Set Destination IP
	Write_4_Byte(config, W5500_Socket_Register.Sn_DIPR0, W5500_Control_Register.Socket_0_Control, socket_config->Destination_IP_Address);
	// Set Destinaiton Port
	uint8_t data[2];
	data[0] = socket_config->Destination_Port >> 8;
	data[1] = socket_config->Destination_Port;
	Write_2_Byte(config, W5500_Socket_Register.Sn_DPORT0, W5500_Control_Register.Socket_0_Control, &data[0]);


	//Receiving Data:

	uint8_t RX_RD[2];
	uint16_t RX_RD_TOTAL;
	Read_1_Byte(config, W5500_Socket_Register.Sn_RX_RD_0, W5500_Control_Register.Socket_0_Control, &RX_RD[0]);
	Read_1_Byte(config, W5500_Socket_Register.Sn_RX_RD_1, W5500_Control_Register.Socket_0_Control, &RX_RD[1]);
	RX_RD_TOTAL = (RX_RD[1] << 8) | (RX_RD[0] << 0);

	uint8_t RX_RS[2];
	uint16_t RX_RS_TOTAL;
	Read_1_Byte(config, W5500_Socket_Register.Sn_RX_RSR_0, W5500_Control_Register.Socket_0_Control, &RX_RS[0]);
	Read_1_Byte(config, W5500_Socket_Register.Sn_RX_RSR_1, W5500_Control_Register.Socket_0_Control, &RX_RS[1]);
	RX_RS_TOTAL = (RX_RS[1] << 8) | (RX_RS[0] << 0);

	uint8_t RX_WR[2];
	uint16_t RX_WR_TOTAL;
	Read_1_Byte(config, W5500_Socket_Register.Sn_RX_WR_0, W5500_Control_Register.Socket_0_Control, &RX_WR[0]);
	Read_1_Byte(config, W5500_Socket_Register.Sn_RX_WR_1, W5500_Control_Register.Socket_0_Control, &RX_WR[1]);
	RX_WR_TOTAL = (RX_WR[1] << 8) | (RX_WR[0] << 0);

	Write_1_Byte(config, W5500_Socket_Register.Sn_CR, W5500_Control_Register.Socket_0_Control, W5500_Socket_Commands.RECV);


	// Send Data
	uint8_t FREE_SPACE_TX[2];
	uint16_t FREE_SPACE_TX_TOTAL;
	Read_1_Byte(config, W5500_Socket_Register.Sn_TX_FSR_0, W5500_Control_Register.Socket_0_Control, &FREE_SPACE_TX[0]);
	Read_1_Byte(config, W5500_Socket_Register.Sn_TX_FSR_1, W5500_Control_Register.Socket_0_Control, &FREE_SPACE_TX[1]);
	FREE_SPACE_TX_TOTAL = (FREE_SPACE_TX[1] << 8) | (FREE_SPACE_TX[0] << 0);

	uint8_t TX_RD[2];
	uint16_t TX_RD_TOTAL;
	Read_1_Byte(config, W5500_Socket_Register.Sn_TX_RD_0, W5500_Control_Register.Socket_0_Control, &TX_RD[0]);
	Read_1_Byte(config, W5500_Socket_Register.Sn_TX_RD_1, W5500_Control_Register.Socket_0_Control, &TX_RD[1]);
	TX_RD_TOTAL = (TX_RD[1] << 8) | (TX_RD[0] << 0);

	uint8_t TX_WR[2];
	uint16_t TX_WR_TOTAL;
	Read_1_Byte(config, W5500_Socket_Register.Sn_TX_WR_0, W5500_Control_Register.Socket_0_Control, &TX_WR[0]);
	Read_1_Byte(config, W5500_Socket_Register.Sn_TX_WR_1, W5500_Control_Register.Socket_0_Control, &TX_WR[1]);
	TX_WR_TOTAL = (TX_WR[1] << 8) | (TX_WR[0] << 0);





	Write_1_Byte(config, W5500_Socket_Register.Sn_TX_WR_0, W5500_Control_Register.Socket_0_Control,socket_config->data_len >> 8);
	Write_1_Byte(config, W5500_Socket_Register.Sn_TX_WR_1, W5500_Control_Register.Socket_0_Control, socket_config->data_len >> 0);
	Write_Multiple_Bytes(config, TX_WR_TOTAL, W5500_Control_Register.Socket_0_TX_Buffer, socket_config->data, socket_config->data_len);

	data[0] = (TX_WR_TOTAL + socket_config->data_len) >> 8;
	data[1] = TX_WR_TOTAL + socket_config->data_len;
	Write_2_Byte(config, W5500_Socket_Register.Sn_TX_WR_0, W5500_Control_Register.Socket_0_Control, &data[0]);

	counter = counter_reset;
	while(counter < counter_overflow)
	{
		uint8_t socket_response = 0x00;
		Write_1_Byte(config, W5500_Socket_Register.Sn_CR, W5500_Control_Register.Socket_0_Control, W5500_Socket_Commands.SEND);
		Recv_Packet(config, socket_config);
		Read_1_Byte(config, W5500_Socket_Register.Sn_SR, W5500_Control_Register.Socket_0_Control, &socket_response);
		Read_1_Byte(config, W5500_Socket_Register.Sn_IR, W5500_Control_Register.Socket_0_Control, &socket_response);
		if(socket_response && 0x10)
		{
			break;
		}
		counter ++;
		Delay_ms(10);
	}
	if(counter >= counter_overflow) return -2;

	// Close Socket
	counter = counter_reset;
	Write_1_Byte(config, W5500_Socket_Register.Sn_CR, W5500_Control_Register.Socket_0_Control, W5500_Socket_Commands.CLOSE);
	while(counter < counter_overflow)
	{
		uint8_t socket_response = 0x01;
		Read_1_Byte(config, W5500_Socket_Register.Sn_SR, W5500_Control_Register.Socket_0_Control, &socket_response);
		if(socket_response == W5500_Socket_Status.SOCK_CLOSED)
		{
			break;
		}
		counter ++;
		Delay_ms(10);
	}
	if(counter >= counter_overflow) {
		return -3;
	}

	return 1;
}

//
//void Recv_Packet(W5500_Config *config, W5500_Socket_Config *socket_config)
//{
//	//Receiving Data:
//
//	uint8_t RX_RD[2];
//	uint16_t RX_RD_TOTAL;
//	Read_1_Byte(config, W5500_Socket_Register.Sn_RX_RD_0, W5500_Control_Register.Socket_0_Control, &RX_RD[0]);
//	Read_1_Byte(config, W5500_Socket_Register.Sn_RX_RD_1, W5500_Control_Register.Socket_0_Control, &RX_RD[1]);
//	RX_RD_TOTAL = (RX_RD[1] << 8) | (RX_RD[0] << 0);
//
//	uint8_t RX_RS[2];
//	uint16_t RX_RS_TOTAL;
//	Read_1_Byte(config, W5500_Socket_Register.Sn_RX_RSR_0, W5500_Control_Register.Socket_0_Control, &RX_RS[0]);
//	Read_1_Byte(config, W5500_Socket_Register.Sn_RX_RSR_1, W5500_Control_Register.Socket_0_Control, &RX_RS[1]);
//	RX_RS_TOTAL = (RX_RS[1] << 8) | (RX_RS[0] << 0);
//
//	uint8_t RX_WR[2];
//	uint16_t RX_WR_TOTAL;
//	Read_1_Byte(config, W5500_Socket_Register.Sn_RX_WR_0, W5500_Control_Register.Socket_0_Control, &RX_WR[0]);
//	Read_1_Byte(config, W5500_Socket_Register.Sn_RX_WR_1, W5500_Control_Register.Socket_0_Control, &RX_WR[1]);
//	RX_WR_TOTAL = (RX_WR[1] << 8) | (RX_WR[0] << 0);
//
//
//	uint8_t rdata[500];
//	Read_Multiple_Bytes(config, RX_RD_TOTAL, W5500_Control_Register.Socket_0_RX_Buffer, &rdata[0], 500);
//
//
//
//
//	Write_1_Byte(config, W5500_Socket_Register.Sn_CR, W5500_Control_Register.Socket_0_Control, W5500_Socket_Commands.RECV);
//
//}
//
