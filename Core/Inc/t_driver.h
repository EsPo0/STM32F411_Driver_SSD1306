#ifndef SSD1306_DRIVER_T_DRIVER_H
#define SSD1306_DRIVER_T_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

#define TD_FB_WIDTH 128
#define TD_FB_HEIGHT 64

#define TD_FB_SIZE (TD_FB_WIDTH * TD_FB_HEIGHT) / 8

extern uint8_t TD_FRAMEBUFFER[TD_FB_SIZE];

void td_draw_bitmap(int x, int y, int width, int height, const uint8_t * bitmap);
void td_draw_bitmap_alt(int x, int y, int width, int height, const uint8_t * bitmap);
void td_set_pixel(int x, int y, bool state);
bool td_get_pixel(int x, int y);
void td_draw_rectangle(int x, int y, int width, int height);
#endif //SSD1306_DRIVER_T_DRIVER_H