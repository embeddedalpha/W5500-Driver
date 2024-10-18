/**
 * @file SPI_Defs.h
 * @brief Definition of SPI configuration structures and constants for STM32F407VGT6.
 *
 * This file defines various structures and constants used for configuring
 * the SPI peripheral on the STM32F407VGT6 microcontroller. It includes modes,
 * data formats, clock settings, interrupt configurations, and more.
 * These definitions are essential for setting up and controlling the SPI peripheral.
 *
 * The SPI_Configurations structure provides predefined values for common settings.
 *
 * This file should be included in any SPI-related source code files.
 *
 * @note Ensure that the appropriate header files such as "main.h" are included before including this file.
 *
 * @version 1.0
 * @date 2024-08-24
 *
 * @author Kunal Salvi
 */

#ifndef SPI_DEFS_H_
#define SPI_DEFS_H_

#include "main.h"

/**
 * @brief Structure defining the modes of SPI operation.
 *
 * This structure contains fields for different SPI modes, such as
 * full-duplex, half-duplex, and master/slave configurations.
 */
typedef struct SPI_Mode
{
    uint8_t Full_Duplex_Master; /**< SPI in full-duplex master mode. */
    uint8_t Full_Duplex_Slave;  /**< SPI in full-duplex slave mode. */
    uint8_t Half_Duplex_Master; /**< SPI in half-duplex master mode. */
    uint8_t Half_Duplex_Slave;  /**< SPI in half-duplex slave mode. */
    uint8_t RX_Only_Master;     /**< SPI in RX-only master mode. */
    uint8_t RX_Only_Slave;      /**< SPI in RX-only slave mode. */
    uint8_t TX_Only_Master;     /**< SPI in TX-only master mode. */
    uint8_t TX_Only_Slave;      /**< SPI in TX-only slave mode. */
} SPI_Mode;

/**
 * @brief Structure defining the CRC (Cyclic Redundancy Check) settings for SPI.
 *
 * This structure contains fields to enable or disable CRC functionality.
 */
typedef struct SPI_CRC
{
    bool Enable;  /**< Enable CRC calculation. */
    bool Disable; /**< Disable CRC calculation. */
} SPI_CRC;

/**
 * @brief Structure defining the data format for SPI communication.
 *
 * This structure contains fields for selecting 8-bit or 16-bit data formats.
 */
typedef struct SPI_Data_Format
{
    uint8_t Bit8;  /**< 8-bit data format. */
    uint8_t Bit16; /**< 16-bit data format. */
} SPI_Data_Format;

/**
 * @brief Structure defining the frame format for SPI communication.
 *
 * This structure contains fields to set the frame format as MSB-first or LSB-first.
 */
typedef struct SPI_Frame_Format
{
    uint8_t MSB_First; /**< Most significant bit first. */
    uint8_t LSB_First; /**< Least significant bit first. */
} SPI_Frame_Format;

/**
 * @brief Structure defining the clock phase and polarity settings for SPI.
 *
 * This structure contains fields to set the clock phase and polarity.
 */
typedef struct SPI_Clock_Phase_and_Polarity
{
    uint8_t High_1; /**< Clock phase/polarity high (1). */
    uint8_t Low_0;  /**< Clock phase/polarity low (0). */
} SPI_Clock_Phase_and_Polarity;

/**
 * @brief Structure defining the type of SPI operation.
 *
 * This structure contains fields for setting the SPI operation as master or slave.
 */
typedef struct SPI_Type
{
    uint8_t Master; /**< SPI in master mode. */
    uint8_t Slave;  /**< SPI in slave mode. */
} SPI_Type;

/**
 * @brief Structure defining the interrupt configuration for SPI.
 *
 * This structure contains fields to enable or disable specific SPI interrupts.
 */
typedef struct SPI_Interrupt
{
    uint8_t Tx_Buffer_Empty;      /**< Interrupt when TX buffer is empty. */
    uint8_t RX_Buffer_not_Empty;  /**< Interrupt when RX buffer is not empty. */
    uint8_t Error;                /**< Interrupt on error. */
    uint8_t Disable;              /**< Disable all interrupts. */
} SPI_Interrupt;

/**
 * @brief Structure defining the DMA configuration for SPI.
 *
 * This structure contains fields for enabling or disabling DMA for TX and RX operations.
 */
