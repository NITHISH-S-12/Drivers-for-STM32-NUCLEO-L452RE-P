/*
 * stm32l452xx.h
 *
 *  Created on: Jul 9, 2026
 *      Author: cdac
 */

#ifndef INC_STM32L452XX_H_
#define INC_STM32L452XX_H_

#include<stdint.h>
#define __vo volatile

/****************************************PROCESSOR SPCIFIC DETAILS*****************************************/
/*
 * ARM Cortex Mx Processor NVIC ISERx register Addresses
 */
#define NVIC_ISER0 			((__vo uint32_t*)0xE000E100)
#define NVIC_ISER1 			((__vo uint32_t*)0xE000E104)
#define NVIC_ISER2 			((__vo uint32_t*)0xE000E108)
#define NVIC_ISER3 			((__vo uint32_t*)0xE000E10C)


/*
 * ARM Cortex Mx Processor NVIC ICERx register Addresses
 */
#define NVIC_ICER0 			((__vo uint32_t*)0XE000E180)
#define NVIC_ICER1 			((__vo uint32_t*)0XE000E184)
#define NVIC_ICER2 			((__vo uint32_t*)0XE000E188)
#define NVIC_ICER3 			((__vo uint32_t*)0XE000E18C)


/*
 * ARM Cortex Mx Processor NVIC ICERx register Addresses
 */
#define NVIC_PR_BASE_ADDR 	((__vo uint32_t*)0xE000E400)

/*
 * ARM Cortex Mx Processor number of priority bits implemented in Priority Register
 */
#define NO_PR_BITS_IMPLEMENTED		4

/*
 * Base addresses of Flash and SRAM memories
 */

#define FLASH_BASEADDR				0x08000000U /*Refer Reference Manual(pg 82)*/
#define SRAM1_BASEADDR				0x20000000U /*Refer Reference Manual(pg 71) 128KB*/
#define SRAM2_BASEADDR 				0x20020000U /*this is after SRAM1(128*1024 = 131072 , in hex = 20000), in reference manual it is mentioned as (1)*/
#define ROM_BASEADDR                0x1FFF0000U /*Refer RF(pg 82) or (pg 71)*/
#define SRAM						SRAM1_BASEADDR


/*
 * Base addresses of AHBx and APBx Bus peripherals
 */
#define PERIPH_BASE					   0x40000000U/*Refer Refer Reference Manual(pg 71)*/
#define APB1PERIPH_BASE                PERIPH_BASE/*Refer Refer Reference Manual(pg 71)*/
#define APB2PERIPH_BASE				   0x40010000U/*Refer Refer Reference Manual(pg 71)*/
#define AHB1PERIPH_BASE				   0x40020000U/*Refer Refer Reference Manual(pg 71)*/
#define AHB2PERIPH_BASE				   0x48000000U/*Refer Refer Reference Manual(pg 71)*/



/*
 * Base addresses of peripherals which are hanging on the APB1 bus
 */
