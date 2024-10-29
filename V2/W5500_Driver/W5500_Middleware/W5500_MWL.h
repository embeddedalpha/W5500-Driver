/*
 * W5500_MWL.h
 *
 *  Created on: Oct 18, 2024
 *      Author: ksalvi
 *
 *  @file W5500_MWL.h
 *  @brief Header file for W5500 Ethernet controller middleware layer.
 *
 *  This file contains the declarations and data structures required to configure
 *  and operate the W5500 Ethernet controller at a middleware level. It provides
 *  configurations for the SPI interface, interrupt, reset pins, and socket-specific
 *  configurations.
 */

#ifndef W5500_MIDDLEWARE_W5500_MWL_H_
#define W5500_MIDDLEWARE_W5500_MWL_H_

#include "main.h"
#include "W5500_MWL_Defs.h"
#include <W5500_Low_Level/W5500_LL.h>

extern bool Network_UpLink_Flag;
extern bool W5500_Service_Flag;
extern bool Network_Speed_Flag;



// Socket 0 reserved for MACRAW so it can do DHCP and non-UDP and TCP protocols.
// 2K TX memory and 2K RX Memory is reserved for this

// Socket 1 reserved for UDP so it can do UDP based protocols
// 7K TX memory and 7K RX Memory is reserved for this

// Socket 2 reserved for TCP so it can do TCP based protocols
// 7K TX memory and 7K RX Memory is reserved for this
/**
 * @brief Configuration structure for W5500 Ethernet controller.
 *
 * This structure encapsulates the configuration settings required to initialize and
 * operate the W5500 chip, including SPI configuration, pin configurations for interrupts
 * and reset, mode selection, IP type, MAC address, and socket-specific settings.
 */
typedef struct W5500_Config
{
    SPI_Config SPI_Handler; /*!< SPI configuration for W5500 communication. */

    /**
     * @brief Pins structure to define interrupt and reset pins.
     *
     * This structure holds the GPIO port and pin number used for the interrupt
     * and reset functionalities of the W5500 chip.
     */
    struct Pins
    {
        GPIO_TypeDef *Port; /*!< GPIO port for interrupt/reset pins. */
        uint8_t pin;        /*!< Pin number for interrupt/reset pins. */
    }Interrupt_Pin, Reset_Pin;

    uint8_t Mode; /*!< Operating mode of the W5500. */
    uint8_t IP_Type; /*!< Type of IP address (e.g., IPv4, etc.). */

    uint8_t Source_MAC[6]; /*!< MAC address of the source device. */
    uint8_t Source_IP[4]; /*!< IP address of the source device. */

    /**
     * @brief Socket configuration structure for up to 8 sockets.
     *
     * This structure encapsulates various configuration options for each socket,
     * including enabling/disabling, mode settings, buffer sizes, pointer positions,
     * port numbers, and both source and destination IP and MAC addresses.
     */
    struct Socket_Config
    {
    	bool Enable;
        uint16_t TX_Pointer;       /*!< TX pointer to keep track of transmitted data. */
        uint16_t RX_Pointer;       /*!< RX pointer to keep track of received data. */
        uint16_t Source_Port;      /*!< Source port number for this socket. */
        uint16_t Destination_Port; /*!< Destination port number for this socket. */
        uint8_t  Destination_IP[4];/*!< Destination IP address for this socket. */
        uint8_t  Destination_MAC[6];/*!< Destination MAC address for this socket. */
    } TCP_Socket, UDP_Socket; /*!< Array of socket configurations for up to 8 sockets. */



} W5500_Config;
/**
 * @brief Initializes the W5500 chip with the given configuration.
 *
 * This function initializes the W5500 Ethernet controller based on the
 * provided configuration parameters, including SPI settings and pin configurations.
 *
 * @param config Pointer to the W5500 configuration structure.
 * @return True if the initialization is successful, false otherwise.
 */
bool MWL_W5500_Init(W5500_Config *config);

/**
 * @brief Checks if the W5500 chip is responding.
 *
 * This function verifies the presence and responsiveness of the W5500 chip
 * by communicating with it over the SPI interface.
 *
 * @param config Pointer to the W5500 configuration structure.
 * @return True if the chip is detected and responding, false otherwise.
 */
bool MWL_W5500_Check_Chip(W5500_Config *config);

/**
 * @brief Checks the link status of the W5500 Ethernet connection.
 *
 * This function checks whether the W5500 has established an active Ethernet link.
 *
 * @param config Pointer to the W5500 configuration structure.
 * @return True if the Ethernet link is active, false otherwise.
 */
bool MWL_W5500_Check_Link(W5500_Config *config);

/**
 * @brief Checks the speed of the Ethernet link.
 *
 * This function determines the speed (e.g., 10 Mbps or 100 Mbps) of the
 * Ethernet link established by the W5500 chip.
 *
 * @param config Pointer to the W5500 configuration structure.
 */
void MWL_W5500_Check_Speed(W5500_Config *config);

/**
 * @brief Sets the destination MAC address for a specific socket.
 *
 * This function configures the destination MAC address for the specified socket
 * in the W5500 configuration.
 *
 * @param config Pointer to the W5500 configuration structure.
 * @param socket_number Socket number for which to set the destination MAC address.
 */
void MWL_W5500_Set_Destination_MAC(W5500_Config *config, uint8_t socket_number);

/**
 * @brief Retrieves the destination MAC address for a specific socket.
 *
 * This function reads and returns the destination MAC address for the specified
 * socket from the W5500 configuration.
 *
 * @param config Pointer to the W5500 configuration structure.
 * @param socket_number Socket number for which to retrieve the destination MAC address.
 */
void MWL_W5500_Get_Destination_MAC(W5500_Config *config, uint8_t socket_number);


void MWL_W5500_Ping(uint8_t *Target_IP[]);

#endif /* W5500_MIDDLEWARE_W5500_MWL_H_ */
