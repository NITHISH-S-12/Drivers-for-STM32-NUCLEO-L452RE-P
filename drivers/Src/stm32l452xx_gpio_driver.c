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
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	uint32_t temp = 0;
	// 1.Configure the mode of GPIO pin

	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		//Non interrupt mode(less or equal to 3 of GPIO_PIN_MODES
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));

		//clear the bits at the specific position in MODER register
		pGPIOHandle->pGPIOx->MODER &= ~(0x3 << (2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));

		//We will place the temp value to corresponding MODER register
		pGPIOHandle->pGPIOx->MODER |= temp; //We should use bitwise or instead of assignment operator because we shouldnot change the content which is there already in a particular register
 	}
	else
	{
		//Interrupt Mode
		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
		{
			//Configure the Falling trigger selection register(FTSR)
			EXTI->FTSR1 |= (1<< pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			//Clear the corresponding RTSR bit because previous configuration may enable this bit)
			EXTI->RTSR1 &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
		{
			//Configure the Rising trigger selection register(RTSR)
			EXTI->RTSR1 |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			//Clear the corresponding FTSR bit because previous configuration may enable this bit)
			EXTI->FTSR1 &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
		{
			//Configure both FTSR and RTSR
			EXTI->FTSR1 |= (1<< pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->RTSR1 |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

		}
		//2. Configure the GPIO port selection in SYSCFG_EXTICR
		uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 3;
		uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 3;
		uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
		SYSCFG_PCLK_EN();
		SYSCFG->EXTICR[temp1] = portcode << (4*temp2);

		//3. Enable the EXTI interrupt delivery using the IMR register
		EXTI->IMR1 |= (1<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	}

	temp = 0;

	//2.Configure the speed
	//Reset the temp value
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));

	//clear the bits at the specific position in speed register
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << (2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));

	//set the bits at the corresponding bit positions for that specific pin number in speed register
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;

	temp = 0;

	//3.Configure the pupd settings
	temp = (pGPIOHandle-> GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));

	//clear the bits at the corresponding bit positions for that specific pin number
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));

	//set the bits at the corresponding bit positions for that specific pin number in pupd register
	pGPIOHandle->pGPIOx->PUPDR |= temp;

	temp = 0;

	//4.Configure the output type functionality in pupd register
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));

	//clear the bits at the corresponding bit positions for that specific pin number in output type register
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

	//set the bits at the corresponding bit positions for that specific pin number in output type register
	pGPIOHandle->pGPIOx->OTYPER |= temp;

	temp = 0;
	//5.Configure the alt function of register
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
	{
		uint32_t temp1, temp2;
		temp1 = (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber/8); //decide AFR[0] or AFR[1]
		temp2 = (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber%8); //shifting the bits to the bits position of pin number in AFR register to change the alternate mode of that pin.

		//clear the bits at the corresponding bit positions for that specific pin number in the alt function register
		pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4 * temp2));

		//set the bits at the corresponding bit positions for that specific pin number in the alt function register
		pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4*temp2));
	}
}

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{

//Reset the GPIOs register uisng the RCC_AHB2RSTR register

			if(pGPIOx == GPIOA)
			{
				GPIOA_REG_RESET();
			}
			else if(pGPIOx == GPIOB)
			{
				GPIOB_REG_RESET();
			}
			else if(pGPIOx == GPIOC)
			{
				GPIOC_REG_RESET();
			}
			else if(pGPIOx == GPIOD)
			{
				GPIOD_REG_RESET();
			}
			else if(pGPIOx == GPIOE)
			{
				GPIOE_REG_RESET();
			}
			else
			{
				GPIOH_REG_RESET();
			}
}

/*
 * Data Read and Write
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)/*Read the value from input pin*//*Input based address of GPIO, pinnumber(totally 16 pins in each port so 8 bits is enough to represent pin number) nad value will be either  0 0r 1 in that pin so return type will b	e uint8_t*/
{
	uint8_t value;
	value = (uint8_t)((pGPIOx->IDR >> PinNumber)& 0x00000001);
	return value;
}

uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)/*Read the value from input port*/ /*returntype is uint16_t because the value in each pin of port(16pins in each port)*/
{
	uint8_t value;
	value = (uint16_t)(pGPIOx->IDR);
	return value;
}
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t pinNumber, uint8_t Value)/*Write the value to output pin*/
{
	if(Value == GPIO_PIN_SET)
	{
		//Write 1 to the output data register at the bit field corresponding to the pin number
		pGPIOx->ODR |= 1 << pinNumber;
	}
	else
	{
		//Write 0 to the output data register at the bit field corresponding to the pin number
		pGPIOx->ODR &= ~(1 << pinNumber);
	}
}
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value)/*Write the value to output port*/
{
	pGPIOx->ODR |= Value;
}

void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)/*To toggle the output pin*/
{
	pGPIOx->ODR ^= (1 << PinNumber);

}

/*
 * IRQ Configuration and ISR handling
*/
/*Configure the IRQ number of GPIO pin(enabling and setup the interrupt number)*/
void GPIO_IRQInterrruptConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(IRQNumber <= 31)
		{
			//Program ISER0 register
			*NVIC_ISER0 |= (1 << IRQNumber);  //for upto 31 IRQ Number
		}
		else if(IRQNumber > 32 && IRQNumber < 64)
		{
			//Program ISER1 register
			*NVIC_ISER1 |= (1 << IRQNumber%32); //for upto 32 to 64 IRQ Number
		}
		else if(IRQNumber >= 64 && IRQNumber < 96)
		{
			//Program ISER2 register 		 //for upto 64 to 95 IRQ Number
			*NVIC_ISER2 |= (1 << IRQNumber%64); //for upto 32 to 64 IRQ Number
		}

	}
	else
	{
				if(IRQNumber <= 31)
				{
					*NVIC_ICER0 |= (1 << IRQNumber);  //for upto 31 IRQ Number//Program ICER0 register
				}
				else if(IRQNumber > 32 && IRQNumber < 64)
				{
				}
				else if(IRQNumber >= 64 && IRQNumber < 96)
				{
					*NVIC_ICER2 |= (1 << IRQNumber%64); //for upto 32 to 64 IRQ Number//Program ICER2 register
				}

	}
}
//void GPIO_IRQHandling(uint8_t PinNumber);/*IRQ handling means whenever the interrupt triggers the user application, then the user application call this IRQ handling function t

