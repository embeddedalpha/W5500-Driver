/*
 * W5500_HAL.h
 *
 *  Created on: Dec 28, 2023
 *      Author: kunal
 */

#ifndef W5500_HAL_H_
#define W5500_HAL_H_

#include "W5500.h"
#include "W5500_LL.h"
#include "W5500_Defs.h"






uint8_t W5500_Read_ID(W5500_Config *config);

void W5500_Read_Gateway_Address(W5500_Config *config, uint32_t *gateway_address);

void W5500_Read_Source_IP_Address(W5500_Config *config, uint32_t *sourceipaddress);

void W5500_Read_Subnet_Mask_Address(W5500_Config *config, uint32_t *subnetmask_address);

void W5500_Read_Source_Hardware_Address(W5500_Config *config, uint64_t *sourcehardwareaddress);

void W5500_Read_Interrupt_Low_Level_Timer(W5500_Config *config, uint16_t *lltimer);

uint8_t W5500_Read_Interrupt_Register(W5500_Config *config);

void W5500_Read_Destination_Hardware_Address(W5500_Config *config, uint64_t *destinationhardwareaddress);

void W5500_Read_Session_ID(W5500_Config *config, uint16_t *sessionID);

void W5500_Read_Maximum_Segment_Size(W5500_Config *config, uint16_t *maxsegmentsize);

uint8_t W5500_Read_Phy_Configuration(W5500_Config *config);

uint8_t W5500_Read_Socket_1_Mode_Register(W5500_Config *config);

void W5500_Setup_Gateway_Address(W5500_Config *config);

void W5500_Setup_Subnet_Mask_Address(W5500_Config *config);

void W5500_Setup_Source_Hardware_Address(W5500_Config *config);

void W5500_Setup_Source_IP_Address(W5500_Config *config);















#endif /* W5500_HAL_H_ */
