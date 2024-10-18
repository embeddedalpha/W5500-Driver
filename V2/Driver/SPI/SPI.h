/**
 * @mainpage SPI Interface Driver Documentation
 *
 * @section intro_sec Introduction
 *
 * This documentation provides a detailed description of the SPI interface driver for
 * the STM32F407VGT6 microcontroller. The driver is designed to initialize, configure,
 * and control the SPI peripheral, providing functions for data transmission and
 * reception, clock control, and more.
 *
 * @section features_sec Features
 * - SPI Initialization and Configuration
 * - Clock Control
 * - Data Transmission and Reception
 * - NSS (Chip Select) Control
 * - DMA and Interrupt Support
 *
 * @section author_sec Author
 * - Name: Kunal Salvi
 * - Date: 2024-08-24
 *
 * @section license_sec License
 * This project is licensed under the MIT License - see the LICENSE file for details.
 *
 * @section history_sec Revision History
 * - Version 1.0 - Initial release
 */


/**
 * @file SPI.h
 * @brief SPI interface driver for STM32F407VGT6.
 *
 * This file provides the API for initializing and controlling the SPI peripheral
 * on the STM32F407VGT6 microcontroller. It includes functions to enable/disable
 * the SPI clock, configure the SPI settings, and transmit/receive data over SPI.
 *
 * @author Kunal Salvi
 * @date 2024-08-24
 * @version 1.0
 */

#ifndef SPI_H_
#define SPI_H_

#include "main.h"
#include "GPIO/GPIO.h"
#include "DMA/DMA.h"
#include "SPI_Defs.h"

/**
 * @brief SPI configuration structure.
 *
 * This structure holds the configuration parameters for the SPI peripheral,
 * including the SPI port, pins, mode, data format, and other settings.
 */
typedef struct SPI_Config
{
    SPI_TypeDef *Port;         /**< Pointer to the SPI port (SPI1, SPI2, etc.). */
    uint8_t clock_pin;         /**< Clock pin number. */
    uint8_t mosi_pin;          /**< MOSI pin number. */
    uint8_t miso_pin;          /**< MISO pin number. */

    GPIO_TypeDef *NSS_Port;    /**< Pointer to the GPIO port for NSS. */
    uint8_t NSS_Pin;           /**< NSS pin number. */

    uint16_t mode;             /**< SPI mode (Master/Slave). */
    uint16_t crc;              /**< CRC polynomial value. */
    uint16_t data_format;      /**< Data format (8-bit, 16-bit). */
    uint16_t frame_format;     /**< Frame format (MSB first, LSB first). */
    uint16_t prescaler;        /**< Clock prescaler value. */
    uint16_t type;             /**< SPI type (full-duplex, half-duplex, simplex). */
    uint16_t clock_polarity;   /**< Clock polarity (CPOL). */
    uint16_t clock_phase;      /**< Clock phase (CPHA). */
    uint16_t interrupt;        /**< Interrupt enable/disable. */
    uint16_t dma;              /**< DMA enable/disable. */

    struct DMA_Setting
    {
        // Add DMA-specific configuration fields here if needed.
    } DMA_Setting;             /**< DMA settings structure. */

} SPI_Config;

/**
 * @brief Enables the SPI clock.
 *
 * This function enables the clock for the specified SPI peripheral.
 *
 * @param[in] config Pointer to the SPI configuration structure.
 * @return int8_t Returns 0 on success, -1 on failure.
 */
int8_t SPI_Clock_Enable(SPI_Config *config);

/**
 * @brief Disables the SPI clock.
 *
 * This function disables the clock for the specified SPI peripheral.
 *
 * @param[in] config Pointer to the SPI configuration structure.
 * @return int8_t Returns 0 on success, -1 on failure.
 */
int8_t SPI_Clock_Disable(SPI_Config *config);

/**
 * @brief Resets the SPI configuration.
 *
 * This function resets the configuration parameters of the SPI peripheral to their default values.
 *
 * @param[in] config Pointer to the SPI configuration structure.
 * @return int8_t Returns 0 on success, -1 on failure.
 */
int8_t SPI_Config_Reset(SPI_Config *config);

/**
 * @brief Initializes the SPI peripheral.
 *
 * This function initializes the SPI peripheral with the specified configuration parameters.
 *
 * @param[in] config Pointer to the SPI configuration structure.
 * @return int8_t Returns 0 on success, -1 on failure.
 */
int8_t SPI_Init(SPI_Config *config);

/**
 * @brief Deinitializes the SPI peripheral.
 *
 * This function deinitializes the SPI peripheral and releases the associated resources.
 *
 * @param[in] config Pointer to the SPI configuration structure.
 */
void SPI_DeInit(SPI_Config *config);

/**
 * @brief Enables the SPI peripheral.
 *
 * This function enables the SPI peripheral, allowing data transmission and reception.
 *
 * @param[in] config Pointer to the SPI configuration structure.
 */
void SPI_Enable(SPI_Config *config);

/**
 * @brief Disables the SPI peripheral.
 *
 * This function disables the SPI peripheral, preventing data transmission and reception.
 *
 * @param[in] config Pointer to the SPI configuration structure.
 */
void SPI_Disable(SPI_Config *config);

/**
 * @brief Updates the SPI data format.
 *
 * This function updates the data format (8-bit, 16-bit) of the SPI peripheral.
 *
 * @param[in] config Pointer to the SPI configuration structure.
 */
void SPI_Data_Format_Update(SPI_Config *config);

/**
 * @brief Transmits and receives a single byte over SPI.
 *
 * This function transmits a single byte of data over SPI and returns the received byte.
 *
 * @param[in] config Pointer to the SPI configuration structure.
 * @param[in] tx_data Data to transmit.
 * @return uint16_t Received data.
 */
uint16_t SPI_TRX_Byte(SPI_Config *config, uint16_t tx_data);

/**
 * @brief Transmits and receives a buffer of data over SPI.
 *
 * This function transmits and receives a buffer of data over SPI.
 *
 * @param[in] config Pointer to the SPI configuration structure.
 * @param[in] tx_buffer Pointer to the transmit buffer.
 * @param[out] rx_buffer Pointer to the receive buffer.
 * @param[in] tx_length Length of the transmit buffer.
 * @param[in] rx_length Length of the receive buffer.
 * @return int8_t Returns 0 on success, -1 on failure.
 */
int8_t SPI_TRX_Buffer(SPI_Config *config, uint16_t *tx_buffer, uint16_t *rx_buffer, uint16_t tx_length, uint16_t rx_length);

/**
 * @brief Sets the NSS pin high.
 *
 * This function sets the NSS pin to a high level, indicating the end of SPI communication.
 *
 * @param[in] config Pointer to the SPI configuration structure.
 */
void SPI_NSS_High(SPI_Config *config);

/**
 * @brief Sets the NSS pin low.
 *
 * This function sets the NSS pin to a low level, indicating the start of SPI communication.
 *
 * @param[in] config Pointer to the SPI configuration structure.
 */
void SPI_NSS_Low(SPI_Config *config);

#endif /* SPI_H_ */
