
#include "hardware/spi.h"
#include "pico/binary_info.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include <string.h>

#define SPI_PORT spi1
#define SPI_CLK_PIN 10
#define SPI_MOSI_PIN 11
#define SPI_MISO_PIN 12
#define MCP3008_CS_PIN 13

int main()
{
    stdio_init_all();
    printf("Hello, mcp3008! Reading raw data from ADC via SPI...\n");

    // This example will use SPI0 at 0.5MHz.
    spi_init(SPI_PORT, 500 * 1000);
    spi_set_format(SPI_PORT, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);
    gpio_set_function(SPI_CLK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(SPI_MOSI_PIN, GPIO_FUNC_SPI);
    gpio_set_function(SPI_MISO_PIN, GPIO_FUNC_SPI);
    // gpio_set_function(SPI_CS_PIN, GPIO_FUNC_SPI); // run CS on 8 bit xfers
    //    Make the SPI pins available to picotool
    bi_decl(bi_3pins_with_func(SPI_MISO_PIN, SPI_MOSI_PIN, SPI_CLK_PIN, GPIO_FUNC_SPI));

    uint8_t outbuf[] = {0x01, 0x00, 0x00}; // start, sgl+chan000 + 4bits, 8bits
    uint8_t inbuf[] = {0x00, 0x00, 0x00};  // 8bits,5bits+0+2bits, 8 bits
    // manually toggle CS -- accross 24 bit xfers
    gpio_init(MCP3008_CS_PIN);
    gpio_set_dir(MCP3008_CS_PIN, GPIO_OUT);
    gpio_put(MCP3008_CS_PIN, 1); // idles high

    printf("out buf = %02X %02X %02X\n", outbuf[0], outbuf[1], outbuf[2]);
    while (1)
    {
        gpio_put(MCP3008_CS_PIN, 0);                         // select
        spi_write_read_blocking(SPI_PORT, outbuf, inbuf, 3); // send/receive
        gpio_put(MCP3008_CS_PIN, 1);                         // deselect
        int value = inbuf[1] << 8 | inbuf[2];                // combine 2 bytes into 16 bit value
        printf("in buf = %02X %02X %02X value = %d\n", inbuf[0], inbuf[1], inbuf[2], value);
        sleep_ms(500);
    }
}
