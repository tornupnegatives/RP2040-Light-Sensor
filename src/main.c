#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/rtc.h"

#include "led_alarm.h"
#include "led_blink.h"
#include "command.h"
#include "tsl237.h"

#define INPUT_BUFFER_SIZE 64

int main() {
    /* HAL initializers */
    stdio_usb_init();
    rtc_init();

    /* User initializers */
    led_alarm_init();
    led_init();
    tsl237_init();

    /* User variables */
    uint8_t cmd_buffer[INPUT_BUFFER_SIZE];

    while(true) {
        if (led_alarm_fired()) {
            led_on();
            sleep_ms(100);
            led_off();
        }

        if (command_scan(cmd_buffer, INPUT_BUFFER_SIZE)) {
            printf("%s\n", cmd_buffer);
            if (*cmd_buffer == 'c')
                tsl237_capture();
            printf("> ");
        }
    }

    return 0;
}