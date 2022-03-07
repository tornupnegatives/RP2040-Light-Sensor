/*!
 *  \file       led_blink.c
 *  \brief      Toggle the LED
 * 
 *  \details    The functionality provided by this file should by all means
 *              reside directly in main as unencapsulated statements.
 *              However, in order to avoid blocking outside of the while loop,
 *              they instead appear here
 * 
 *  \author    Joseph Bellahcen <joe@josephbellahcen.com>
 */
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

/* Private variables */
volatile bool capture_complete;
uint64_t capture_distance;

/* Private prototypes */
void tsl237_gpio_callback(uint gpio, uint32_t events);

void tsl237_init() {
    capture_distance = 0;
    capture_complete = false;
    gpio_set_irq_enabled_with_callback(2, GPIO_IRQ_EDGE_RISE, true, tsl237_gpio_callback);
}

void tsl237_capture(void) {
  uint64_t capture_i, capture_f;

  gpio_set_irq_enabled(2, GPIO_IRQ_EDGE_RISE, true);
  while(!capture_complete);
  capture_complete = false;

  double frequency = 1.0e6 / (float)capture_distance;
  printf("%f Hz\n", frequency);
}

void tsl237_gpio_callback(uint gpio, uint32_t events) {
  static bool first_capture = true;
  static bool capture_done = false;
  static uint64_t capture_0, capture_1;

  if (first_capture) {
    capture_0 = time_us_64();
    first_capture = false;
    capture_complete = false;

  } else if (!capture_done) {
    capture_1 = time_us_64();
    capture_done = true;

  } else {
    capture_distance = capture_1 - capture_0;
    first_capture = true;
    capture_done = false;
    capture_complete = true;
    gpio_set_irq_enabled(2, GPIO_IRQ_EDGE_RISE, false);
  }
}