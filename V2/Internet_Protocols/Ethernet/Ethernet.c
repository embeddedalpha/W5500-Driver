/*
 * Ethernet.c
 *
 *  Created on: Oct 21, 2024
 *      Author: kunal
 */


#include "IPv4.h"


uint8_t *Eth_Packet_Assemble(Ethernet_Frame_Type *frame, char *buffer,
                             uint16_t *len) {

  static uint8_t frame_buffer[ETH_FRAME_LEN];
  uint16_t buff_len = *len;
  uint16_t final_buff_len = ETH_Header_Length + buff_len;

  memcpy(&frame->payload[0], buffer, (uint16_t)buff_len);
  memcpy(frame_buffer, frame, final_buff_len);

  *len = final_buff_len;

  return frame_buffer; // Return the pointer to the buffer
}