typedef struct SPI_DMA
{
    uint8_t TX_DMA_Enable;  /**< Enable DMA for TX. */
    uint8_t TX_DMA_Disable; /**< Disable DMA for TX. */
    uint8_t RX_DMA_Enable;  /**< Enable DMA for RX. */
    uint8_t RX_DMA_Disable; /**< Disable DMA for RX. */
} SPI_DMA;

/**
 * @brief Structure defining the clock prescaler settings for SPI.
 *
 * This structure contains fields for setting the clock prescaler to various divisions.
 */
typedef struct SPI_Prescaler
{
    uint8_t CLK_div_2;   /**< Clock divided by 2. */
    uint8_t CLK_div_4;   /**< Clock divided by 4. */
    uint8_t CLK_div_8;   /**< Clock divided by 8. */
    uint8_t CLK_div_16;  /**< Clock divided by 16. */
    uint8_t CLK_div_32;  /**< Clock divided by 32. */
    uint8_t CLK_div_64;  /**< Clock divided by 64. */
    uint8_t CLK_div_128; /**< Clock divided by 128. */
    uint8_t CLK_div_256; /**< Clock divided by 256. */
} SPI_Prescaler;

/**
 * @brief Structure defining the SPI pin mappings.
 *
 * This structure contains nested structures defining the pin mappings
 * for SPI1, SPI2, and SPI3 for the CLK, MOSI, and MISO signals.
 */
typedef struct SPI_Pin
{
    /**
     * @brief Structure defining the pin mappings for SPI1.
     */
    struct _SPI1_
    {
        /**
         * @brief CLK pin mappings for SPI1.
         */
        struct CLK1
        {
            uint8_t PA5; /**< Pin PA5 for SPI1 CLK. */
            uint8_t PB3; /**< Pin PB3 for SPI1 CLK. */
        } CLK1;

        /**
         * @brief MOSI pin mappings for SPI1.
         */
        struct MOSI1
        {
            uint8_t PA7; /**< Pin PA7 for SPI1 MOSI. */
            uint8_t PB5; /**< Pin PB5 for SPI1 MOSI. */
        } MOSI1;

        /**
         * @brief MISO pin mappings for SPI1.
         */
        struct MISO1
        {
            uint8_t PA6; /**< Pin PA6 for SPI1 MISO. */
            uint8_t PB4; /**< Pin PB4 for SPI1 MISO. */
        } MISO1;

    } _SPI1_;

    /**
     * @brief Structure defining the pin mappings for SPI2.
     */
    struct _SPI2_
    {
        /**
         * @brief CLK pin mappings for SPI2.
         */
        struct CLK2
        {
            uint16_t PB10; /**< Pin PB10 for SPI2 CLK. */
            uint16_t PB13; /**< Pin PB13 for SPI2 CLK. */
        } CLK2;

        /**
         * @brief MOSI pin mappings for SPI2.
         */
        struct MOSI2
        {
            uint16_t PC3;  /**< Pin PC3 for SPI2 MOSI. */
            uint16_t PB15; /**< Pin PB15 for SPI2 MOSI. */
        } MOSI2;

        /**
         * @brief MISO pin mappings for SPI2.
         */
        struct MISO2
        {
            uint16_t PC2;  /**< Pin PC2 for SPI2 MISO. */
            uint16_t PB14; /**< Pin PB14 for SPI2 MISO. */
        } MISO2;

    } _SPI2_;

    /**
     * @brief Structure defining the pin mappings for SPI3.
     */
    struct _SPI3_
    {
        /**
         * @brief CLK pin mappings for SPI3.
         */
        struct CLK3
        {
            uint16_t PC10; /**< Pin PC10 for SPI3 CLK. */
            uint16_t PB3;  /**< Pin PB3 for SPI3 CLK. */
        } CLK3;

        /**
         * @brief MOSI pin mappings for SPI3.
         */
        struct MOSI3
        {
            uint16_t PC12; /**< Pin PC12 for SPI3 MOSI. */
            uint16_t PB5;  /**< Pin PB5 for SPI3 MOSI. */
        } MOSI3;

        /**
         * @brief MISO pin mappings for SPI3.
         */
        struct MISO3
        {
            uint16_t PC11; /**< Pin PC11 for SPI3 MISO. */
            uint16_t PB4;  /**< Pin PB4 for SPI3 MISO. */
        } MISO3;

    } _SPI3_;

} SPI_Pin;

