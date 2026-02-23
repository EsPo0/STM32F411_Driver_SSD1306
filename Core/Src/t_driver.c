#include "t_driver.h"
#include <sys/types.h>

uint8_t TD_FRAMEBUFFER[TD_FB_SIZE] = {0};

void td_set_pixel(int x, int y, bool state) {

    if (x < 0 || x >= TD_FB_WIDTH) return;
    if (y < 0 || y >= TD_FB_HEIGHT) return;

    int pos = x + (y/8) * TD_FB_WIDTH;
    uint8_t bit = 1 << (y & 7);

    if (state) {
        TD_FRAMEBUFFER[pos] |= bit;
    }
    else {
        TD_FRAMEBUFFER[pos] &= ~bit;
    }
}

bool td_get_pixel(int x, int y) {

    if (x < 0 || x >= TD_FB_WIDTH) return false;
    if (y < 0 || y >= TD_FB_HEIGHT) return false;

    int pos = x + (y/8) * TD_FB_WIDTH;
    uint8_t bit = 1 << (y & 7);

    return (TD_FRAMEBUFFER[pos] & bit) != 0;

}

void td_draw_rectangle(int x, int y, int width, int height) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            td_set_pixel(x + i, y + j, true);
        }
    }
}
void td_draw_bitmap(int x, int y, int width, int height, const uint8_t *bitmap) {

    uint8_t chkMsk = 0;
    int size = width * height >> 3;

    int orginalX = x;
    int orginalY = y;

    for (u_int32_t i = 0; i < size; i++) {
        for (int j = 0; j < 8; j++) {
            chkMsk = 0x80 >> j;

            td_set_pixel(x, y, bitmap[i] & chkMsk);
            x++;

            if ((x - orginalX) == width) {
                y++;
                x = orginalX;
            }

            if ((y - orginalY) == height) {
                return;
            }
        }
    }

}