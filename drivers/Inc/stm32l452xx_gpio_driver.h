/*
 * stm32l452xx_gpio_driver.h
 *
 *  Created on: Jul 24, 2026
 *      Author: cdac
 */

#ifndef INC_STM32L452XX_GPIO_DRIVER_H_
#define INC_STM32L452XX_GPIO_DRIVER_H_

#include "stm32l452xx.h"


/*
 *Configuration Structure for a GPIO pin
 */
typedef struct
{
	uint8_t GPIO_PinNumber;    /*possible values from @GPIO_PIN_NUMBERS*/
	uint8_t GPIO_PinMode;      /*possible values from @GPIO_PIN_MODES */
	uint8_t GPIO_PinSpeed;	   /*possible values from @GPIO_PIN_SPEED */
	uint8_t GPIO_PinPuPdControl;
	uint8_t GPIO_PinOPType;
	uint8_t GPIO_PinAltFunMode;

}GPIO_PinConfig_t;
/*
 * Handle structure for a GPIO pin
 */
typedef struct
{
	GPIO_RegDef_t *pGPIOx;  /*This hold the base address of the GPIO port to which the pin belong*/
	GPIO_PinConfig_t GPIO_PinConfig; /*This holds GPIO pin configuration settings*/

}GPIO_Handle_t;


/*
 *GPIO_PIN_NUMBERS
 *GPIO PIN NUMBERS
 */
#define 	GPIO_PIN_NO_0			0
#define 	GPIO_PIN_NO_1			1
#define 	GPIO_PIN_NO_2			2
#define		GPIO_PIN_NO_3			3
#define		GPIO_PIN_NO_4			4
#define		GPIO_PIN_NO_5			5
#define		GPIO_PIN_NO_6			6
#define		GPIO_PIN_NO_7			7
#define		GPIO_PIN_NO_8			8
#define		GPIO_PIN_NO_9			9
#define		GPIO_PIN_NO_10			10
#define		GPIO_PIN_NO_11			11
#define		GPIO_PIN_NO_12			12
#define		GPIO_PIN_NO_13			13
#define		GPIO_PIN_NO_14			14
#define		GPIO_PIN_NO_15			15
/*
 * GPIO_PIN_MODES
 * GPIO pin possible modes
 */
#define GPIO_MODE_IN 		0
#define GPIO_MODE_OUT       1
#define GPIO_MODE_ALTFN 	2
#define GPIO_MODE_ANALOG	3
/*When the  pin is in input mode , we can configure the GPIO pin to deliver an interrupt when the falling edge or rising edge is detected on the pin*/
#define GPIO_MODE_IT_FT     4 //Input mode falling edge trigger
#define GPIO_MODE_IT_RT 	5 //Input mode Rising edge trigger
#define GPIO_MODE_IT_RFT	6 //Input mode Rising and falling edge trigger

/*
 * GPIO pin possible output types
 */
#define GPIO_OP_TYPE_PP		0 //Output type is push pull
#define GPIO_OP_TYPE_OD		1//Output type is open drain

/*
 *GPIO_PIN_SPEED
 *GPIO pin possible output speeds
 */
#define GPIO_SPEED_LOW		0
#define GPIO_SPEED_MEDIUM	1
#define GPIO_SPEED_HIGH		2
#define GPIO_SPEED_VERYHIGH 3

/*
 * GPIO pull up and Pull down Configuration macros
 */
#define GPIO_NO_PUPD		0
#define GPIO_PIN_PU			1
#define GPIO_PIN_PD			2
/**
 * API supported by the GPIO driver
 */
/*
 * Peripheral Clock Setup
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi); /*Enable or Disable the peripheral clock of that port*//*input:base address of GPIO and enableordiable value*/

/*
 * INit and Deinit
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle); /*Initialize the given GPIO port and pin*/ /*Input is base address of GPIO*/
void GPIO_DeInit(void); /*Deinitialize the given GPIO port and pin(giving GPIO port settings to reset state)*/

/*
 * Data Read and Write
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber); /*Read the value from input pin*//*Input based address of GPIO, pinnumber(totally 16 pins in each port so 8 bits is enough to represent pin number) nad value will be either  0 0r 1 in that pin so return type will b	e uint8_t*/
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);/*Read the value from input port*/ /*returntype is uint16_t because the value in each pin of port(16pins in each port)*/
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t pinNumber, uint8_t Value);/*Write the value to output pin*/
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx);/*Write the value to output port*/
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);/*To toggle the output pin*/

/*
 * IRQ Configuration and ISR handling
 */
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi);/*Configure the IRQ number of GPIO pin(enabling and setup the interrupt number)*/
void GPIO_IRQHandling(uint8_t PinNumber);/*IRQ handling means whenever the interrupt triggers the user application, then the user application call this IRQ handling function to process the interrupt*/

#endif /* INC_STM32L452XX_GPIO_DRIVER_H_ */


