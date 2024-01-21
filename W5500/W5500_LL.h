/*
 * W5500_LL.h
 *
 *  Created on: Nov 15, 2023
 *      Author: kunal
 */

#ifndef W5500_LL_H_
#define W5500_LL_H_

#include "W5500.h"

void Write_2_Byte(W5500_Config *config,uint16_t offset, uint8_t control_register, uint8_t data[2]);
void Write_4_Byte(W5500_Config *config,uint16_t offset, uint8_t control_register, uint8_t data[4]);
void Write_1_Byte(W5500_Config *config,uint16_t offset, uint8_t control_register, uint8_t data);
void Write_Multiple_Bytes(W5500_Config *config,uint16_t offset, uint8_t control_register, uint8_t *data, uint16_t length);

void Read_1_Byte(W5500_Config *config,uint16_t offset, uint8_t control_register, uint8_t *data);
void Read_2_Byte(W5500_Config *config,uint16_t offset, uint8_t control_register, uint8_t *data);
void Read_4_Byte(W5500_Config *config,uint16_t offset, uint8_t control_register, uint8_t *data1,uint8_t *data2,uint8_t *data3,uint8_t *data4);
void Read_Multiple_Bytes(W5500_Config *config,uint16_t offset, uint8_t control_register, uint8_t *data, uint16_t length);
void Read_Buffer(W5500_Config *config,uint16_t address, uint8_t *data, uint16_t length);


#endif /* W5500_LL_H_ */

