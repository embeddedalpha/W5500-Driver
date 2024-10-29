/*
 * W5500.h
 *
 *  Created on: Oct 28, 2024
 *      Author: kunal
 */

#ifndef W5500_APPLICATION_LAYER_W5500_H_
#define W5500_APPLICATION_LAYER_W5500_H_

#include "W5500_Low_Level/W5500_LL.h"
#include "W5500_Middleware/W5500_MWL.h"


bool W5500_UDP_Send_Data(uint8_t socket_number, uint8_t *data[], unit16_t length);
bool W5500_UDP_Receive_Data(uint8_t socket_number, uint8_t *data[], unit16_t *length);





#endif /* W5500_APPLICATION_LAYER_W5500_H_ */
