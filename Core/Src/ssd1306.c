#include "ssd1306.h"
#include "i2c.h"

#define SSD1306_ADDR 0x3C

void ssd1306_write_cmd(uint8_t cmd)
{
    uint8_t buf[2] = {0x00, cmd};
    i2c_write_buffer(0x3C, buf, 2);
}

void ssd1306_write_data(uint8_t *data, uint16_t size)
{
    uint8_t buf[size + 1];   // temporary for now
    buf[0] = 0x40;

    for (uint16_t i = 0; i < size; i++)
        buf[i + 1] = data[i];

    i2c_write_buffer(0x3C, buf, size + 1);
}

void ssd1306_update(uint8_t *framebuffer)
{
    // sets column address range
    ssd1306_write_cmd(0x21);
    ssd1306_write_cmd(0);      // start column
    ssd1306_write_cmd(127);    // end column

    // sets page address range
    ssd1306_write_cmd(0x22);
    ssd1306_write_cmd(0);      // start page
    ssd1306_write_cmd(7);      // end page

    // Send framebuffer
    ssd1306_write_data(framebuffer, 1024);
}

void ssd1306_init(void)
{
    ssd1306_write_cmd(0xAE); // display off

    ssd1306_write_cmd(0x20); // addressing mode
    ssd1306_write_cmd(0x00); // horizontal

    ssd1306_write_cmd(0xA8); // multiplex ratio
    ssd1306_write_cmd(0x3F);

    ssd1306_write_cmd(0xD3); // display offset
    ssd1306_write_cmd(0x00);

    ssd1306_write_cmd(0x40);

    ssd1306_write_cmd(0xA1);
    ssd1306_write_cmd(0xC8);

    ssd1306_write_cmd(0xDA);
    ssd1306_write_cmd(0x12);

    ssd1306_write_cmd(0x81);
    ssd1306_write_cmd(0x7F);

    ssd1306_write_cmd(0xA4);
    ssd1306_write_cmd(0xA6);

    ssd1306_write_cmd(0xD5);
    ssd1306_write_cmd(0x80);

    ssd1306_write_cmd(0x8D);
    ssd1306_write_cmd(0x14);

    ssd1306_write_cmd(0xAF); // display on
}
