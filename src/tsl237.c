/*!
 *  \file       tsl237.c
 *
 *  \brief      Interface with TSL237 light-to-frequency converter
 * 
 *  \details    Monitor GPIO PIN 2 for TSL237 signals and measure the
 *              period with a timer
 * 
 *  \author    Joseph Bellahcen <joe@josephbellahcen.com>
 */
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

volatile bool capture_complete;
uint64_t capture_distance;
void tsl237_gpio_callback();

/*!
 * \brief   Initialize the TSL237 interface
 *
 * \details Establishes a timer interrupt which will be triggered by the
 *          output pulse of the TSL237
 */
void tsl237_init() {
    capture_distance = 0;
    capture_complete = false;
    gpio_set_irq_enabled_with_callback(2, GPIO_IRQ_EDGE_RISE, true, tsl237_gpio_callback);
}

/*!
 * \brief       Measure the frequency of the TSL237
 *
 * \details     Enable the GPIO interrupt, wait for it to disable itself,
 *              and then calculate the sensor frequency based on its period
 * 
 * \return      The frequency in Hertz of the TSL237
 */
float tsl237_capture() {
    /*
     * Enable the GPIO interrupt and wait for it to signal that it is done.
     * The callback function will handle disabling the interrupt handler
     * when it is finished capturing
     */
    gpio_set_irq_enabled(2, GPIO_IRQ_EDGE_RISE, true);
    while(!capture_complete);
    capture_complete = false;

    /* The timer updates once every microsecond (1.0e-6 seconds) */
    float frequency = 1.0e6 / (float)capture_distance;
    return frequency;
}

/*!
 * \brief   Handle TSL237 interrupts on GPIO PIN 2
 *
 * \details Fires on the rising edge of the signal to measure to
 *          value of the hardware timer. When two captures have been
 *          taken, updates the fileprivate `capture_distance` variable,
 *          signals that the capture distance has been recorded,
 *          and disables the GPIO interrupt
 */
void tsl237_gpio_callback() {
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