#define TIM2_BASE             (APB1PERIPH_BASE + 0x0000UL)
#define TIM3_BASE             (APB1PERIPH_BASE + 0x0400UL)
#define TIM6_BASE             (APB1PERIPH_BASE + 0x1000UL)
#define RTC_BASE              (APB1PERIPH_BASE + 0x2800UL)
#define WWDG_BASE             (APB1PERIPH_BASE + 0x2C00UL)
#define IWDG_BASE             (APB1PERIPH_BASE + 0x3000UL)
#define SPI2_BASE             (APB1PERIPH_BASE + 0x3800UL)
#define SPI3_BASE             (APB1PERIPH_BASE + 0x3C00UL)
#define USART2_BASE           (APB1PERIPH_BASE + 0x4400UL)
#define USART3_BASE           (APB1PERIPH_BASE + 0x4800UL)
#define UART4_BASE            (APB1PERIPH_BASE + 0x4C00UL)
#define I2C1_BASE             (APB1PERIPH_BASE + 0x5400UL)
#define I2C2_BASE             (APB1PERIPH_BASE + 0x5800UL)
#define I2C3_BASE             (APB1PERIPH_BASE + 0x5C00UL)
#define CRS_BASE              (APB1PERIPH_BASE + 0x6000UL)
#define CAN1_BASE             (APB1PERIPH_BASE + 0x6400UL)
#define USB_BASE              (APB1PERIPH_BASE + 0x6800UL)
#define USB_PMAADDR           (APB1PERIPH_BASE + 0x6C00UL)
#define I2C4_BASE             (APB1PERIPH_BASE + 0x8400UL)
#define PWR_BASE              (APB1PERIPH_BASE + 0x7000UL)
#define DAC_BASE              (APB1PERIPH_BASE + 0x7400UL)
#define DAC1_BASE             (APB1PERIPH_BASE + 0x7400UL)
#define OPAMP_BASE            (APB1PERIPH_BASE + 0x7800UL)
#define OPAMP1_BASE           (APB1PERIPH_BASE + 0x7800UL)
#define LPTIM1_BASE           (APB1PERIPH_BASE + 0x7C00UL)
#define LPUART1_BASE          (APB1PERIPH_BASE + 0x8000UL)
#define LPTIM2_BASE           (APB1PERIPH_BASE + 0x9400UL)


/*
 * Base addresses of peripherals which are hanging on the APB2 bus
 */
#define SYSCFG_BASE           (APB2PERIPH_BASE + 0x0000UL)
#define VREFBUF_BASE          (APB2PERIPH_BASE + 0x0030UL)
#define COMP1_BASE            (APB2PERIPH_BASE + 0x0200UL)
#define COMP2_BASE            (APB2PERIPH_BASE + 0x0204UL)
#define EXTI_BASE             (APB2PERIPH_BASE + 0x0400UL)
#define FIREWALL_BASE         (APB2PERIPH_BASE + 0x1C00UL)
#define SDMMC1_BASE           (APB2PERIPH_BASE + 0x2800UL)
#define TIM1_BASE             (APB2PERIPH_BASE + 0x2C00UL)
#define SPI1_BASE             (APB2PERIPH_BASE + 0x3000UL)
#define USART1_BASE           (APB2PERIPH_BASE + 0x3800UL)
#define TIM15_BASE            (APB2PERIPH_BASE + 0x4000UL)
#define TIM16_BASE            (APB2PERIPH_BASE + 0x4400UL)
#define SAI1_BASE             (APB2PERIPH_BASE + 0x5400UL)
#define SAI1_Block_A_BASE     (SAI1_BASE + 0x0004UL)
#define SAI1_Block_B_BASE     (SAI1_BASE + 0x0024UL)
#define DFSDM1_BASE           (APB2PERIPH_BASE + 0x6000UL)
#define DFSDM1_Channel0_BASE  (DFSDM1_BASE + 0x0000UL)
#define DFSDM1_Channel1_BASE  (DFSDM1_BASE + 0x0020UL)
#define DFSDM1_Channel2_BASE  (DFSDM1_BASE + 0x0040UL)
#define DFSDM1_Channel3_BASE  (DFSDM1_BASE + 0x0060UL)
#define DFSDM1_Filter0_BASE   (DFSDM1_BASE + 0x0100UL)
#define DFSDM1_Filter1_BASE   (DFSDM1_BASE + 0x0180UL)

/*
 * Base addresses of peripherals which are hanging on the AHB1 bus
 */
#define DMA1_BASE             (AHB1PERIPH_BASE)
#define DMA2_BASE             (AHB1PERIPH_BASE + 0x0400UL)
#define RCC_BASEADDR          (AHB1PERIPH_BASE + 0x1000UL)
#define FLASH_R_BASE          (AHB1PERIPH_BASE + 0x2000UL)
#define CRC_BASE              (AHB1PERIPH_BASE + 0x3000UL)
#define TSC_BASE              (AHB1PERIPH_BASE + 0x4000UL)


