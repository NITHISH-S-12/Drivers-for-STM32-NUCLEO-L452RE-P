/*
 * 001led_toggle.c
 *
 *  Created on: Jul 29, 2026
 *      Author: cdac
 */
#include "stm32l452xx.h"
#include "stm32l452xx_gpio_driver.h"

void delay(void)
{
	//for(volatile uint32_t i=0; i < 500000; i++);

	   for(volatile uint32_t i=0; i < 500000; i++)
	    {
	        //i++;// empty
	    }
}
int main (void)
{
	GPIO_Handle_t GpioLed;
	GpioLed.pGPIOx = GPIOB;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GpioLed.GPIO_PinConfig.GPIO_PinMode  = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    GPIO_PeriClockControl(GPIOB, ENABLE);
    GPIO_Init(&GpioLed);

    while(1)
    {
    	//GPIO_ToggleOutputPin(GPIOB, GPIO_PIN_NO_13);
    	//delay();

    	//GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_13, 1);
    	//delay();
    	GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_13, 0);
    	delay();
    }
    return 0;

}
