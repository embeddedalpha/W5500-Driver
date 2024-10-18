/*
 * W5500_LL.h
 *
 *  Created on: Oct 18, 2024
 *      Author: ksalvi
 */

#ifndef W5500_LOW_LEVEL_W5500_LL_H_
#define W5500_LOW_LEVEL_W5500_LL_H_

#include <W5500_Low_Level/W5500_LL_Regs.h>
#include "main.h"
#include "GPIO/GPIO.h"
#include "SPI/SPI.h"
#include "DMA/DMA.h"

#ifdef W5500_LOG
#include "Logs/Logs.h"
#endif


void LL_W5500_Init_Link(SPI_Config *_spi_);

bool LL_W5500_Write_Common_Register(uint16_t Control_Register, uint8_t data[], uint16_t len);

bool LL_W5500_Read_Common_Register(uint16_t Control_Register, uint8_t *data, uint16_t len);

bool LL_W5500_Write_Socket_Configuration_Register(uint16_t Socket_Register, uint8_t socket_number, uint8_t data[], uint16_t len);

bool LL_W5500_Read_Socket_Configuration_Register(uint16_t Socket_Register, uint8_t socket_number, uint8_t *data, uint16_t len);

bool LL_W5500_Write_Socket_Buffer(uint16_t address, uint8_t socket_number, uint8_t tx_data[], uint16_t len);

bool LL_W5500_Read_Socket_Buffer(uint16_t address, uint8_t socket_number, uint8_t *rx_data[], uint16_t len);



#endif /* W5500_LOW_LEVEL_W5500_LL_H_ */