#define DMA1_Channel1_BASE    (DMA1_BASE + 0x0008UL)
#define DMA1_Channel2_BASE    (DMA1_BASE + 0x001CUL)
#define DMA1_Channel3_BASE    (DMA1_BASE + 0x0030UL)
#define DMA1_Channel4_BASE    (DMA1_BASE + 0x0044UL)
#define DMA1_Channel5_BASE    (DMA1_BASE + 0x0058UL)

/*
 * Base addresses of peripherals which are hanging on the AHB2 bus
 */
#define GPIOA_BASE            (AHB2PERIPH_BASE + 0x0000UL)
#define GPIOB_BASE            (AHB2PERIPH_BASE + 0x0400UL)
#define GPIOC_BASE            (AHB2PERIPH_BASE + 0x0800UL)
#define GPIOD_BASE            (AHB2PERIPH_BASE + 0x0C00UL)
#define GPIOE_BASE            (AHB2PERIPH_BASE + 0x1000UL)
#define GPIOH_BASE            (AHB2PERIPH_BASE + 0x1C00UL)


#define ADC1_BASE             (AHB2PERIPH_BASE + 0x08040000UL)
#define ADC1_COMMON_BASE      (AHB2PERIPH_BASE + 0x08040300UL)


#define RNG_BASE              (AHB2PERIPH_BASE + 0x08060800UL)



/*
 *Reset and Clock Control
 */

