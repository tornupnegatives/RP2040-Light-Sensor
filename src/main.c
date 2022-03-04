#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/rtc.h"

#include "led_alarm.h"
#include "led_blink.h"
#include "command.h"

#define INPUT_BUFFER_SIZE 64

int main() {
    /* HAL initializers */
    stdio_usb_init();
    rtc_init();

    /* User initializers */
    alarm_init();
    led_init();

    /* User variables */
    uint8_t cmd_buffer[INPUT_BUFFER_SIZE];

    while(!stdio_usb_connected());
    printf("Connected established\n");

    while(true) {

        if (alarm_fired()) {
            led_on();
            sleep_ms(100);
            led_off();
        }

        if (command_scan(cmd_buffer, INPUT_BUFFER_SIZE)) {
            printf("%s\n", cmd_buffer);
            printf("> ");
        }
    }

    return 0;
}