/*
 * W5500.h
 *
 *  Created on: Oct 17, 2024
 *      Author: kunal
 */

#ifndef MIDDLEWARE_W5500_H_
#define MIDDLEWARE_W5500_H_

#include "Low_Level/W5500_Low_Level.h"
#include "HAL/W5500_HAL.h"
#include "W5500_Defs.h"

bool W5500_Link_UP_Down;

typedef struct W5500_Socket_Config
{
	uint8_t Hardware_Socket_Number;
	uint8_t client_server;
	uint8_t Mode;
	uint8_t *Destination_Hardware_Address;
	uint8_t *Destination_IP_Address;
	uint16_t Destination_Port;
	uint8_t *data;
	uint16_t data_len;
}W5500_Socket_Config;

typedef struct W5500_Config
{
	 SPI_Config SPI;
	 uint8_t *Gateway_Address;
	 uint8_t *Subnet_Mask_Address;
	 uint8_t *Source_Hardware_Address;
	 uint16_t Source_Port;
	 uint8_t *Source_IP_Address;
}W5500_Config;

int W5500_Init(W5500_Config *config);



int8_t W5500_MACRAW_Socket_Open(W5500_Config *config, uint8_t Socket_Number);
int8_t W5500_MACRAW_Socket_Set_Packet(W5500_Config *config, uint8_t Socket_Number, uint8_t *buffer, uint16_t length);
int8_t W5500_MACRAW_Socket_Get_Packet(W5500_Config *config, uint8_t Socket_Number, uint8_t *buffer, uint16_t *length);
int8_t W5500_MACRAW_Socket_Close(W5500_Config *config, uint8_t Socket_Number);



int8_t W5500_TCP_Socket_Open(W5500_Config *config, W5500_Socket_Config *socket_config);
int8_t W5500_TCP_Socket_Get_Packet(W5500_Config *config, W5500_Socket_Config *socket_config, uint8_t *IP_Address[4], uint16_t *Port , uint8_t *Payload, uint8_t *Payload_Length);
int8_t W5500_TCP_Socket_Send_Packet(W5500_Config *config, W5500_Socket_Config *socket_config);
int8_t W5500_TCP_Socket_Close(W5500_Config *config, W5500_Socket_Config *socket_config);


int8_t W5500_UDP_Socket_Open(W5500_Config *config, W5500_Socket_Config *socket_config);
int8_t W5500_UDP_Socket_Send_Packet(W5500_Config *config, W5500_Socket_Config *socket_config);
int8_t W5500_UDP_Socket_Close(W5500_Config *config, W5500_Socket_Config *socket_config);
int8_t W5500_UDP_Socket_Get_Packet(W5500_Config *config, W5500_Socket_Config *socket_config, uint8_t *IP_Address[4], uint16_t *Port , uint8_t *Payload, uint8_t *Payload_Length);



#endif /* MIDDLEWARE_W5500_H_ */