typedef struct
{
   __vo uint32_t CR;          /*!< RCC clock control register,                                              Address offset: 0x00 */
   __vo uint32_t ICSCR;       /*!< RCC internal clock sources calibration register,                         Address offset: 0x04 */
   __vo uint32_t CFGR;        /*!< RCC clock configuration register,                                        Address offset: 0x08 */
   __vo uint32_t PLLCFGR;     /*!< RCC system PLL configuration register,                                   Address offset: 0x0C */
   __vo uint32_t PLLSAI1CFGR; /*!< RCC PLL SAI1 configuration register,                                     Address offset: 0x10 */
  uint32_t      RESERVED;    /*!< Reserved,                                                               Address offset: 0x14 */
  __vo uint32_t CIER;        /*!< RCC clock interrupt enable register,                                     Address offset: 0x18 */
  __vo uint32_t CIFR;        /*!< RCC clock interrupt flag register,                                       Address offset: 0x1C */
  __vo uint32_t CICR;        /*!< RCC clock interrupt clear register,                                      Address offset: 0x20 */
  uint32_t      RESERVED0;   /*!< Reserved,                                                                Address offset: 0x24 */
  __vo uint32_t AHB1RSTR;    /*!< RCC AHB1 peripheral reset register,                                      Address offset: 0x28 */
  __vo uint32_t AHB2RSTR;    /*!< RCC AHB2 peripheral reset register,                                      Address offset: 0x2C */
  __vo uint32_t AHB3RSTR;    /*!< RCC AHB3 peripheral reset register,                                      Address offset: 0x30 */
  uint32_t      RESERVED1;   /*!< Reserved,                                                                Address offset: 0x34 */
  __vo uint32_t APB1RSTR1;   /*!< RCC APB1 peripheral reset register 1,                                    Address offset: 0x38 */
  __vo uint32_t APB1RSTR2;   /*!< RCC APB1 peripheral reset register 2,                                    Address offset: 0x3C */
  __vo uint32_t APB2RSTR;    /*!< RCC APB2 peripheral reset register,                                      Address offset: 0x40 */
  uint32_t      RESERVED2;   /*!< Reserved,                                                                Address offset: 0x44 */
  __vo uint32_t AHB1ENR;     /*!< RCC AHB1 peripheral clocks enable register,                              Address offset: 0x48 */
  __vo uint32_t AHB2ENR;     /*!< RCC AHB2 peripheral clocks enable register,                              Address offset: 0x4C */
  __vo uint32_t AHB3ENR;     /*!< RCC AHB3 peripheral clocks enable register,                              Address offset: 0x50 */
  uint32_t      RESERVED3;   /*!< Reserved,                                                                Address offset: 0x54 */
  __vo uint32_t APB1ENR1;    /*!< RCC APB1 peripheral clocks enable register 1,                            Address offset: 0x58 */
  __vo uint32_t APB1ENR2;    /*!< RCC APB1 peripheral clocks enable register 2,                            Address offset: 0x5C */
  __vo uint32_t APB2ENR;     /*!< RCC APB2 peripheral clocks enable register,                              Address offset: 0x60 */
  uint32_t      RESERVED4;   /*!< Reserved,                                                                0x0000UL)Address offset: 0x64 */
  __vo uint32_t AHB1SMENR;   /*!< RCC AHB1 peripheral clocks enable in sleep and stop modes register,      Address offset: 0x68 */
  __vo uint32_t AHB2SMENR;   /*!< RCC AHB2 peripheral clocks enable in sleep and stop modes register,      Address offset: 0x6C */
  __vo uint32_t AHB3SMENR;   /*!< RCC AHB3 peripheral clocks enable in sleep and stop modes register,      Address offset: 0x70 */
  uint32_t      RESERVED5;   /*!< Reserved,                                                                Address offset: 0x74 */
  __vo uint32_t APB1SMENR1;  /*!< RCC APB1 peripheral clocks enable in sleep mode and stop modes register 1, Address offset: 0x78 */
  __vo uint32_t APB1SMENR2;  /*!< RCC APB1 peripheral clocks enable in sleep mode and stop modes register 2, Address offset: 0x7C */
  __vo uint32_t APB2SMENR;   /*!< RCC APB2 peripheral clocks enable in sleep mode and stop modes register, Address offset: 0x80 */
  uint32_t      RESERVED6;   /*!< Reserved,                                                                Address offset: 0x84 */
  __vo uint32_t CCIPR;       /*!< RCC peripherals independent clock configuration register,                Address offset: 0x88 */
  uint32_t      RESERVED7;   /*!< Reserved,                                                                Address offset: 0x8C */
  __vo uint32_t BDCR;        /*!< RCC backup domain control register,                                      Address offset: 0x90 */
  __vo uint32_t CSR;         /*!< RCC clock control & status register,                                     Address offset: 0x94 */
  __vo uint32_t CRRCR;       /*!< RCC clock recovery RC register,                                          Address offset: 0x98 */
  __vo uint32_t CCIPR2;      /*!< RCC peripherals independent clock configuration register 2,              Address offset: 0x9C */
} RCC_RegDef_t;




/*
 * Peripheral register definition structure for EXTI
 */
typedef struct
{
	__vo uint32_t IMR1;
	__vo uint32_t EMR1;
	__vo uint32_t RTSR1;
	__vo uint32_t FTSR1;
	__vo uint32_t SWIER1;
	__vo uint32_t EXTI_PR1;
	__vo uint32_t EXTI_IMR2;
	__vo uint32_t EXTI_EMR2;
	__vo uint32_t EXTI_RTSR2;
	__vo uint32_t EXTI_FTSR2;
	__vo uint32_t SWIER2;
	__vo uint32_t EXTI_PR2;

}EXTI_RegDef_t;


/*
 * Peripheral register definition structure for SYSCFG
 */
typedef struct
{
	__vo uint32_t MEMRMP;
	__vo uint32_t CFGR1;
	__vo uint32_t EXTICR[4];
	__vo uint32_t CSR;
	__vo uint32_t CFGR2;
	__vo uint32_t SWPR;
	__vo uint32_t SKR;
}SYSCFG_RegDef_t;

/*
 * Peripheral register definition structure for GPIO
 */
