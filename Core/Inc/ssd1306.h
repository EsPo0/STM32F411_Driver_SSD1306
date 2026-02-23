#pragma once
#include <stdint.h>

void ssd1306_init(void);
void ssd1306_write_cmd(uint8_t cmd);
void ssd1306_write_data(uint8_t *data, uint16_t size);
void ssd1306_update(uint8_t *framebuffer);

#ifndef SSD1306_DRIVER_SSD1306_H
#define SSD1306_DRIVER_SSD1306_H

#endif //SSD1306_DRIVER_SSD1306_H