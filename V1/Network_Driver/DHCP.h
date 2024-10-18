/*
 * DHCP.h
 *
 *  Created on: Dec 19, 2023
 *      Author: kunal
 */

#ifndef DHCP_DHCP_H_
#define DHCP_DHCP_H_

#include "main.h"
#include "W5500.h"


void DHCP_Client_Send_Discovery(W5500_Config *config, W5500_Socket_Config *socket_config);

#endif /* DHCP_DHCP_H_ */
