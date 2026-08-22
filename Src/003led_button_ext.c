/*
 * 003led_button_ext.c
 *
 *  Created on: Jul 31, 2026
 *      Author: cdac
 */



#include "stm32l452xx.h"
#include "stm32l452xx_gpio_driver.h"

#define HIGH 			1
#define LOW 			0
#define BTN_PRESSED 	LOW
void delay(void)
{
	//for(volatile uint32_t i=0; i < 500000; i++);

	   for(volatile uint32_t i=0; i < 500000/4	; i++)
	    {
	        //i++;// empty
	    }
}
int main (void)
{
	GPIO_Handle_t GpioLed, GpioBtn;

	//Led Gpio Configuration
	GpioLed.pGPIOx = GPIOB;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GpioLed.GPIO_PinConfig.GPIO_PinMode  = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;


    GPIO_PeriClockControl(GPIOB , ENABLE);
    GPIO_Init(&GpioLed);


    //Button Gpio Configuration
	GpioBtn.pGPIOx = GPIOC;
	GpioBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GpioBtn.GPIO_PinConfig.GPIO_PinMode  = GPIO_MODE_IN;
	GpioBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
    GpioBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    GPIO_PeriClockControl(GPIOC, ENABLE);
    GPIO_Init(&GpioBtn);
    while(1)
    {

    	if(GPIO_ReadFromInputPin(GPIOC,GPIO_PIN_NO_13) == BTN_PRESSED)
    	{
    	  delay();//This delay given because to give time for debouncing of user button, other wise this loop executes multiple times
    	  GPIO_WriteToOutputPin(GPIOB,GPIO_PIN_NO_13, ENABLE);
    	}



    }
    return 0;

}
void I2C1_EV_IRQHandler(void)
{

}
