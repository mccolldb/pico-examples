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
#ifndef PICO_DEFAULT_LED_PIN
#warning blink example requires a board with a regular LED
#else
    const uint LED_PIN = 18; /* PICO_DEFAULT_LED_PIN; */
    const uint LED_2 = LED_PIN + 1;
    const uint LED_3 = LED_PIN + 2;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_init(LED_2);
    gpio_set_dir(LED_2, GPIO_OUT);
    gpio_init(LED_3);
    gpio_set_dir(LED_3, GPIO_OUT);
    stdio_init_all();
    uint count = 0;
    while (true)
    {
        uint pin = LED_PIN + (++count) % 3;
        gpio_put(pin, 1);
        sleep_ms(250);
        gpio_put(pin, 0);
        sleep_ms(250);
        if (pin == LED_PIN)
            printf("Hello, world! %d pin=%d\n", count, pin);
    }
#endif
}
