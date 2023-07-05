/**
 *********************************************************************************************************
 *                                              Fluffy Time
 *                                             (ふわふわ時間)
 *
 *                    Copyright 2023-2024 Fluffy Time(ふわふわ時間)
 *
 *                                 SPDX-License-Identifier: APACHE-2.0
 *
 *               This software is subject to an open source license and is distributed by
 *                Fluffy Time(ふわふわ時間). pursuant to the terms of the Apache License,
 *                    Version 2.0 available at www.apache.org/licenses/LICENSE-2.0.
 *
 *********************************************************************************************************
 */

/**
 *********************************************************************************************************
 *                                           SERVICE
 *
 * File    : service.c
 * Version : V1.0.0
 *********************************************************************************************************
 */

#include "service.h"
#include <stdarg.h>
#include <stdio.h>
#include "systick.h"

/**
 ************************************************************************************************************************
 *                                                   Console output
 *
 * Description: Console output interface (__WEAK)
 *
 * Arguments  : str Strough string to be output by the console
 *
 * Returns    : NONE
 *
 * Note(s)    : (1) The log output interface if the log print is required the function must be implemented
 ************************************************************************************************************************
 */
__WEAK void board_console_output(const char *str)
{
    /* empty console output */
}

/**
 ************************************************************************************************************************
 *                                                   __kprintf
 *
 * Description: This function will print a formatted string on system console.
 *
 * Arguments  : fmt is the format parameters.
 *
 *              level great or equal to 2 printing timestamp.
 *
 * Returns    : The number of characters actually written to buffer.
 *
 * Note(s)    : (1) Variable Arguments
 *                  #include <stdarg.h>
 *                  In the functional statement the last parameter is specified as an omission number '...',
 *                  Indicates parameters that accept variable quantities.
 *                  va_list: Type variables declare a parameter list object.
 *                  va_start(): Initialization parameter list object.
 *                  va_arg(va_list, data-type): Get the value of variable parameters one by one.
 *                  va_end(va_list): End the access of the parameter list.
 *                      eg. void functionName(int fixedArg, ...) {
 *                              va_list variableArgs;
 *                              va_start(variableArgs, fixedArg);
 *
 *                              int value1 = va_arg(variableArgs, int);
 *                              double value2 = va_arg(variableArgs, double);
 *                              char* value3 = va_arg(variableArgs, char*);
 *
 *                              va_end(variableArgs);
 *                          }
 *
 *              (2) vsnprintf
 *                  #include <stdio.h>
 *                  int vsnprintf(char *str, size_t size, const char *format, va_list ap);
 *                  Parameter Description:
 *                      str: Point to a buffer to store the formatted string.
 *                      size: The size of the buffer including the position of the last empty character.
 *                      format: Format strings specify the format of the strings to be generated.
 *                      ap: va_list type parameter list contains formal variable parameters.
 *                  Return Value:
 *                      Successful: Return to the number of characters written to the buffer
 *                                  (excluding the final empty character)
 *                                  if the output string is truncated the number of characters you actual need
 *                                  (excluding the final empty character)
 *                      Failure: Return negative
 *              (3) snprintf
 *                  #include <stdio.h>
 *                  int snprintf(char *str, size_t size, const char *format, ...);
 *                  Parameter Description:
 *                      str: Point to a buffer to store the formatted string.
 *                      size: The size of the buffer including the position of the last empty character.
 *                      format: Format strings specify the format of the strings to be generated.
 *                      ...: The parameter of the variable quantity matches the format indicator symbol
 *                           in the format string
 *                  Return Value:
 *                      Successful: Return to generate string length
 *                                  (excluding the final empty character)
 *                      Failure: if the output string is truncated the number of characters you actual need
 *                               (excluding the final empty character)
 *
 ************************************************************************************************************************
 */
static int __kprintf(uint8_t level, const char *fmt, va_list args) {
    size_t length = 0;
    size_t temp_length = 0;
    static char log_buf[CONFIG_CONSOLEBUF_SIZE];

    if (level >= 2) {
        temp_length = snprintf(log_buf, sizeof(log_buf) - 1, "[%d.%03d]",
                               systick_get_millisecond() / 1000, systick_get_millisecond() % 1000);
    }
    length = vsnprintf(log_buf + temp_length, sizeof(log_buf) - temp_length - 1, fmt, args);
    if (length > CONFIG_CONSOLEBUF_SIZE - 1) {
        length = CONFIG_CONSOLEBUF_SIZE - 1;
    }

    /* Back end output */
    board_console_output(log_buf);

    return length;
}

/**
 ************************************************************************************************************************
 *                                                   kprint
 *
 * Description: Printing format string
 *
 * Arguments  : fmt is the format parameters.
 *
 * Returns    : The number of characters actually written to buffer.
 ************************************************************************************************************************
 */
int kprint(const char *fmt, ...) {
    size_t length = 0;
    va_list args;

    va_start(args, fmt);
    length = __kprintf(0, fmt, args);
    va_end(args);

    return length;
}

/**
 ************************************************************************************************************************
 *                                                   kprintf
 *
 * Description: Printing format string, will add time stamp information to the beginning of printing.
 *
 * Arguments  : fmt is the format parameters.
 *
 * Returns    : The number of characters actually written to buffer.
 *
 * Note(s)    : (1) Will add time stamp information at the beginning.
 ************************************************************************************************************************
 */
int kprintf(const char *fmt, ...) {
    size_t length = 0;
    va_list args;

    va_start(args, fmt);
    length = __kprintf(2, fmt, args);
    va_end(args);

    return length;
}
