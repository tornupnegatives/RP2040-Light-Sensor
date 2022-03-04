/*!
 *  \file      led_alarm.c
 *  \brief     Query the LED alarm
 *  \details   The LED alarm triggers 30 seconds past the top of each minute
 *  \author    Joseph Bellahcen <joe@josephbellahcen.com>
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/rtc.h"
#include "pico/util/datetime.h"

/* Private variables */
volatile bool _alarm_fired;

/* Private prototypes */
void led_alarm_callback(void);

/* Public interface */

/*!
 * \brief       Set the current date and time and set the LED alarm
 *
 * \details     The current time defaults to 1/13/2021 11:20:00, and the alarm
 *              will fire 30 seconds past the top of each
 *              each minute
 */
void led_alarm_init() {
    /* Set current time to Wednesday 13th January 2021 11:20:00 */
    datetime_t t = {
        .year  = 2020,
        .month = 01,
        .day   = 13,
        .dotw  = 3, // 0 is Sunday, so 3 is Wednesday
        .hour  = 11,
        .min   = 20,
        .sec   = 00
    };

    rtc_set_datetime(&t);

    /* Set alarm to trigger 30 sec past the minute */
    datetime_t alarm = {
        .year  = -1,
        .month = -1,
        .day   = -1,
        .dotw  = -1,
        .hour  = -1,
        .min   = -1,
        .sec   = 30
    };

    rtc_set_alarm(&alarm, &led_alarm_callback);
    _alarm_fired = false;
}

/*!
 * \brief   Did the LED alarm just fire?
 */
bool led_alarm_fired() {
    if (_alarm_fired) {
        _alarm_fired = false;
        return true;
    }

    return false;
}

/* Private interface */

/*!
 * \brief   On alarm interrupt, indicate that it has fired
 */
void led_alarm_callback(void) {
    _alarm_fired = true;
}