/*
 * W5500_Defs.h
 *
 *  Created on: Nov 14, 2023
 *      Author: kunal
 */

#ifndef W5500_DEFS_H_
#define W5500_DEFS_H_

#include "main.h"

#define W5500_DEBUG_FLAG 0


static const struct W5500_Control_Register
{
	uint8_t Common_Register;
	uint8_t Socket_0_Control;
	uint8_t Socket_0_TX_Buffer;
	uint8_t Socket_0_RX_Buffer;

	uint8_t Socket_1_Control;
	uint8_t Socket_1_TX_Buffer;
	uint8_t Socket_1_RX_Buffer;

	uint8_t Socket_2_Control;
	uint8_t Socket_2_TX_Buffer;
	uint8_t Socket_2_RX_Buffer;

	uint8_t Socket_3_Control;
	uint8_t Socket_3_TX_Buffer;
	uint8_t Socket_3_RX_Buffer;

	uint8_t Socket_4_Control;
	uint8_t Socket_4_TX_Buffer;
	uint8_t Socket_4_RX_Buffer;

	uint8_t Socket_5_Control;
	uint8_t Socket_5_TX_Buffer;
	uint8_t Socket_5_RX_Buffer;

	uint8_t Socket_6_Control;
	uint8_t Socket_6_TX_Buffer;
	uint8_t Socket_6_RX_Buffer;

	uint8_t Socket_7_Control;
	uint8_t Socket_7_TX_Buffer;
	uint8_t Socket_7_RX_Buffer;

}W5500_Control_Register = {0,
						  1,2,3,
		                  5,6,7,
						  9,10,11,
						  13,14,15,
						  17,18,19,
						  21,22,23,
						  25,26,27,
						  29,30,31
};


static const struct W5500_Common_Register
{
	uint16_t Mode;

	uint16_t Gateway_Address_0;
	uint16_t Gateway_Address_1;
	uint16_t Gateway_Address_2;
	uint16_t Gateway_Address_3;

	uint16_t Subnet_Mask_Address_0;
	uint16_t Subnet_Mask_Address_1;
	uint16_t Subnet_Mask_Address_2;
	uint16_t Subnet_Mask_Address_3;

	uint16_t Source_Hardware_Address_0;
	uint16_t Source_Hardware_Address_1;
	uint16_t Source_Hardware_Address_2;
	uint16_t Source_Hardware_Address_3;
	uint16_t Source_Hardware_Address_4;
	uint16_t Source_Hardware_Address_5;

	uint16_t Source_IP_Address_0;
	uint16_t Source_IP_Address_1;
	uint16_t Source_IP_Address_2;
	uint16_t Source_IP_Address_3;

	uint16_t Interrupt_Low_Level_Timer_0;
	uint16_t Interrupt_Low_Level_Timer_1;

	uint16_t Interrupt;

	uint16_t Interrupt_Mask;

	uint16_t Socket_Interrupt;

	uint16_t Socket_Interrupt_Mask;

	uint16_t Retry_Time_0;
	uint16_t Retry_Time_1;

	uint16_t Retry_Count ;

	uint16_t PPP_LCP_Request_Timer;

	uint16_t PPP_LCP_Magic_number;

	uint16_t PPP_Destination_MAC_Address_0;
	uint16_t PPP_Destination_MAC_Address_1;
	uint16_t PPP_Destination_MAC_Address_2;
	uint16_t PPP_Destination_MAC_Address_3;
	uint16_t PPP_Destination_MAC_Address_4;
	uint16_t PPP_Destination_MAC_Address_5;

	uint16_t PPP_Session_Identification_0;
	uint16_t PPP_Session_Identification_1;

	uint16_t PPP_Maximum_Segment_Size_0;
	uint16_t PPP_Maximum_Segment_Size_1;

	uint16_t Unreachable_IP_address_0;
	uint16_t Unreachable_IP_address_1;
	uint16_t Unreachable_IP_address_2;
	uint16_t Unreachable_IP_address_3;

	uint16_t Unreachable_Port_0;
	uint16_t Unreachable_Port_1;

	uint16_t PHY_Configuration;

	uint16_t Chip_Version;

}W5500_Common_Register = {	0x0000,
							0x0001, 0x0002, 0x0003, 0x0004,
							0x0005,	0x0006, 0x0007, 0x0008,
							0x0009,	0x000A, 0x000B,	0x000C, 0x000D, 0x000E,
							0x000F, 0x0010, 0x0011, 0x0012,
							0x0013, 0x0014,
							0x0015,
							0x0016,
							0x0017,
							0x0018,
							0x0019, 0x001A,
							0x001B,
							0x001C, 0x001D,
							0x001E, 0x001F, 0x0020, 0x0021, 0x0022, 0x0023,
							0x0024, 0x0025,
							0x0026, 0x0027,
							0x0028, 0x0029, 0x002A, 0x002B,
							0x002C, 0x002D,
							0x002E, 0x0039,

						 };