/**
 * @brief Structure defining the SPI ports available on the microcontroller.
 *
 * This structure contains pointers to the SPI1, SPI2, and SPI3 peripherals.
 */
typedef struct SPI_Ports
{
    SPI_TypeDef *_SPI1_; /**< Pointer to SPI1 peripheral. */
    SPI_TypeDef *_SPI2_; /**< Pointer to SPI2 peripheral. */
    SPI_TypeDef *_SPI3_; /**< Pointer to SPI3 peripheral. */

} SPI_Ports;

/**
 * @brief Structure containing the complete SPI configuration.
 *
 * This structure defines all the necessary configurations for the SPI peripheral,
 * including mode, CRC, data format, frame format, clock settings, type, interrupts,
 * DMA, prescaler, and pin mappings.
 */
static const struct SPI_Configurations
{
    SPI_Mode Mode;                              /**< SPI mode configuration. */
    SPI_CRC CRC_Enable;                         /**< SPI CRC enable/disable. */
    SPI_Data_Format Data_Format;                /**< SPI data format configuration. */
    SPI_Frame_Format Frame_Format;              /**< SPI frame format configuration. */
    SPI_Clock_Phase_and_Polarity Clock_Phase;   /**< SPI clock phase configuration. */
    SPI_Clock_Phase_and_Polarity Clock_Polarity;/**< SPI clock polarity configuration. */
    SPI_Type Type;                              /**< SPI type configuration (Master/Slave). */
    SPI_Interrupt Interrupts;                   /**< SPI interrupt configuration. */
    SPI_DMA DMA_Type;                           /**< SPI DMA configuration. */
    SPI_Prescaler Prescaler;                    /**< SPI clock prescaler configuration. */
    SPI_Pin Pin;                                /**< SPI pin configuration. */
} SPI_Configurations =
{
		.Mode = {
				.Full_Duplex_Master = 11,
				.Full_Duplex_Slave  = 12,
				.Half_Duplex_Master  = 13,
				.Half_Duplex_Slave = 14,
				.RX_Only_Master = 15,
				.RX_Only_Slave = 16,
				.TX_Only_Master = 17,
				.TX_Only_Slave = 18,
				},

		.CRC_Enable = {
			    .Enable = 1,
			    .Disable = 0,
		},

		.Data_Format = {
				.Bit8 = 11,
				.Bit16 = 12,
		},

		.Frame_Format = {
				.MSB_First = 23,
				.LSB_First = 24,
		},

		.Clock_Phase = {
				.High_1 = 22,
				.Low_0 = 23,
		},

		.Clock_Polarity = {
				.High_1 = 32,
				.Low_0 = 33,
		},

		.Type = {
				.Master = 50,
				.Slave = 51,
		},

		.Interrupts = {
				.Tx_Buffer_Empty = 73,
				.RX_Buffer_not_Empty = 72,
				.Error = 71,
				.Disable = 70,
		},

		.DMA_Type = {
				.TX_DMA_Enable  = 61,
				.TX_DMA_Disable = 62,
				.RX_DMA_Enable  = 63,
				.RX_DMA_Disable = 64,
		},

		.Prescaler = {

				.CLK_div_2 = 40,
				.CLK_div_4 = 41,
				.CLK_div_8 = 42,
				.CLK_div_16 = 43,
				.CLK_div_32 = 44,
				.CLK_div_64 = 45,
				.CLK_div_128 = 46,
				.CLK_div_256 = 47,
		},

		.Pin = {

				._SPI1_ = {

						.CLK1 = {
							.PA5 = 15,
							.PB3 = 33,
						},

						.MOSI1 = {
							.PA7 = 17,
							.PB5 = 35,
						},

						.MISO1 = {
							.PA6 = 16,
							.PB4 = 34,
						},

					},

				._SPI2_ = {

						.CLK2 = {
							.PB10 = 19,
							.PB13 = 23,
						},

						.MOSI2 = {
							.PC3 = 17,
							.PB15 = 29,
						},

						.MISO2 = {
							.PC2 = 32,
							.PB14 = 27,
						},

					},

				._SPI3_ = {

						.CLK3 = {
							.PC10 = 37,
							.PB3 = 23,
						},

						.MOSI3 = {
							.PC12 = 39,
							.PB5 = 25,
						},

						.MISO3 = {
							.PC11 = 39,
							.PB4 = 24,
						},

					},
		},
};






#endif /* SPI_DEFS_H_ */
