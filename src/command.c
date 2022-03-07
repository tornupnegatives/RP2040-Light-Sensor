/*!
 *  \file      command.c
 *
 *  \brief     Basis of the command-line interface
 * 
 *  \details   Provides functions for parsing and executing commands over USB serial/UART
 * 
 *  \author    Joseph Bellahcen <joe@josephbellahcen.com>
 */

#include <stdio.h>
#include "pico/stdlib.h"

/*!
 * \brief       Scan the console for user input without blocking
 *
 * \param[out]  buff: Buffer into which to store command
 * 
 * \param[in]   buff_size: Size of the buffer
 */
int command_scan(uint8_t* buff, uint8_t buff_size) {
    static uint8_t i = 0;
    static enum status{READ, DONE} status = READ;
    
    int8_t ch = getchar_timeout_us(0);

    switch(ch) {
        /* No data */
        case 0:
            break;
        
        /* Serial timeout */
        case PICO_ERROR_TIMEOUT:
            break;

        /* Newline */
        case '\n':
            status = DONE;
            break;

        /* Carriage return */
        case '\r':
            status = DONE;
            break;

        /* Backspace */
        case 0x7f:
            printf("\b \b");
            i--;
            break;

        default:
            putchar(ch);
            buff[i++] = ch;
    }

    /* Commands past the max_size are truncated */
    if (i >= buff_size - 2) {
        status = DONE;
    }

    /* When a command is entered or the buffer is full, null-terminate */
    if (status == DONE) {
        buff[i] = '\0';
        
        i = 0;
        status = READ;

        printf("\n\r");
        return 1;
    }

    /* Otherwise, signal no command so the MCU can do other things */
    return 0;
 }
 