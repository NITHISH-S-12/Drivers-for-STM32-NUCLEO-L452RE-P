/*
 * STM32L452RE SPI2 Master <----> Arduino UNO SPI Slave
 *
 * PB13 = SCK
 * PB14 = MISO
 * PB15 = MOSI
 * PB12 = NSS
 *
 * PC13 = Nucleo User Button (active HIGH)
 *
 * NSS remains LOW for all five commands in one session.
 */

#include <stdint.h>
#include <string.h>

#include "stm32l452xx.h"
#include "stm32l452xx_gpio_driver.h"
#include "stm32l452xx_spi_driver.h"


// ==========================================
// COMMAND DEFINITIONS
// ==========================================

#define COMMAND_LED_CTRL       0x50
#define COMMAND_SENSOR_READ    0x51
#define COMMAND_LED_READ       0x52
#define COMMAND_PRINT          0x53
#define COMMAND_ID_READ        0x54

#define ACK                    0xF5

#define LED_ON                 1

#define LED_PIN                9

#define ANALOG_PIN0            0


// ==========================================
// DELAY FUNCTION
// ==========================================

static void delay(void)
{
    for (volatile uint32_t i = 0; i < 250000U; i++)
    {
    }
}


// ==========================================
// BUTTON CHECK
// ==========================================

static uint8_t buttonIsPressed(void)
{
    return GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13);
}


// ==========================================
// WAIT FOR BUTTON PRESS AND RELEASE
// ==========================================

static void waitForButtonPressRelease(void)
{
    // Wait until button is pressed.
    while (buttonIsPressed() == 0U)
    {
    }

    // Short debounce delay.
    for (volatile uint32_t i = 0; i < 10000U; i++)
    {
    }

    // Confirm button is still pressed.
    if (buttonIsPressed() == 0U)
    {
        waitForButtonPressRelease();
        return;
    }

    // Wait until button is released.
    while (buttonIsPressed() != 0U)
    {
    }

    // Short release debounce.
    for (volatile uint32_t i = 0; i < 10000U; i++)
    {
    }
}

// ==========================================
// SPI GPIO INITIALIZATION
// ==========================================

static void SPI2_GPIOInits(void)
{
    GPIO_Handle_t SPIPins;

    SPIPins.pGPIOx = GPIOB;

    SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;

    SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;

    SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;

    SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;


    // PB13 = SPI2 SCK
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;

    GPIO_Init(&SPIPins);


    // PB15 = SPI2 MOSI
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;

    GPIO_Init(&SPIPins);


    // PB14 = SPI2 MISO
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;

    GPIO_Init(&SPIPins);


    // PB12 = SPI2 NSS
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;

    GPIO_Init(&SPIPins);
}


// ==========================================
// SPI2 PERIPHERAL INITIALIZATION
// ==========================================

static void SPI2_Inits(void)
{
    SPI_Handle_t SPI2handle;

    SPI2handle.pSPIx = SPI2;


    SPI2handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;

    SPI2handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;


    // SPI Clock = PCLK1 / 32
    SPI2handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV32;


    SPI2handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;

    SPI2handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;

    SPI2handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;

    // Hardware NSS.
    SPI2handle.SPIConfig.SPI_SSM = SPI_SSM_DI;


    SPI_Init(&SPI2handle);
}


// ==========================================
// BUTTON GPIO INITIALIZATION
// ==========================================

static void GPIO_ButtonInit(void)
{
    GPIO_Handle_t GpioBtn;

    GpioBtn.pGPIOx = GPIOC;

    GpioBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;

    GpioBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;

    GpioBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;

    GpioBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;


    GPIO_Init(&GpioBtn);
}


// ==========================================
// VERIFY ACK
// ==========================================

static uint8_t SPI_VerifyResponse(uint8_t ackbyte)
{
    return (ackbyte == ACK) ? 1U : 0U;
}


// ==========================================
// SPI TRANSFER FUNCTION
// ==========================================

/*
 * SPI is full duplex.
 *
 * Whenever STM32 sends one byte,
 * it also receives one byte.
 *
 * This function sends one byte and
 * reads the simultaneously received byte.
 */

static uint8_t SPI2_TransferByte(uint8_t data)
{
    uint8_t received = 0U;

    SPI_SendData(SPI2, &data, 1U);

    SPI_ReceiveData(SPI2, &received, 1U);

    return received;
}


