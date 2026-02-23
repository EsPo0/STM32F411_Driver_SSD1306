#pragma once
#include <stdint.h>
#include <stdbool.h>

void i2c_init(void);
bool i2c_write_byte(uint8_t addr, uint8_t data);

#ifndef SSD1306_DRIVER_I2C_H
#define SSD1306_DRIVER_I2C_H

#endif //SSD1306_DRIVER_I2C_H