/*
 * W5500_HAL.c
 *
 *  Created on: Dec 28, 2023
 *      Author: kunal
 */


#include "W5500_HAL.h"



uint8_t W5500_Read_ID(W5500_Config *config)
{
	uint8_t id;
	Read_1_Byte(config, W5500_Common_Register.Chip_Version, W5500_Control_Register.Common_Register, &id);
	return id;
}

void W5500_Read_Gateway_Address(W5500_Config *config, uint32_t *gateway_address)
{
	uint8_t data1,data2,data3,data4;
	Read_4_Byte(config, W5500_Common_Register.Gateway_Address_0, W5500_Control_Register.Common_Register, &data1, &data2, &data3, &data4);
	*gateway_address = (data1 << 24) | (data2 << 16) | (data3 << 8) | (data4 << 0);
}

void W5500_Read_Source_IP_Address(W5500_Config *config, uint32_t *sourceipaddress)
{
	uint8_t data1,data2,data3,data4;
	Read_4_Byte(config, W5500_Common_Register.Source_IP_Address_0, W5500_Control_Register.Common_Register, &data1, &data2, &data3, &data4);
	*sourceipaddress = (data1 << 24) | (data2 << 16) | (data3 << 8) | (data4 << 0);
}

void W5500_Read_Subnet_Mask_Address(W5500_Config *config, uint32_t *subnetmask_address)
{
	uint8_t data1,data2,data3,data4;
	Read_4_Byte(config, W5500_Common_Register.Subnet_Mask_Address_0, W5500_Control_Register.Common_Register, &data1, &data2, &data3, &data4);
	*subnetmask_address = (data1 << 24) | (data2 << 16) | (data3 << 8) | (data4 << 0);
}

void W5500_Read_Source_Hardware_Address(W5500_Config *config, uint64_t *sourcehardwareaddress)
{
	uint8_t data[6];
	Read_Multiple_Bytes(config, W5500_Common_Register.Source_Hardware_Address_0, W5500_Control_Register.Common_Register, &data[0], 6);
	*sourcehardwareaddress = (uint64_t)(((uint64_t)data[0] << (8*5)) | ((uint64_t)data[1] << (8*4) | ((uint64_t)data[2] << (8*3)) |
						  ((uint64_t)data[3] << (8*2)) | ((uint64_t)data[4] << (8*1)) | ((uint64_t)data[0] << (8*0))));
}

void W5500_Read_Interrupt_Low_Level_Timer(W5500_Config *config, uint16_t *lltimer)
{
	uint8_t data[2];
	Read_2_Byte(config, W5500_Common_Register.Interrupt_Low_Level_Timer_0, W5500_Control_Register.Common_Register, &data[0]);
	*lltimer = (data[0] << 8) | (data[1] << 0);
}

uint8_t W5500_Read_Interrupt_Register(W5500_Config *config)
{
	uint8_t data;
	Read_1_Byte(config, W5500_Common_Register.Interrupt, W5500_Control_Register.Common_Register, &data);
	return data;
}

void W5500_Read_Destination_Hardware_Address(W5500_Config *config, uint64_t *destinationhardwareaddress)
{
	uint8_t data[6];
	Read_Multiple_Bytes(config, W5500_Common_Register.PPP_Destination_MAC_Address_0, W5500_Control_Register.Common_Register, &data[0], 6);
	*destinationhardwareaddress = (uint64_t)(((uint64_t)data[0] << (8*5)) | ((uint64_t)data[1] << (8*4) | ((uint64_t)data[2] << (8*3)) |
						  ((uint64_t)data[3] << (8*2)) | ((uint64_t)data[4] << (8*1)) | ((uint64_t)data[0] << (8*0))));
}

void W5500_Read_Session_ID(W5500_Config *config, uint16_t *sessionID)
{
	uint8_t data[2];
	Read_2_Byte(config, W5500_Common_Register.PPP_Session_Identification_0, W5500_Control_Register.Common_Register, &data[0]);
	*sessionID = (data[0] << 8) | (data[1] << 0);
}

void W5500_Read_Maximum_Segment_Size(W5500_Config *config, uint16_t *maxsegmentsize)
{
	uint8_t data[2];
	Read_2_Byte(config, W5500_Common_Register.PPP_Maximum_Segment_Size_0, W5500_Control_Register.Common_Register, &data[0]);
	*maxsegmentsize = (data[0] << 8) | (data[1] << 0);
}

uint8_t W5500_Read_Phy_Configuration(W5500_Config *config)
{
	uint8_t id;
	Read_1_Byte(config, W5500_Common_Register.PHY_Configuration, W5500_Control_Register.Common_Register, &id);
	return id;
}

uint8_t W5500_Read_Socket_1_Mode_Register(W5500_Config *config)
{
	uint8_t mode;
	Read_1_Byte(config, W5500_Socket_Register.Sn_TTL, W5500_Control_Register.Socket_0_Control, &mode);
	return mode;
}

void W5500_Setup_Gateway_Address(W5500_Config *config)
{

	Write_4_Byte(config, W5500_Common_Register.Gateway_Address_0, W5500_Control_Register.Common_Register, config->Gateway_Address);
#if W5500_DEBUG_FLAG
	uint32_t gateway_address;
	W5500_Read_Gateway_Address(config, &gateway_address);
#endif
}

void W5500_Setup_Subnet_Mask_Address(W5500_Config *config)
{

	Write_4_Byte(config, W5500_Common_Register.Subnet_Mask_Address_0, W5500_Control_Register.Common_Register, config->Subnet_Mask_Address);
#if W5500_DEBUG_FLAG
	uint32_t subnetmask_address;
	W5500_Read_Subnet_Mask_Address(config, &subnetmask_address);
#endif
}

void W5500_Setup_Source_Hardware_Address(W5500_Config *config)
{
	Write_Multiple_Bytes(config, W5500_Common_Register.Source_Hardware_Address_0, W5500_Control_Register.Common_Register, config->Source_Hardware_Address, 6);
#if W5500_DEBUG_FLAG
	uint8_t data[6];
	Read_Multiple_Bytes(config, W5500_Common_Register.Source_Hardware_Address_0, W5500_Control_Register.Common_Register, &data[0], 6);
	uint64_t sourcehardwareaddress = (uint64_t)(((uint64_t)data[0] << (8*5)) | ((uint64_t)data[1] << (8*4) | ((uint64_t)data[2] << (8*3)) |
						  ((uint64_t)data[3] << (8*2)) | ((uint64_t)data[4] << (8*1)) | ((uint64_t)data[0] << (8*0))));
#endif


}

void W5500_Setup_Source_IP_Address(W5500_Config *config)
{

	Write_4_Byte(config, W5500_Common_Register.Source_IP_Address_0, W5500_Control_Register.Common_Register, config->Source_IP_Address);
#if W5500_DEBUG_FLAG
	uint32_t sourceipaddress;
	W5500_Read_Source_IP_Address(config, &sourceipaddress);
#endif


}

