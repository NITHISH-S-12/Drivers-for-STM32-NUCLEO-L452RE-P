/*
 * stm32l452xx_gpio_driver.c
 *
 *  Created on: Jul 24, 2026
 *      Author: cdac
 */

#include "stm32l452xx_gpio_driver.h"



/*********************************************************************
 * @fn              - GPIO_Init
 *
 * @brief           - Initializes the peripheral GPIOx pin according to the specified parameters.
 *
 * @param[in]       - GPIOx: Base address of the GPIO peripheral port (e.g., GPIOA, GPIOB).
 * @param[in]       - PinNumber: The specific pin to configure (e.g., 0 to 15).
 * @param[in]       - pGPIOConfig: Pointer to the configuration structure containing mode, speed, and pull-up/down settings.
 *
 * @return          - None
 *
 * @Note            - Ensure the peripheral clock for the given GPIO port is enabled before calling this function.
 */

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();
		}
		else
		{
			GPIOH_PCLK_EN();
		}
	}
	else
	{
		if(pGPIOx == GPIOA)
				{
					GPIOA_PCLK_DI();
				}
				else if(pGPIOx == GPIOB)
				{
					GPIOB_PCLK_DI();
				}
				else if(pGPIOx == GPIOC)
				{
					GPIOC_PCLK_DI();
				}
				else if(pGPIOx == GPIOD)
				{
					GPIOD_PCLK_DI();
				}
				else if(pGPIOx == GPIOE)
				{
					GPIOE_PCLK_DI();
				}
				else
				{
					GPIOH_PCLK_DI();
				}

	}

}

/*
 * Init and Deinit
 */
void GPIO_Init(GPIO_RegDef_t *pGPIOx)
{

}
void GPIO_DeInit(void)
{

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
void GPIO_IRQHandling(uint8_t PinNumber);/*IRQ handling means whenever the interrupt triggers the user application, then the user application call this IRQ handling function t
