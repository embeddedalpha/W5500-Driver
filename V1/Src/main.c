#include "main.h"
#include "SPI.h"
#include "W5500.h"
#include "Console.h"
//#include "DHCP.h"


SPI_Config xDevice;


W5500_Config xW5500;
W5500_Socket_Config xW5500_Socket0;




int main(void)
{
	MCU_Clock_Setup();
	Delay_Config();
	Console_Init(USART1, 9600);




	SPI_Config_Reset(&xW5500.SPI);
	xW5500.SPI.Port = SPI1;
	xW5500.SPI.miso_pin = SPI1_MISO.PA6;
	xW5500.SPI.mosi_pin = SPI1_MOSI.PA7;
	xW5500.SPI.clock_pin = SPI1_CLK.PA5;
	xW5500.SPI.prescaler = SPI_Prescaler.CLK_div_16;



	uint8_t Subnet_Mask_Address[] = {255,255,0,0};
	uint8_t Gateway_address[] = {0xFF,0xFF,0xFF,0xFF};
	uint8_t Source_Hardware_Address[] = {0x11,0x22,0x33,0x44,0x55,0x66};
	uint8_t Source_IP_Address[] = {169,254,26,102}; //169.254.26.103

	xW5500.Gateway_Address = Gateway_address;
	xW5500.Source_Hardware_Address = Source_Hardware_Address;
	xW5500.Source_IP_Address = Source_IP_Address;
	xW5500.Subnet_Mask_Address = Subnet_Mask_Address;
	xW5500.Source_Port = 48567;

	W5500_Init(&xW5500);

	xW5500_Socket0.Hardware_Socket_Number = W5500_Hardware_Socket.Socket_1;
	xW5500_Socket0.Mode = W5500_Socket_Mode.UDP;
	xW5500_Socket0.Destination_Port = 48569; //48569

	uint8_t Destination_Hardware_Address[] = { 0x00,0xe0,0x4c,0x68,0x9e,0x2c};
	uint8_t Destination_IP_Address[] = {169,254,149,36}; //169.254.26.103
	xW5500_Socket0.Destination_Hardware_Address = Destination_Hardware_Address;
	xW5500_Socket0.Destination_IP_Address = Destination_IP_Address;




	uint8_t IP[4];
	uint16_t Port;
	uint16_t Payload_Length;
	uint8_t Payload[200];




	int i = 0;

	while(i < 10000)
	{
		uint8_t data[] = {'K','u','n','a','l',' ', 'S', 'a', 'l', 'v', 'i',i};
		xW5500_Socket0.data = &data[0];
		xW5500_Socket0.data_len = 12;
		W5500_UDP_Socket_Open(&xW5500, &xW5500_Socket0);
		W5500_UDP_Socket_Send_Packet(&xW5500, &xW5500_Socket0);
		W5500_UDP_Socket_Get_Packet(&xW5500, &xW5500_Socket0, &IP, &Port, &Payload, &Payload_Length);
		W5500_UDP_Socket_Close(&xW5500, &xW5500_Socket0);

		printConsole("%d\r\n",Port);
		printConsole("%d\r\n",Payload_Length);

		Delay_s(5);
		i++;
	}


}

//hello

