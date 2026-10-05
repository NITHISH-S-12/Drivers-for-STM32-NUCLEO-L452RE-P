/*
 * 008spi_cmd_handling.c
 *
 *  Created on: Oct 5, 2026
 *      Author: cdac
 */



/*
 * SPI2_Send_Data_Tx.c
 *
 *  Created on: Sep 26, 2026
 *      Author: ubuntu
 */

#include<string.h>
#include<stm32l452xx.h>
#include<stm32l452xx_gpio_driver.h>
#include<stm32l452xx_spi_driver.h>

/*
PB 14  ==> SPI2_MISO
PB 15  ==> SPI2_MOSI
PB 13  ==> SPI2_SCLK
PB 12  ==> SPI2_NSS
ALT Function mode is 5
*/

void SPI2_GPIOInits(void)
{
	GPIO_Handle_t SPIPins;

	SPIPins.pGPIOx = GPIOB;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;

    //SCLK
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&SPIPins);

	//MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPIPins);

	//MISO
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	GPIO_Init(&SPIPins);

	//NSS
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GPIO_Init(&SPIPins);



}

void SPI2_Inits(void)
{
	SPI_Handle_t SPI2handle;
	SPI2handle.pSPIx =  SPI2;
	SPI2handle.SPIConfig.SPI_BusConfig  = SPI_BUS_CONFIG_FD;
	SPI2handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV2;//Generate SCLK as 2MHz
	SPI2handle.SPIConfig.SPI_DFF =SPI_DFF_8BITS;
	SPI2handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2handle.SPIConfig.SPI_SSM = SPI_SSM_DI;//Hardware slave management enabled for NSS pin

	SPI_Init(&SPI2handle);
}


void GPIO_ButtonInit(void)
{
	    GPIO_Handle_t GpioBtn;
	    //Button Gpio Configuration
		GpioBtn.pGPIOx = GPIOC;
		GpioBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
		GpioBtn.GPIO_PinConfig.GPIO_PinMode  = GPIO_MODE_IN;
		GpioBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	    GpioBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	    //GPIO_PeriClockControl(GPIOC, ENABLE); (no need to enable the clock because we have enable the peripheral clock in GPIO_Init
	    GPIO_Init(&GpioBtn);

}

void delay(void)
{
	//for(volatile uint32_t i=0; i < 500000; i++);

	   for(volatile uint32_t i=0; i < 500000/4	; i++)
	    {
	        //i++;// empty
	    }
}


int main(void)
{

	//Init the Button
	GPIO_ButtonInit();

	//This function is used to initialize the GPIO pins to behave as SPI2 pins
	SPI2_GPIOInits();

	//This function is to initialize the SPI peripheral
	SPI2_Inits();

	/*making SSOE 1 does NSS output enable.
	The NSS pin is automatically managed by the hardware.
	i.e when SPE=1, NSS will be pulled to low
	and NSS pin will be high when SPE=0
	*/
	SPI_SSOEConfig(SPI2, ENABLE);

	while(1)
	{
	//wait till button is pressed
	while(!GPIO_ReadFromInputPin(GPIOC,GPIO_PIN_NO_13))

	//To avoid button de-bouncing related isssues
	 delay();

	//Enable the SPI2 Peripheral
	SPI_PeripheralControl(SPI2, ENABLE);


	//Confirm whether SPI is not busy
	while( SPI_GetFlagStatus(SPI2,SPI_BUSY_FLAG))

	//Enable the SPI peripheral
	SPI_PeripheralControl(SPI2, DISABLE);




	//Send data
	SPI_SendData(SPI2, user_data, strlen(user_data));




	return 0;
}

