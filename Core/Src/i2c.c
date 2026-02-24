#include "stm32f411xe.h"
#include "i2c.h"

void i2c_init(void)
{
    // enable clocks
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

    // configure PB6 (SCL) and PB7 (SDA)

    // alternate function mode
    GPIOB->MODER &= ~(3 << (6 * 2));
    GPIOB->MODER |=  (2 << (6 * 2));

    GPIOB->MODER &= ~(3 << (7 * 2));
    GPIOB->MODER |=  (2 << (7 * 2));

    // open-drain
    GPIOB->OTYPER |= (1 << 6) | (1 << 7);

    // pull up
    GPIOB->PUPDR &= ~(3 << (6 * 2));
    GPIOB->PUPDR |=  (1 << (6 * 2));

    GPIOB->PUPDR &= ~(3 << (7 * 2));
    GPIOB->PUPDR |=  (1 << (7 * 2));

    // AF4 (I2C1)
    GPIOB->AFR[0] &= ~((0xF << (6 * 4)) | (0xF << (7 * 4)));
    GPIOB->AFR[0] |=  ((4 << (6 * 4)) | (4 << (7 * 4)));

    // reset I2C
    I2C1->CR1 |= I2C_CR1_SWRST;
    I2C1->CR1 &= ~I2C_CR1_SWRST;

    // configure peripheral clock frequency (APB1 = 42 MHz typical)
    I2C1->CR2 = 42;  // must match APB1 clock in MHz!!!

    // configure clock control register for 100kHz
    I2C1->CCR = 210; // 42MHz / (2*100kHz)

    // configure rise time
    I2C1->TRISE = 43; // 42MHz + 1

    // enable peripheral
    I2C1->CR1 |= I2C_CR1_PE;
}

bool i2c_write_byte(uint8_t addr, uint8_t data)
{
    // wait until not busy
    while (I2C1->SR2 & I2C_SR2_BUSY);

    // generate START
    I2C1->CR1 |= I2C_CR1_START;

    // wait for SB (start bit set)
    while (!(I2C1->SR1 & I2C_SR1_SB));

    // send address
    I2C1->DR = addr << 1;

    // wait for ADDR flag
    while (!(I2C1->SR1 & I2C_SR1_ADDR));

    // clear ADDR by reading SR1 and SR2
    volatile uint32_t temp;
    temp = I2C1->SR1;
    temp = I2C1->SR2;

    // wait until TXE
    while (!(I2C1->SR1 & I2C_SR1_TXE));

    // send data
    I2C1->DR = data;

    // wait until BTF (byte transfer finished)
    while (!(I2C1->SR1 & I2C_SR1_BTF));

    // generate STOP
    I2C1->CR1 |= I2C_CR1_STOP;

    return true;
}

bool i2c_write_buffer(uint8_t addr, uint8_t *data, uint16_t length)
{
    while (I2C1->SR2 & I2C_SR2_BUSY);

    // start
    I2C1->CR1 |= I2C_CR1_START;

    while (!(I2C1->SR1 & I2C_SR1_SB));

    // send address
    I2C1->DR = addr << 1;

    while (!(I2C1->SR1 & I2C_SR1_ADDR));

    volatile uint32_t temp;
    temp = I2C1->SR1;
    temp = I2C1->SR2;

    for (uint16_t i = 0; i < length; i++)
    {
        while (!(I2C1->SR1 & I2C_SR1_TXE));
        I2C1->DR = data[i];
    }

    while (!(I2C1->SR1 & I2C_SR1_BTF));

    I2C1->CR1 |= I2C_CR1_STOP;

    return true;
}

