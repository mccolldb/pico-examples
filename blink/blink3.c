/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *  updated for 3 external leds
 */

#include "pico/stdlib.h"
#include <stdio.h>

int main()
{
    const uint LED_1 = 18; 
    const uint LED_2 = LED_1 + 1;
    const uint LED_3 = LED_1 + 2;
    gpio_init(LED_1);
    gpio_set_dir(LED_1, GPIO_OUT);
    gpio_init(LED_2);
    gpio_set_dir(LED_2, GPIO_OUT);
    gpio_init(LED_3);
    gpio_set_dir(LED_3, GPIO_OUT);
    stdio_init_all();
    uint count = 0;
    while (true)
    {
        uint pin = LED_1 + (++count) % 3;
        gpio_put(pin, 1);
        sleep_ms(250);
        gpio_put(pin, 0);
        sleep_ms(250);
        printf("Hello, world! %d pin=%d\n", count, pin);
    }
}
