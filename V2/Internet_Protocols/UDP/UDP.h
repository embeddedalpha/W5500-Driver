/*
 * UDP.h
 *
 *  Created on: Oct 21, 2024
 *      Author: ksalvi
 */

#ifndef UDP_UDP_H_
#define UDP_UDP_H_

#include "main.h"

#define UDP_Data_Packet_Length 1500-20-8


typedef struct UDP_Header_Format{

	uint8_t Source_Port[2];
	uint8_t Destination_Port[2];
	uint8_t Length[2];
	uint8_t Checksum[2];
	uint8_t *data[UDP_Data_Packet_Length];
}__attribute__((__packed__))UDP_Header_Format;

void UDP_Send_Packet(UDP_Header_Format *header, uint8_t *packet, uint8_t length);
void UDP_Get_Packet(UDP_Header_Format *header, uint8_t *packet, uint8_t length);

#endif /* UDP_UDP_H_ */
