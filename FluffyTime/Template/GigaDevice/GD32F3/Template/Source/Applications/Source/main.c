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
 *                                           (Title)
 *
 * File    : main.c
 * Version : V1.0.0
 *********************************************************************************************************
 */
#include "main.h"

#define DBG_TAG             "main"
#define DBG_LVL             DBG_LOG
#define DBG_ENABLE
#define DBG_COLOR
#include "debug.h"


int main(void) {
    // TODO：return value judgment
    systick_config(0);
    board_console_init();

    while (1)
    {
        delay_ms(1000);
        LOG_D("runing...debug");
        LOG_I("runing...info");
        LOG_W("runing...warning");
        LOG_E("runing...error");
        LOG_RAW("runing...raw\r\n");
    }

}
