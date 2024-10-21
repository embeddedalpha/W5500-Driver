


#include "IPv4.h"
#include "stdio.h"

uint8_t *UDP_Packet_Assemble(UDP_Frame_Type *frame, char *buffer,
                             uint16_t *len) {

  static uint8_t frame_buffer[UDP_Frame_Max_Len];
  uint16_t buff_len = *len;
  uint16_t final_buff_len = UDP_Header_Length + buff_len;


  frame->Checksum = swap_bytes(0x0000);
  frame->Length = swap_bytes(final_buff_len);
  memcpy(&frame->data[0], buffer, (uint16_t)buff_len); //replace with dma
  memcpy(frame_buffer, frame, final_buff_len);

  *len = final_buff_len;

  return frame_buffer; // Return the pointer to the buffer
}
