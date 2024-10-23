/*
 * IPv4.c
 *
 *  Created on: Oct 21, 2024
 *      Author: kunal
 */


#include "IPv4.h"

uint8_t *IPv4_Packet_Assemble(IPv4_Frame_Type *frame, uint8_t *buffer,
                              uint16_t *len) {

  static uint8_t frame_buffer[IPv4_Frame_Max_Len];
  uint16_t buff_len = *len;

  uint16_t final_buff_len = IPv4_Header_Length + buff_len;

  frame->Version_IHL = 0x45;
  frame->DSCP_ECN = 0x00;
  frame->Total_Length = swap_bytes(final_buff_len);
  frame->Identification = swap_bytes(0x0000);
  frame->Flags_Fragment_Offset = 0x00;
  frame->Time_to_Live = 0x40;
  frame->Protocol = 0x11;
  frame->Header_Checksum = swap_bytes(0x0000);

  memcpy(&frame->data[0], buffer, (uint16_t)buff_len);

  memcpy(frame_buffer, frame, final_buff_len);

  *len = final_buff_len;

  return frame_buffer; // Return the pointer to the buffer
}

void Add_IP_CRC(uint8_t *buffer, uint16_t len) {

  uint32_t f2 = 0;

  uint16_t ip_header[10];
  ip_header[0] = buffer[14] << 8 | buffer[15]; // Version, IHL
  ip_header[1] = buffer[16] << 8 | buffer[17]; // TOS, Total Length
  ip_header[2] = buffer[18] << 8 | buffer[19]; // Identification
  ip_header[3] = buffer[20] << 8 | buffer[21];
  ip_header[4] = buffer[22] << 8 | buffer[23];
  ip_header[5] = buffer[24] << 8 | buffer[25];
  ip_header[6] = buffer[26] << 8 | buffer[27]; // Source_IP 2 bytes
  ip_header[7] = buffer[28] << 8 | buffer[29]; // Source_IP 2 bytes
  ip_header[8] = buffer[30] << 8 | buffer[31]; // Destination_IP 2 bytes
  ip_header[9] = buffer[32] << 8 | buffer[33]; // Destination_IP 2 bytes

  // uint16_t ip_checksum = calculate_checksum(ip_header, 10);

  for (int i = 0; i < 10; i++) {
    f2 += ip_header[i];
  }

  uint16_t final_checksum = ~(((f2 & 0xfffF0000) >> 16) + (f2 & 0x0000FFFF));

//  printf("IP correct = %x \n", final_checksum);

  buffer[24] = (final_checksum & 0xFF00) >> 8;
  buffer[25] = (final_checksum & 0x00FF) >> 0;
}
