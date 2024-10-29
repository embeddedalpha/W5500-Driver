/*
 * W5500_MWL_Defs.h
 *
 *  Created on: Oct 18, 2024
 *      Author: ksalvi
 */

#ifndef W5500_MIDDLEWARE_W5500_MWL_DEFS_H_
#define W5500_MIDDLEWARE_W5500_MWL_DEFS_H_

#define W5500_COMMAND_SOCKET_OPEN		0x01
#define W5500_COMMAND_SOCKET_LISTEN		0x02
#define W5500_COMMAND_SOCKET_CONNECT 	0x04
#define W5500_COMMAND_SOCKET_DISCO		0x08
#define W5500_COMMAND_SOCKET_CLOSE		0x10
#define W5500_COMMAND_SOCKET_SEND		0x20
#define W5500_COMMAND_SOCKET_SEND_MAC	0x21
#define W5500_COMMAND_SOCKET_SEND_KEEP	0x22
#define W5500_COMMAND_SOCKET_RECV		0x40

#define W5500_STATUS_SOCK_CLOSED		0x00
#define W5500_STATUS_SOCK_INIT			0x13
#define W5500_STATUS_SOCK_LISTEN		0x14
#define W5500_STATUS_SOCK_ESTABLISHED	0x17
#define W5500_STATUS_SOCK_CLOSE_WAIT	0x1c
#define W5500_STATUS_SOCK_UDP			0x22
#define W5500_STATUS_SOCK_MACRAW		0x42
#define W5500_STATUS_SOCK_SYNSENT		0x15
#define W5500_STATUS_SOCK_SYNRECV		0x16
#define W5500_STATUS_SOCK_FIN_WAIT		0x18
#define W5500_STATUS_SOCK_CLOSING		0x1a
#define W5500_STATUS_SOCK_TIME_WAIT		0x1b
#define W5500_STATUS_SOCK_LAST_ACK		0x1d


typedef struct __W5500_Mode__
{
	uint8_t Speed_10BT_Half_Duplex_Auto_Negotiation_Disabled;
	uint8_t Speed_10BT_Full_Duplex_Auto_Negotiation_Disabled;
	uint8_t Speed_100BT_Half_Duplex_Auto_Negotiation_Disabled;
	uint8_t Speed_100BT_Full_Duplex_Auto_Negotiation_Disabled;
	uint8_t Speed_100BT_Half_Duplex_Auto_Negotiation_Enabled;
	uint8_t Power_Down_Mode;
	uint8_t All_Capable_Auto_Negotiation_Enabled;
}__W5500_Mode__;


typedef struct __W5500_IP_Type__
{
	uint8_t Static;
	uint8_t Dynamic;
}__W5500_IP_Type__;


typedef struct __W5500_Socket_Config__
{
	struct Mode{
		uint8_t Closed;
		uint8_t TCP;
		uint8_t UDP;
		uint8_t MACRAW;
	}Mode;

	struct Buffer_Size{
		uint8_t Size_0KB;
		uint8_t Size_1KB;
		uint8_t Size_2KB;
		uint8_t Size_4KB;
		uint8_t Size_8KB;
		uint8_t Size_16KB;
	}Buffer_Size;

}__W5500_Socket_Configs__;


static const struct W5500_Configuration
{

	__W5500_Mode__ Mode;
	__W5500_IP_Type__ IP_Type;
	__W5500_Socket_Configs__ Socket_Config;
}W5500_Configuration;

#endif /* W5500_MIDDLEWARE_W5500_MWL_DEFS_H_ */
