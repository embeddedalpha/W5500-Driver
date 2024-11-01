/*
 * W5500_MWL.c
 *
 *  Created on: Oct 18, 2024
 *      Author: ksalvi
 */


#include <W5500_Middleware/W5500_MWL.h>

bool Network_UpLink_Flag;
bool W5500_Service_Flag;
bool Network_Speed_Flag;

uint8_t temp_data[4];




void EXTI0_IRQHandler(void){

	uint8_t socket_interrupt_buffer[8];

	for(int i = 0; i < 8; i++)
	{
		socket_interrupt_buffer[i] = LL_W5500_Read_Socket_Configuration_Register(W5500_Control_Register.Socket_Register.Sn_IR, i, &temp_data[0], 1);
	}





}


bool W5500_Init(W5500_Config *config)
{
	LL_W5500_Init_Link(&config->SPI_Handler);

	GPIO_Pin_Init(config->Reset_Pin.Port, config->Reset_Pin.pin, GPIO_Configuration.Mode.General_Purpose_Output,
				  GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed,
				  GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.None);

	GPIO_Pin_Init(config->Interrupt_Pin.Port, config->Interrupt_Pin.pin, GPIO_Configuration.Mode.Input,
				  GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.None,
				  GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.None);



	GPIO_Pin_High(config->Reset_Pin.Port, config->Reset_Pin.pin);
	Delay_milli(10);
	GPIO_Pin_Low(config->Reset_Pin.Port, config->Reset_Pin.pin);
	Delay_milli(10);
	GPIO_Pin_High(config->Reset_Pin.Port, config->Reset_Pin.pin);


	if(W5500_Check_Chip(config))
	{
		if(W5500_Check_Link(config))
		{
			W5500_Check_Speed(config);

			LL_W5500_Write_Common_Register(W5500_Control_Register.Common_Register.SHAR0, config->Source_MAC, 6);

			if(config->IP_Type == W5500_Configuration.IP_Type.Static)
			{
				// Setup IP Address for
				LL_W5500_Write_Common_Register(W5500_Control_Register.Common_Register.SIPR0, config->Source_IP, 4);
			}
			else
			{
				// Do DHCP Routine to get Dynamic IP
			}

			//Setup Interrupts
			GPIO_Interrupt_Setup(config->Interrupt_Pin.pin, GPIO_Configuration.Interrupt_Edge.FALLING_EDGE, 0);

//			for(uint8_t i = 0; i < 8; i++)
//			{
//				temp_data[0] = 0b00011111;
//				LL_W5500_Write_Socket_Configuration_Register(W5500_Control_Register.Socket_Register.Sn_IMR, i, data, 1);
//			}


			temp_data[0] = 0x04;
			LL_W5500_Write_Socket_Configuration_Register(W5500_Control_Register.Socket_Register.Sn_TXBUF_SIZE, 0, temp_data[0], 1);


			temp_data[0] = 0x08; //For UDP
			LL_W5500_Write_Socket_Configuration_Register(W5500_Control_Register.Socket_Register.Sn_TXBUF_SIZE, 1, temp_data[0], 1);

			temp_data[0] = 0x08; //For UDP
			LL_W5500_Write_Socket_Configuration_Register(W5500_Control_Register.Socket_Register.Sn_TXBUF_SIZE, 2, temp_data[0], 1);


			temp_data[0] = 0x04;
			LL_W5500_Write_Socket_Configuration_Register(W5500_Control_Register.Socket_Register.Sn_RXBUF_SIZE, 0, temp_data[0], 1);


			temp_data[0] = 0x08; //For UDP
			LL_W5500_Write_Socket_Configuration_Register(W5500_Control_Register.Socket_Register.Sn_RXBUF_SIZE, 1, temp_data[0], 1);

			temp_data[0] = 0x08; //For UDP
			LL_W5500_Write_Socket_Configuration_Register(W5500_Control_Register.Socket_Register.Sn_RXBUF_SIZE, 2, temp_data[0], 1);




		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}

	return 0;



}


bool W5500_Check_Chip(W5500_Config *config)
{
	uint8_t counter = 100;
	while(counter != 0)
	{
		 LL_W5500_Read_Common_Register(W5500_Control_Register.Common_Register.VERSIONR, temp_data, 1);
		 if(temp_data[0] == 0x04) return 1;
		counter--;
	}
	return 0;
}

bool W5500_Check_Link(W5500_Config *config)
{

	 LL_W5500_Read_Common_Register(W5500_Control_Register.Common_Register.PHYCFGR, temp_data, 1);
	 if(temp_data[0] & 0x01){
		 Network_UpLink_Flag = 1;
		 return 1;
	 }
	 Network_UpLink_Flag = 0;
	 return 0;
}

void W5500_Check_Speed(W5500_Config *config)
{
	 LL_W5500_Read_Common_Register(W5500_Control_Register.Common_Register.PHYCFGR, temp_data, 1);
	 if((temp_data[0] & 0x02) == 0x02){
		 Network_Speed_Flag = 1;
	 }
	 else
	 {
		 Network_Speed_Flag = 0;
	 }
}

//void W5500_Set_Destination_MAC(W5500_Config *config, uint8_t socket_number)
//{
//	LL_W5500_Write_Socket_Configuration_Register(W5500_Control_Register.Socket_Register.Sn_DHAR0, socket_number, config->Socket_Config[socket_number].Destination_MAC, 6);
//}
//
//void W5500_Get_Destination_MAC(W5500_Config *config, uint8_t socket_number)
//{
//	LL_W5500_Read_Socket_Configuration_Register(W5500_Control_Register.Socket_Register.Sn_DHAR0, socket_number, config->Socket_Config[socket_number].Destination_MAC, 6);
//}

void W5500_Set_Mode(W5500_Config *config)
{
	LL_W5500_Read_Common_Register(W5500_Control_Register.Common_Register.PHYCFGR, temp_data, 1);
	temp_data[0] &= ~0x38;
	temp_data[0] |= config->Mode << 3;
	LL_W5500_Write_Common_Register(W5500_Control_Register.Common_Register.PHYCFGR, temp_data, 1);

}

void W5500_Ping(uint8_t *Target_IP[])
{


}

void W5500_Get_RX_Buffer_Details(uint8_t socket_number, uint16_t *read_pointer,uint16_t *write_pointer, uint16_t *rx_packet_size)
{

	LL_W5500_Read_Socket_Configuration_Register(W5500_Control_Register.Socket_Register.Sn_RX_WR0, socket_number, temp_data, 2);
	*write_pointer = (temp_data[0] << 8) | (temp_data[1]);

	LL_W5500_Read_Socket_Configuration_Register(W5500_Control_Register.Socket_Register.Sn_RX_RD0, socket_number, temp_data, 2);
	*read_pointer = (temp_data[0] << 8) | (temp_data[1]);

	LL_W5500_Read_Socket_Configuration_Register(W5500_Control_Register.Socket_Register.Sn_RX_RSR0, socket_number, temp_data, 2);
	*rx_packet_size = (temp_data[0] << 8) | (temp_data[1]);
}



bool W5500_Socket_Close(W5500_Config *config, uint8_t socket_number)
{
	if((config->Socket[socket_number].Enable == true))
	{
		#ifdef W5500_Debug_Flag
				log_info("Socket %d will be closed",socket_number);
		#endif
		temp_data[0] = W5500_COMMAND_SOCKET_CLOSE;
		LL_W5500_Write_Socket_Configuration_Register(W5500_Control_Register.Socket_Register.Sn_CR, socket_number, temp_data, 1);
		LL_W5500_Read_Socket_Configuration_Register(W5500_Control_Register.Socket_Register.Sn_SR, socket_number, temp_data, 1);

		if(temp_data[0] == W5500_STATUS_SOCK_CLOSED)
		{
			#ifdef W5500_Debug_Flag
					log_info("Socket %d is closed",socket_number);
			#endif
			return 1;
		}
		else
		{
			#ifdef W5500_Debug_Flag
					log_error("Socket %d is not closed",socket_number);
			#endif
			return 1;
		}

	}
	else
	{
		#ifdef W5500_Debug_Flag
				log_error("Socket %d is not enabled. Try enabling it!",socket_number);
		#endif
		return 0;
	}

return 0;

}

bool W5500_Socket_Open(W5500_Config *config, uint8_t socket_number)
{
	if((config->Socket[socket_number].Enable == true))
	{
		#ifdef W5500_Debug_Flag
				log_info("Socket %d will be opened",socket_number);
		#endif
		if(config->Socket->mode == W5500_Configuration.Socket_Config.Mode.UDP){
			temp_data[0] = W5500_COMMAND_SOCKET_OPEN;
			LL_W5500_Write_Socket_Configuration_Register(W5500_Control_Register.Socket_Register.Sn_CR, socket_number, temp_data, 1);
			LL_W5500_Read_Socket_Configuration_Register(W5500_Control_Register.Socket_Register.Sn_SR, socket_number, temp_data, 1);
			if(temp_data[0] == W5500_STATUS_SOCK_UDP)
			{
				#ifdef W5500_Debug_Flag
						log_info("Socket %d is opened as UDP",socket_number);
				#endif
				return 1;
			}
			else
			{
				while(!W5500_Socket_Close(config, socket_number));
				#ifdef W5500_Debug_Flag
						log_error("Socket %d cannot be opened and is closed. Try opening again",socket_number);
				#endif
				return 0;
			}
		}
		else if(config->Socket->mode == W5500_Configuration.Socket_Config.Mode.TCP){
			temp_data[0] = W5500_COMMAND_SOCKET_OPEN;
			LL_W5500_Write_Socket_Configuration_Register(W5500_Control_Register.Socket_Register.Sn_CR, socket_number, temp_data, 1);
			LL_W5500_Read_Socket_Configuration_Register(W5500_Control_Register.Socket_Register.Sn_SR, socket_number, temp_data, 1);
			if(temp_data[0] == W5500_STATUS_SOCK_INIT)
			{
				#ifdef W5500_Debug_Flag
						log_info("Socket %d is opened as TCP",socket_number);
				#endif
				return 1;
			}
			else
			{
				while(!W5500_Socket_Close(config, socket_number));
				#ifdef W5500_Debug_Flag
						log_error("Socket %d cannot be opened and is being closed. Try opening again",socket_number);
				#endif
				return 0;
			}
		}
		else if(config->Socket->mode == W5500_Configuration.Socket_Config.Mode.MACRAW){
			temp_data[0] = W5500_COMMAND_SOCKET_OPEN;
			LL_W5500_Write_Socket_Configuration_Register(W5500_Control_Register.Socket_Register.Sn_CR, socket_number, temp_data, 1);
			LL_W5500_Read_Socket_Configuration_Register(W5500_Control_Register.Socket_Register.Sn_SR, socket_number, temp_data, 1);
			if(temp_data[0] == W5500_STATUS_SOCK_MACRAW)
			{
				#ifdef W5500_Debug_Flag
						log_info("Socket %d is opened as MACRAW",socket_number);
				#endif
				return 1;
			}
			else
			{
				while(!W5500_Socket_Close(config, socket_number));
				#ifdef W5500_Debug_Flag
						log_error("Socket %d cannot be opened and is being closed. Try opening again",socket_number);
				#endif
				return 0;
			}
		}
	}
	else
	{
		#ifdef W5500_Debug_Flag
				log_error("Socket %d is not enabled. Try enabling it!",socket_number);
		#endif
	}
	return 0;
}

bool W5500_Socket_Listen(W5500_Config *config, uint8_t socket_number)
{
	if(config->Socket[socket_number].Enable == true)
	{
		if(config->Socket[socket_number].mode == W5500_Configuration.Socket_Config.Mode.TCP)
		{
			temp_data[0] = W5500_COMMAND_SOCKET_OPEN;
			LL_W5500_Write_Socket_Configuration_Register(W5500_Control_Register.Socket_Register.Sn_CR, socket_number, temp_data, 1);
			LL_W5500_Read_Socket_Configuration_Register(W5500_Control_Register.Socket_Register.Sn_SR, socket_number, temp_data, 1);
			if(temp_data[0] == W5500_STATUS_SOCK_MACRAW)
			{
#ifdef W5500_Debug_Flag
			log_info("Socket %d is listening on %d",socket_number,config->Socket[socket_number].Destination_Port);
#endif
			}
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}

	return 0;
}


bool W5500_Socket_Send(W5500_Config *config, uint8_t socket_number)
{
	temp_data[0] = W5500_COMMAND_SOCKET_SEND;
	LL_W5500_Write_Socket_Configuration_Register(W5500_Control_Register.Socket_Register.Sn_CR, socket_number, temp_data, 1);
	LL_W5500_Read_Socket_Configuration_Register(W5500_Control_Register.Socket_Register.Sn_IR, socket_number, temp_data, 1);
	if(temp_data[0] && (1 << 4))
	{
#ifdef W5500_Debug_Flag
	log_info("Data sent to address %d",config->Socket[socket_number].Destination_Port);
#endif
	return 1;
	}
	else
	{
#ifdef W5500_Debug_Flag
	log_info("Data is not sent to address %d",config->Socket[socket_number].Destination_Port);
#endif
		return 0;
	}

	return 0;
}

bool W5500_Socket_Receive(W5500_Config *config, uint8_t socket_number)
{
	temp_data[0] = W5500_COMMAND_SOCKET_RECV;
	LL_W5500_Write_Socket_Configuration_Register(W5500_Control_Register.Socket_Register.Sn_CR, socket_number, temp_data, 1);
	LL_W5500_Read_Socket_Configuration_Register(W5500_Control_Register.Socket_Register.Sn_IR, socket_number, temp_data, 1);
	if(temp_data[0] && (1 << 2))
	{
#ifdef W5500_Debug_Flag
	log_info("Data is received from address %d",config->Socket[socket_number].Destination_Port);
#endif
	return 1;
	}
	else
	{
#ifdef W5500_Debug_Flag
	log_info("Data is not received from address %d",config->Socket[socket_number].Destination_Port);
#endif
		return 0;
	}

	return 0;
}
