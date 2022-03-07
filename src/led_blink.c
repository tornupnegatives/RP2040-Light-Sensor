/*!
 *  \file       led_blink.c
 *
 *  \brief      Toggle the LED
 * 
 *  \details    The functionality provided by this file should by all means
 *              reside directly in main as unencapsulated statements.
 *              However, in order to avoid blocking outside of the while loop,
 *              they instead appear here
 * 
 *  \author    Joseph Bellahcen <joe@josephbellahcen.com>
 */

#include "pico/stdlib.h"
#include "led_blink.h"

#define LED_PIN PICO_DEFAULT_LED_PIN

/*!
 * \brief   Set the LED pin as a GPIO output
 */
void led_init() {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

/*!
 * \brief   Toggle the LED on
 */
void led_on() {
    gpio_put(LED_PIN, 1);
}

/*!
 * \brief   Toggle the LED off
 */
void led_off() {
    gpio_put(LED_PIN, 0);
}