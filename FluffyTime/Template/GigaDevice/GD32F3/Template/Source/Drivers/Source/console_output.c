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
 *                                           CONSOLE OUTPUT IMPLEMENT
 *
 * File    : console_output.c
 * Version : V1.0.0
 *********************************************************************************************************
 */
#include "console_output.h"

/**
 ************************************************************************************************************************
 *                                                   CONSOLE INITIALIZATION
 *
 * Description: Initialize console output serial port
 *
 * Arguments  : NONE
 *
 * Returns    : NONE
 ************************************************************************************************************************
 */
void board_console_init(void)
{
    /* enable GPIO clock */
    rcu_periph_clock_enable(RCU_GPIOA);

    /* enable USART clock */
    rcu_periph_clock_enable(RCU_USART0);

    /* connect port to USARTx_Tx */
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);

    /* connect port to USARTx_Rx */
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_10);

    /* USART configure */
    usart_deinit(USART0);
    usart_baudrate_set(USART0, 115200U);
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
    usart_enable(USART0);
}

/**
 ************************************************************************************************************************
 *                                                   CONSOLE OUTPUT IMPLEMENTED
 *
 * Description: Realization of the back end of the console output
 *
 * Arguments  : str Strough string to be output by the console
 *
 * Returns    : NONE
 ************************************************************************************************************************
 */
void board_console_output(const char *str) {
    while(*str != 0) {
        usart_data_transmit(USART0, *str++);
        while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));
    }
}
