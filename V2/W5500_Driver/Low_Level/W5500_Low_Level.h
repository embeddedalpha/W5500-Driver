/*
 * W5500_Low_Level.h
 *
 *  Created on: Oct 17, 2024
 *      Author: kunal
 */

#ifndef W5500_LOW_LEVEL_H_
#define W5500_LOW_LEVEL_H_

#include "main.h"
#include "SPI/SPI.h"
#include "HAL/W5500_HAL.h"
#include "Middleware/W5500.h"


void Write_2_Byte(W5500_Config *config,uint16_t offset, uint8_t control_register, uint8_t data[2]);
void Write_4_Byte(W5500_Config *config,uint16_t offset, uint8_t control_register, uint8_t data[4]);
void Write_1_Byte(W5500_Config *config,uint16_t offset, uint8_t control_register, uint8_t data);
void Write_Multiple_Bytes(W5500_Config *config,uint16_t offset, uint8_t control_register, uint8_t *data, uint16_t length);

void Read_1_Byte(W5500_Config *config,uint16_t offset, uint8_t control_register, uint8_t *data);
void Read_2_Byte(W5500_Config *config,uint16_t offset, uint8_t control_register, uint8_t *data[]);
void Read_4_Byte(W5500_Config *config,uint16_t offset, uint8_t control_register, uint8_t *data[]);
void Read_Multiple_Bytes(W5500_Config *config,uint16_t offset, uint8_t control_register, uint8_t *data, uint16_t length);

void Read_Buffer(W5500_Config *config,uint16_t address, uint8_t *data, uint16_t length);


#endif /* W5500_LOW_LEVEL_H_ */
