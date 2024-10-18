/*
 * W5500_UDP.c
 *
 *  Created on: Jan 14, 2024
 *      Author: kunal
 */

#include "W5500.h"
#include "W5500_LL.h"
#include "W5500_HAL.h"

int counter_reset_udp = 0;
int counter_udp = 0;
int counter_overflow_udp = 1000;

int8_t W5500_UDP_Socket_Open(W5500_Config *config, W5500_Socket_Config *socket_config)
{
	counter_udp = counter_reset_udp;

	uint8_t data[2];
	data[0] = config->Source_Port >> 8;
	data[1] = config->Source_Port;

	Write_1_Byte(config, W5500_Socket_Register.Sn_MR, W5500_Control_Register.Socket_0_Control, W5500_Socket_Mode.UDP);
	Write_2_Byte(config, W5500_Socket_Register.Sn_PORT_0, W5500_Control_Register.Socket_0_Control, &data[0]);

	Write_1_Byte(config, W5500_Socket_Register.Sn_MR, W5500_Control_Register.Socket_0_Control, W5500_Socket_Mode.UDP);
	while(counter_udp < counter_overflow_udp)
	{
		uint8_t socket_response = 0x01;

		Write_1_Byte(config, W5500_Socket_Register.Sn_CR, W5500_Control_Register.Socket_0_Control, 0x01);
		Read_1_Byte(config, W5500_Socket_Register.Sn_SR, W5500_Control_Register.Socket_0_Control, &socket_response);
		if(socket_response == W5500_Socket_Status.SOCK_UDP)
		{
			break;
		}
		counter_udp ++;
		Delay_ms(10);
	}
	if(counter_udp >= counter_overflow_udp){
		return -1;
	}

		// Set Destination IP
		Write_4_Byte(config, W5500_Socket_Register.Sn_DIPR0, W5500_Control_Register.Socket_0_Control, socket_config->Destination_IP_Address);
		// Set Destinaiton Port
		data[0] = socket_config->Destination_Port >> 8;
		data[1] = socket_config->Destination_Port;
		Write_2_Byte(config, W5500_Socket_Register.Sn_DPORT0, W5500_Control_Register.Socket_0_Control, &data[0]);
		return 1;

}

int8_t W5500_UDP_Socket_Send_Packet(W5500_Config *config, W5500_Socket_Config *socket_config)
{
	uint8_t FREE_SPACE_TX[2],data[2];
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
	Write_Multiple_Bytes(config, TX_WR_TOTAL, W5500_Control_Register.Socket_0_TX_Buffer, &socket_config->data[0], socket_config->data_len);

	data[0] = (TX_WR_TOTAL + socket_config->data_len) >> 8;
	data[1] = TX_WR_TOTAL + socket_config->data_len;
	Write_2_Byte(config, W5500_Socket_Register.Sn_TX_WR_0, W5500_Control_Register.Socket_0_Control, &data[0]);

	return 2;
}

int8_t W5500_UDP_Socket_Get_Packet(W5500_Config *config, W5500_Socket_Config *socket_config, uint8_t *IP_Address[4], uint16_t *Port , uint8_t *Payload, uint8_t *Payload_Length)
{
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

	counter_udp = counter_reset_udp;
	while(counter_udp < (counter_overflow_udp))
	{
		uint8_t RX_WR[2];
		uint16_t RX_WR_TOTAL;
		Read_1_Byte(config, W5500_Socket_Register.Sn_RX_WR_0, W5500_Control_Register.Socket_0_Control, &RX_WR[0]);
		Read_1_Byte(config, W5500_Socket_Register.Sn_RX_WR_1, W5500_Control_Register.Socket_0_Control, &RX_WR[1]);
		RX_WR_TOTAL = (RX_WR[1] << 8) | (RX_WR[0] << 0);
		if(RX_WR_TOTAL > 0x00)
		{
			break;
		}
		Delay_ms(10);
	}
	if(counter_udp >= counter_overflow_udp) return -3;

	uint8_t rdata[500];
	Read_Multiple_Bytes(config, RX_RD_TOTAL, W5500_Control_Register.Socket_0_RX_Buffer, &rdata[0], 500);


	for(int i = 0; i < 4; i++)
	{
		*IP_Address[i] = rdata[i];
	}

	*Port = (rdata[4] << 8) | rdata[5];

	*Payload_Length = (rdata[6] << 8) | rdata[7];

	for(int i = 0; i < *Payload_Length; i++)
	{
		Payload[i] = rdata[8+i];
	}

//	Read_Buffer(config, 0x0000, socket_config->data[0], 100);
	Write_1_Byte(config, W5500_Socket_Register.Sn_CR, W5500_Control_Register.Socket_0_Control, W5500_Socket_Commands.RECV);
	return 3;
}

int8_t W5500_UDP_Socket_Close(W5500_Config *config, W5500_Socket_Config *socket_config)
{
	// Close Socket
	counter_udp = counter_reset_udp;
	Write_1_Byte(config, W5500_Socket_Register.Sn_CR, W5500_Control_Register.Socket_0_Control, W5500_Socket_Commands.CLOSE);
	while(counter_udp < counter_overflow_udp)
	{
		uint8_t socket_response = 0x01;
		Read_1_Byte(config, W5500_Socket_Register.Sn_SR, W5500_Control_Register.Socket_0_Control, &socket_response);
		if(socket_response == W5500_Socket_Status.SOCK_CLOSED)
		{
			break;
		}
		counter_udp ++;
		Delay_ms(10);
	}
	if(counter_udp >= counter_overflow_udp) {
		return -3;
	}
		return 3;
}
