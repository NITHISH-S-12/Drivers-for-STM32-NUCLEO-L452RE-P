/*
 * stm32l452xx_spi_driver.h
 *
 *  Created on: Jul 13, 2026
 *      Author: cdac
 */

#ifndef INC_STM32L452XX_SPI_DRIVER_H_
#define INC_STM32L452XX_SPI_DRIVER_H_


#include "stm32l452xx.h"

/*
 * Configuration structure for SPIx peripheral
 */

typedef struct
{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_SclkSpeed;
	uint8_t SPI_DFF;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;

}SPI_Config_t;


/*
 * Handle Structure for SPIx peripheral
 */
typedef struct
{
	SPI_RegDef_t *pSPIx; /*!<Holds the base address of SPIx(x:0,1,2) >*/
	SPI_Config_t SPIConfig;
}SPI_Handle_t;

#endif /* INC_STM32L452XX_SPI_DRIVER_H_ */



/*
 * @SPI_DeviceMode
 */
#define SPI_DEVICE_MODE_MASTER 1
#define SPI_DEVICE_MODE_SLAVE  0

/*
 * @SPI_BusConfig
 */
#define SPI_BUS_CONFIG_FD	1
#define SPI_BUS_CONFIG_HD   2
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY 3

/*
 * @SPI_Sclk_Speed
 */
#define SPI_SCLK_SPEED_DIV2		0
#define SPI_SCLK_SPEED_DIV4		1
#define SPI_SCLK_SPEED_DIV8		2
#define SPI_SCLK_SPEED_DIV16	3
#define SPI_SCLK_SPEED_DIV32	4
#define SPI_SCLK_SPEED_DIV64	5
#define SPI_SCLK_SPEED_DIV128	6
#define SPI_SCLK_SPEED_DIV256	7


/*
 *@SPI_DFF
 */
#define SPI_DFF_4BITS	4
#define SPI_DFF_5BITS   5
#define SPI_DFF_6BITS	6
#define SPI_DFF_7BITS	7
#define SPI_DFF_8BITS	8​
#define SPI_DFF_9BITS	9
#define SPI_DFF_10BITS	10
#define SPI_DFF_11BITS	11
#define SPI_DFF_12BITS	12
#define SPI_DFF_13BITS	13
#define SPI_DFF_14BITS	14
#define SPI_DFF_15BITS	15
#define SPI_DFF_16BITS	16


/*
 *@CPOL
 */
#define SPI_CPOL_HIGH	0
#define SPI_CPOL_LOW	1

/*
 * @CPHA
 */
#define SPI_CPHA_HIGH	0
#define SPI_CPHA_LOW	1

/*
 * @SPI_SSM
 */
#define SPI_SSM_DI 		0
#define SPI_SSM_EN		1


/*
 * @SPI related flag definition register
 */
#define SPI_TXE_FLAG   	(1 << SPI_SR_TXE)
#define SPI_RXNE_FLAG   (1 << SPI_SR_RXNE)
#define SPI_BUSY_FLAG	(1 << SPI_SR_BSY)

/*
 *  Peripheral Clock Setup
 */
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);


/*
 * Init  and De-init
 */
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);


/*
 * Data Send and Receive
 */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);