// ==========================================
// SEND COMMAND AND RECEIVE ACK
// ==========================================

static uint8_t SPI2_SendCommandAndGetAck(uint8_t command)
{
    // Send command to Arduino.
    (void)SPI2_TransferByte(command);


    // Allow Arduino to process the command.
    delay();


    // Send dummy byte to generate clock.
    // Arduino returns ACK or NACK.
    return SPI2_TransferByte(0xFF);
}


// ==========================================
// MAIN FUNCTION
// ==========================================

int main(void)
{
    uint8_t ackbyte;

    uint8_t analog_read;

    uint8_t led_status;

    uint8_t id[11];


    static const uint8_t message[] =
        "Hello ! How are you ??";

    const uint8_t message_len =
        (uint8_t)(sizeof(message) - 1U);


    // Initialize button GPIO.
    GPIO_ButtonInit();


    // Initialize SPI GPIO pins.
    SPI2_GPIOInits();


    // Initialize SPI2 peripheral.
    SPI2_Inits();


    // Enable hardware NSS output.
    SPI_SSOEConfig(SPI2, ENABLE);


    while (1)
    {

        // ==================================
        // START SPI SESSION
        // ==================================

        waitForButtonPressRelease();

        // Enable SPI.
        // NSS becomes LOW.
        SPI_PeripheralControl(SPI2, ENABLE);


        // ==================================
        // COMMAND 1: LED CONTROL
        // ==================================

        ackbyte =
            SPI2_SendCommandAndGetAck(COMMAND_LED_CTRL);


        if (SPI_VerifyResponse(ackbyte))
        {
            // Send LED pin number.
            (void)SPI2_TransferByte(LED_PIN);


            // Send LED ON command.
            (void)SPI2_TransferByte(LED_ON);
        }


        // ==================================
        // COMMAND 2: SENSOR READ
        // ==================================

        waitForButtonPressRelease();


        ackbyte =
            SPI2_SendCommandAndGetAck(COMMAND_SENSOR_READ);


        if (SPI_VerifyResponse(ackbyte))
        {
            // Select Arduino A0.
            (void)SPI2_TransferByte(ANALOG_PIN0);


            // Allow Arduino to perform analogRead().
            delay();


            // Read sensor value.
            analog_read = SPI2_TransferByte(0xFF);

            (void)analog_read;
        }


        // ==================================
        // COMMAND 3: LED READ
        // ==================================

        waitForButtonPressRelease();


        ackbyte =
            SPI2_SendCommandAndGetAck(COMMAND_LED_READ);


        if (SPI_VerifyResponse(ackbyte))
        {
            // Send LED pin number.
            (void)SPI2_TransferByte(LED_PIN);


            // Allow Arduino to read LED state.
            delay();


            // Receive LED status.
            led_status = SPI2_TransferByte(0xFF);

            (void)led_status;
        }


        // ==================================
        // COMMAND 4: PRINT MESSAGE
        // ==================================

        waitForButtonPressRelease();


        ackbyte =
            SPI2_SendCommandAndGetAck(COMMAND_PRINT);


        if (SPI_VerifyResponse(ackbyte))
        {
            // Send message length.
            (void)SPI2_TransferByte(message_len);


            // Send message characters.
            for (uint8_t i = 0U; i < message_len; i++)
            {
                (void)SPI2_TransferByte(message[i]);
            }
        }


        // ==================================
        // COMMAND 5: BOARD ID READ
        // ==================================

        waitForButtonPressRelease();


        ackbyte =
            SPI2_SendCommandAndGetAck(COMMAND_ID_READ);


        if (SPI_VerifyResponse(ackbyte))
        {
            // Allow Arduino to prepare first ID character.
            delay();


            // Receive 10 characters.
            for (uint8_t i = 0U; i < 10U; i++)
            {
                id[i] = SPI2_TransferByte(0xFF);

                // Allow Arduino to prepare next character.
                delay();
            }


            // Add string terminator.
            id[10] = '\0';
        }


        // ==================================
        // END SPI SESSION
        // ==================================

        // Wait until SPI transmission is complete.
        while (SPI_GetFlagStatus(SPI2, SPI_BUSY_FLAG) == FLAG_SET)
        {
        }


        // Disable SPI.
        // NSS becomes HIGH.
        SPI_PeripheralControl(SPI2, DISABLE);
    }

}
