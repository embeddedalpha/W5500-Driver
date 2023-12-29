/*
 * DHCP.c
 *
 *  Created on: Dec 19, 2023
 *      Author: kunal
 *
 *
 */


// Ethernet Frame:
// --------------------------------------------------------------------
// | Destination MAC | Source MAC | EtherType (IPv4) | IP Header... |
// --------------------------------------------------------------------
//
// IP Header (inside Ethernet frame):
// --------------------------------------------------------------------
// | Version | IHL | DSCP | ECN | Total Length | Identification | ... |
// --------------------------------------------------------------------
//
// UDP Header (inside IP packet):
// --------------------------------------------------------------------
// | Source Port | Destination Port | Length | Checksum | DHCP Payload |
// --------------------------------------------------------------------
//
// DHCP Payload (inside UDP packet):
// --------------------------------------------------------------------
// | Op Code | HTYPE | HLEN | HOPS | Transaction ID | Seconds | Flags | ... |
// --------------------------------------------------------------------
// | Client IP Address | Your IP Address | Next Server IP | Relay Agent IP | ... |
// --------------------------------------------------------------------
// | Client Hardware Address | Server Host Name | Boot Filename | Options... |
// --------------------------------------------------------------------



#include "DHCP.h"

//ment to be used as a client
#define DHCP_Client_Port 68
#define DHCP_Server_Port 67

static const struct DHCP_Defs
{
	uint8_t OP_Request;
	uint8_t OP_Reply;
	uint8_t HTYPE_Ethernet;
	uint8_t HLEN_Hardware_Address_Length;
	uint8_t HOPS_Default;


}DHCP_Defs = {1,2,1,6,0};

struct DHCP_Frame
{
	uint8_t OP_Code;
	uint8_t HTYPE;
	uint8_t HLEN;
	uint8_t HOPS;
	uint8_t Transaction_ID[4];
	uint8_t Seconds[2];
	uint8_t Flags[2];
	uint8_t Client_IP_Address[4];

}DHCP_Frame;



/*
 * Packet Structure:
 * 1. UDP Header:
 * Source Port: 67 (DHCP server) or 68 (DHCP client)
 * Destination Port: 67 (DHCP server) or 68 (DHCP client)
 *
 *
 */