typedef struct
{
	__vo uint32_t MODER;
	__vo uint32_t OTYPER;
	__vo uint32_t OSPEEDR;
	__vo uint32_t PUPDR;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t LCKR;
	__vo uint32_t AFR[2];
	__vo uint32_t BRR;
}GPIO_RegDef_t;



#define GPIOA 					((GPIO_RegDef_t*)GPIOA_BASE)
#define GPIOB 					((GPIO_RegDef_t*)GPIOB_BASE)
#define GPIOC					((GPIO_RegDef_t*)GPIOC_BASE)
#define GPIOD 					((GPIO_RegDef_t*)GPIOD_BASE)
#define GPIOE 					((GPIO_RegDef_t*)GPIOE_BASE)
#define GPIOH					((GPIO_RegDef_t*)GPIOH_BASE)

#define EXTI					((EXTI_RegDef_t*)EXTI_BASE)

#define SYSCFG				    ((SYSCFG_RegDef_t*)SYSCFG_BASE)
/*
 * Clock Enable Macro for GPIOx peripheral
 */
#define GPIOA_PCLK_EN()			(RCC->AHB2ENR |= (1 << 0))
#define GPIOB_PCLK_EN()			(RCC->AHB2ENR |= (1 << 1))
#define GPIOC_PCLK_EN()			(RCC->AHB2ENR |= (1 << 2))
#define GPIOD_PCLK_EN()			(RCC->AHB2ENR |= (1 << 3))
#define GPIOE_PCLK_EN()			(RCC->AHB2ENR |= (1 << 4))
#define GPIOH_PCLK_EN()			(RCC->AHB2ENR |= (1 << 6))


/*
 * Clock Disable Macro for GPIOx peripheral
 */
#define GPIOA_PCLK_DI()			(RCC->AHB2ENR &= ~(1 << 0))
#define GPIOB_PCLK_DI()			(RCC->AHB2ENR &= ~(1 << 1))
#define GPIOC_PCLK_DI()			(RCC->AHB2ENR &= ~(1 << 2))
#define GPIOD_PCLK_DI()			(RCC->AHB2ENR &= ~(1 << 3))
#define GPIOE_PCLK_DI()			(RCC->AHB2ENR &= ~(1 << 4))
#define GPIOH_PCLK_DI()			(RCC->AHB2ENR &= ~(1 << 6))


/*
 * Clock Enable Macro for SYSCFG peripheral
 */
#define SYSCFG_PCLK_EN()		(RCC->APB2ENR |= (1 << 0))

/*
 * CLock Disable Macro for SYSCFG peripheral
 */
#define SYSCFG_PCLK_DI()		(RCC->APB2ENR |= (0 << 0))

/*
 * Peripheral register definition structure for SPI
 */
typedef struct
{
	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t SR;
	__vo uint32_t DR;
	__vo uint32_t CRCPR;
	__vo uint32_t RXCRCR;
	__vo uint32_t TXCRCR;

}SPI_RegDef_t;


#define RCC                 ((RCC_RegDef_t *) RCC_BASEADDR)
#define SPI1                ((SPI_RegDef_t *) SPI1_BASE)
#define SPI2  				((SPI_RegDef_t *) SPI2_BASE)
#define SPI3                ((SPI_RegDef_t *) SPI3_BASE)


/*
 * Clock Enable Macros for SPIx Peripherals
 */
#define SPI1_PCLK_EN() 		(RCC->APB2ENR) |= (1<<12)
#define SPI2_PCLK_EN() 		(RCC->APB1ENR1) |= (1<<14)
#define SPI3_PCLK_EN() 		(RCC->APB1ENR1) |= (1<<15)




/*
 * Macros to reset the GPIOx peripherals
 */
