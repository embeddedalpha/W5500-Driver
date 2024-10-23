


#include "IPv4.h"
#include "stdio.h"

uint8_t *UDP_Packet_Assemble(UDP_Frame_Type *frame, char *buffer,
                             uint16_t *len) {

  static uint8_t frame_buffer[UDP_Frame_Max_Len];
  uint16_t buff_len = *len;
  uint16_t final_buff_len = UDP_Header_Length + buff_len;

  frame->Checksum = swap_bytes(0x0000);
  frame->Length = swap_bytes(final_buff_len);
  memcpy(&frame->data[0], buffer, (uint16_t)buff_len);
  memcpy(frame_buffer, frame, final_buff_len);

  *len = final_buff_len;

  return frame_buffer; // Return the pointer to the buffer
}

void Add_UDP_CRC(uint8_t *buffer, uint16_t len) {

  uint16_t Pseudo_Header[6];
  uint16_t UDP_Segment[4];

  Pseudo_Header[0] = buffer[26] << 8 | buffer[27]; // Source_IP 2 bytes
  Pseudo_Header[1] = buffer[28] << 8 | buffer[29]; // Source_IP 2 bytes
  Pseudo_Header[2] = buffer[30] << 8 | buffer[31]; // Destination_IP 2 bytes
  Pseudo_Header[3] = buffer[32] << 8 | buffer[33]; // Destination_IP 2 bytes
  Pseudo_Header[4] = 0x00 << 8 | buffer[23];       // Protocol 1 byte
  Pseudo_Header[5] = buffer[38] << 8 | buffer[39]; // UDP Length 2 bytes

  UDP_Segment[0] = buffer[34] << 8 | buffer[35];
  UDP_Segment[1] = buffer[36] << 8 | buffer[37];
  UDP_Segment[2] = buffer[38] << 8 | buffer[39];
  UDP_Segment[3] = buffer[40] << 8 | buffer[41];

  uint16_t length = UDP_Segment[2] - 8;
  //printf("buffer length = %d\n", length);

  uint32_t f1 = Pseudo_Header[0] + Pseudo_Header[1] + Pseudo_Header[2] +
                Pseudo_Header[3] + Pseudo_Header[4] + Pseudo_Header[5];
  //printf("Pseudo Header CRC sum  = %x \n", f1);

  uint32_t f2 =
      UDP_Segment[0] + UDP_Segment[1] + UDP_Segment[2] + UDP_Segment[3];
  //printf("UDP Header CRC sum  = %x \n", f2);

  uint32_t f3 = 0;

  for (int i = 0; i < length; i += 2) {
    uint32_t word;
    if (i + 1 < length) {
      // Combine two bytes into a 16-bit word
      word = (buffer[42+i] << 8) + buffer[42+i + 1];
    } else {
      // If the length is odd, pad the last byte with 0x00
      word = (buffer[42+i] << 8) + 0x00;
    }

    f3 += word;
  }
  //printf("UDP payload CRC sum  = %x \n", f3);


  uint32_t final_checksum = ((f1 + f2 + f3));

  uint32_t final_checksum_1 = (final_checksum & 0xFFFF0000) >> 16;
  uint32_t final_checksum_2 = final_checksum & 0x0000FFFF;

  uint16_t Final_checksum = ~(final_checksum_1 + final_checksum_2);

  //printf("Final CRC sum = %x \n", Final_checksum);

  buffer[40] = (Final_checksum & 0xFF00) >> 8;
  buffer[41] = (Final_checksum & 0x00FF) >> 0;
}