static const struct W5500_Socket_Register
{
	uint16_t Sn_MR;

	uint16_t Sn_CR;
	uint16_t Sn_IR;
	uint16_t Sn_SR;

	uint16_t Sn_PORT_0;
	uint16_t Sn_PORT_1;

	uint16_t Sn_DHAR0;
	uint16_t Sn_DHAR1;
	uint16_t Sn_DHAR2;
	uint16_t Sn_DHAR3;
	uint16_t Sn_DHAR4;
	uint16_t Sn_DHAR5;

	uint16_t Sn_DIPR0;
	uint16_t Sn_DIPR1;
	uint16_t Sn_DIPR2;
	uint16_t Sn_DIPR3;

	uint16_t Sn_DPORT0;
	uint16_t Sn_DPORT1;

	uint16_t Sn_MSSR0;
	uint16_t Sn_MSSR1;

	uint16_t Sn_TOS;

	uint16_t Sn_TTL;

	uint16_t Sn_RXBUF_SIZE;

	uint16_t Sn_TXBUF_SIZE;

	uint16_t Sn_TX_FSR_0;
	uint16_t Sn_TX_FSR_1;

	uint16_t Sn_TX_RD_0;
	uint16_t Sn_TX_RD_1;

	uint16_t Sn_TX_WR_0;
	uint16_t Sn_TX_WR_1;

	uint16_t Sn_RX_RSR_0;
	uint16_t Sn_RX_RSR_1;

	uint16_t Sn_RX_RD_0;
	uint16_t Sn_RX_RD_1;

	uint16_t Sn_RX_WR_0;
	uint16_t Sn_RX_WR_1;

	uint16_t Sn_IMR;

	uint16_t Sn_FRAG_0;
	uint16_t Sn_FRAG_1;

	uint16_t Sn_KPALVTR;


}W5500_Socket_Register = {	0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005,
							0x0006, 0x0007, 0x0008, 0x0009, 0x000A, 0x000B,
							0x000C, 0x000D, 0x000E, 0x000F, 0x0010, 0x0011,
							0x0012, 0x0013, 0x0015, 0x0016,
							0x001E, 0x001F, 0x0020, 0x0021, 0x0022, 0x0023,
							0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029,
							0x002A, 0x002B, 0x002C, 0x002D, 0x002E, 0x0039
						 };


static const struct W5500_Socket_Mode
{
	uint8_t Closed;
	uint8_t TCP;
	uint8_t UDP;
	uint8_t MACRAW;
}W5500_Socket_Mode = {0,1,2,4};

static const struct W5500_Socket_Commands
{
	uint8_t OPEN;
	uint8_t LISTEN;
	uint8_t CONNECT;
	uint8_t DISCON;
	uint8_t CLOSE;
	uint8_t SEND;
	uint8_t SEND_MAC;
	uint8_t SEND_KEEP;
	uint8_t RECV;
}W5500_Socket_Commands = {1,2,4,8,0x10,0x20,0x21,0x22,0x40};

static const struct W5500_Socket_Status
{
	uint8_t SOCK_CLOSED;
	uint8_t SOCK_INIT;
	uint8_t SOCK_LISTEN;
	uint8_t SOCK_ESTABLISHED;
	uint8_t SOCK_CLOSE_WAIT;
	uint8_t SOCK_UDP;
	uint8_t SOCK_MACRAW;
	uint8_t SOCK_SYNSENT;
	uint8_t SOCK_SYNRECV;
	uint8_t SOCK_FIN_WAIT;
	uint8_t SOCK_CLOSING;
	uint8_t SOCK_TIME_WAIT;
	uint8_t SOCK_LAST_ACK;
}W5500_Socket_Status = {0x00,0x13,0x14,0x17,0x1C,0x22,0x42,0x15,0x16,0x18,0x1A,0x1B,0x1D};

static const struct W5500_Hardware_Socket
{
	uint8_t Socket_1;
	uint8_t Socket_2;
	uint8_t Socket_3;
	uint8_t Socket_4;
	uint8_t Socket_5;
	uint8_t Socket_6;
	uint8_t Socket_7;
}W5500_Hardware_Socket = {1,2,3,4,5,6,7};

static const struct W5500_Socket_Type
{
	uint8_t Client;
	uint8_t Server;
}W5500_Socket_Type = {1,2};


#endif /* W5500_DEFS_H_ */
