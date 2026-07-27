/*
 * stm32l452xx_spi_driver.c
 *
 *  Created on: Jul 13, 2026
 *      Author: cdac
 */


#include "stm32l452xx_spi_driver.h"


void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
		if(EnorDi == ENABLE)
		{
			if(pSPIx == SPI1)
			{
				SPI1_PCLK_EN();
			}
			else if(pSPIx == SPI2)
			{
				SPI2_PCLK_EN();
			}
			else if(pSPIx == SPI3)
			{
				SPI3_PCLK_EN();
			}
		}
}

void SPI_Init(SPI_Handle_t *pSPIHandle)
{
	//Configure the SPI_CR1 register
	uint32_t temp_reg = 0;

	//1.Configure the device mode
	temp_reg |= pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR;

	//2.Configure the bus config
	if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		//BIMODE to be cleared
		temp_reg &= ~(1<< SPI_CR1_BIDIMODE);
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		//BIMODE to be set
		temp_reg |= (1<< SPI_CR1_BIDIMODE);
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig ==  SPI_BUS_CONFIG_SIMPLEX_RXONLY)
	{
	    //BITMODE to be cleared
		temp_reg &= ~(1<< SPI_CR1_BIDIMODE);

		//RXonly bit to be set
		temp_reg |= (1<< SPI_CR1_RX_ONLY);
	}

	//3.Configure the serial clock speed of spi(baud rate)
	temp_reg |= pSPIHandle->SPIConfig.SPI_SclkSpeed << SPI_CR1_BR;

	//4. Configure the Data frame
	temp_reg |= pSPIHandle->SPIConfig.SPI_DFF << SPI_CR2_DS;

	//5.Configure the CPOL
	temp_reg |= pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPOL ;

	//6.Configure the CPHA
	temp_reg |= pSPIHandle->SPIConfig.SPI_CPHA << SPI_CR1_CPHA;

	//Assign the temp_reg value to the CR1 register of SPI
	pSPIHandle->pSPIx->CR1 = temp_reg;
}

/*void SPI_DeInit()
{

}*/

uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPI, uint32_t FlagName)
{
	if(pSPI->SR & FlagName)
	{
		return FLAG_SET;

	}
	return FLAG_RESET;
}

void SPI_SendData(SPI_RegDef_t *pSPI, uint8_t *pTxBuffer, uint32_t Len) //Len is number of bytes
{
	while(Len > 0)
	{
		//1. wait until  TXE is set
		while(SPI_GetFlagStatus(pSPI, SPI_TXE_FLAG) == FLAG_RESET);

		//2.Check the DFF bit in CR2 is less than or equal to 8 bits
		if((pSPI->CR2 & ( 15 << SPI_CR2_DS)) <= 8)
		{
			//Equal or less than 8 bit we will fix as 8 bit frame.
			//load the data in to DR.
			pSPI->DR = *((uint8_t*)(pTxBuffer));
			Len--;
			pTxBuffer++;
		}
		else
		{
			//more than 8 bits we will fix as 16 bit frame.
			pSPI->DR = *((uint16_t*)pTxBuffer);
			Len--;
			Len--;
			(uint16_t*)pTxBuffer++;
		}


	}
}