#define GPIOA_REG_RESET() 				do {(RCC->AHB2RSTR) |= (1 << 0); (RCC->AHB2RSTR) &= ~(1 << 0);}while(0)
#define GPIOB_REG_RESET() 				do {(RCC->AHB2RSTR) |= (1 << 1); (RCC->AHB2RSTR) &= ~(1 << 1);}while(0)
#define GPIOC_REG_RESET() 				do {(RCC->AHB2RSTR) |= (1 << 2); (RCC->AHB2RSTR) &= ~(1 << 2);}while(0)
#define GPIOD_REG_RESET() 				do {(RCC->AHB2RSTR) |= (1 << 3); (RCC->AHB2RSTR) &= ~(1 << 3);}while(0)
#define GPIOE_REG_RESET() 				do {(RCC->AHB2RSTR) |= (1 << 4); (RCC->AHB2RSTR) &= ~(1 << 4);}while(0)
#define GPIOH_REG_RESET() 				do {(RCC->AHB2RSTR) |= (1 << 7); (RCC->AHB2RSTR) &= ~(1 << 7);}while(0)



/*
 * This macro returns from 0 to 4 or 7 for a given GPIO base address(x)
 */
#define GPIO_BASEADDR_TO_CODE(x)      	( (x == GPIOA)?0 :\
										  (x == GPIOB)?1 :\
										  (x == GPIOC)?2 :\
										  (x == GPIOD)?3 :\
										  (x == GPIOE)?4 :\
										  (x == GPIOH)?7 : 0)



/*
 * IRQ(Interrupt Request) Number of STM32 NUCLEO L452RE-P MCU
 */
#define IRQ_NO_EXTIO		6
#define IRQ_NO_EXTI1		7
#define IRQ_NO_EXTI2		8
#define IRQ_NO_EXTI3		9
#define IRQ_NO_EXTI4		10
#define IRQ_NO_EXTI9_5		23
#define IRQ_NO_EXTI15_10	40


//some generic macros
#define ENABLE  		1
#define DISABLE 		0
#define SET 			ENABLE
#define RESET   		DISABLE
#define GPIO_PIN_SET    SET
#define GPIO_PIN_RESET  RESET
#define FLAG_RESET 		RESET
#define FLAG_SET		SET

/*
 * Bit positions definition of SPI_CR1
 */
#define SPI_CR1_CPHA		0
#define SPI_CR1_CPOL 		1
#define SPI_CR1_MSTR		2
#define SPI_CR1_BR			3
#define SPI_CR1_SPE			6
#define SPI_CR1_LSB_FIRST 	7
#define SPI_CR1_SSI			8
#define SPI_CR1_SSM			9
#define SPI_CR1_RX_ONLY		10
#define SPI_CR1_CRCL		11
#define SPI_CR1_CRCN_EXT	12
#define SPI_CR1_CRC_EN		13
#define SPI_CR1_BIDIODE		14
#define SPI_CR1_BIDIMODE	15

/*
 * Bit position definition of SPI_CR2
 */
#define SPI_CR2_RXDMAEN				0
#define SPI_CR2_TXDMAEN				1
#define SPI_CR2_SSOE 				2
#define SPI_CR2_NSSP				3
#define SPI_CR2_FRF					4
#define SPI_CR2_ERRIE				5
#define SPI_CR2_RXNEIE				6
#define SPI_CR2_TXEIE				7
#define SPI_CR2_DS					8
#define SPI_CR2_FRXTH				12
#define SPI_CR2_LDMA_RX				13
#define SPI_CR2_LDMA_TX				14


/*
 * Bit position definition of SPI_SR
 */
#define SPI_SR_RXNE					0
#define SPI_SR_TXE					1
#define SPI_SR_CRCE_RR				4
#define SPI_SR_MODF					5
#define SPI_SR_OVR					6
#define SPI_SR_BSY					7
#define SPI_SR_FRE					8
#define SPI_SR_FRLVL				9
#define SPI_SR_FTLVL				11

#endif /* INC_STM32L452XX_H_ */
