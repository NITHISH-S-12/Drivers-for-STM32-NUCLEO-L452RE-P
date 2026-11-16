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
	uint8_t *pTxBuffer;  /*!<To store the app. Tx buffer address>*/
	uint8_t *RxBuffer;	 /*!<To store the app. Rx buffer address>*/
	uint32_t *TxLen;	 /*!<To store Tx Len>*/
	uint32_t *RxLen;	 /*!<To store Rx Len>*/
	uint8_t  *TxState	 /*!<To store Tx state>*/
	uint8_t  *Rxstate 	 /*!<To store Rx state>*/
}SPI_Handle_t;


/*
 * SPI application states
 */
#define SPI_READY			0
#define SPI_BUSY_IN_RX		1
#define SPI_BUSY_IN_TX		2

#endif /* INC_STM32L452XX_SPI_DR	/*
	 * IRQ Configuration and ISR handling
	 */

	void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);/*Configure the IRQ number of GPIO pin(enabling and setup the interrupt number)*/
	void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
	void GPIO_IRQHandling(uint8_t PinNumber);/*IRQ handling means whenever the interrupt triggers the user application, then the user application call this IRQ handling function to process the interrupt*/
IVER_H_ */



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
#define SPI_DFF_4BITS	3
#define SPI_DFF_5BITS   4
#define SPI_DFF_6BITS	5
#define SPI_DFF_7BITS	6
#define SPI_DFF_8BITS 	7
#define SPI_DFF_9BITS	8
#define SPI_DFF_10BITS	9
#define SPI_DFF_11BITS	10
#define SPI_DFF_12BITS	11
#define SPI_DFF_13BITS	12
#define SPI_DFF_14BITS	13
#define SPI_DFF_15BITS	14
#define SPI_DFF_16BITS	15


/*
 *@CPOL
 */
#define SPI_CPOL_LOW	0
#define SPI_CPOL_HIGH	1

/*
 * @CPHA
 */
#define SPI_CPHA_LOW	0
#define SPI_CPHA_HIGH	1

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


/*
 *
 */
uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t Len);
uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Len);


/*
 *SPI FLag Status
 */
uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPI, uint32_t FlagName);

/*
 *  Enable or Disable SPI Peripheral
 */
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx , uint8_t EnOrDi);

/*
 *  Enable or Disable SSI bit in the SPI control Register.
 */
void SPI_SSIConfig(SPI_RegDef_t *pSPIx , uint8_t EnOrDi);

/*
 *  Enable or Disable SSOE
 */
void SPI_SSOEConfig(SPI_RegDef_t *pSPIx , uint8_t EnOrDi);

/*
 * IRQ Configuration and ISR handling
 */
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);/*Configure the IRQ number of GPIO pin(enabling and setup the interrupt number)*/

void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);

void SPI_IRQHandling(SPI_Handle_t *pHandle);/*IRQ handling means whenever the interrupt triggers the user application, then the user application call this IRQ handling function to process the interrupt*/
