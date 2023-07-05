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
 *                                           SYSTICK IMPLEMENT
 *
 * File    : systick.c
 * Version : V1.0.0
 *********************************************************************************************************
 */
#include "systick.h"

/**
 ------------------------------------------------------------------------------------------------------------------------
 *                                                   Tick Frequency
 ------------------------------------------------------------------------------------------------------------------------
 */
typedef enum
{
    TICK_FREQ_10HZ      = 100U,
    TICK_FREQ_100HZ     = 10U,
    TICK_FREQ_1KHZ      = 1U,
    TICK_FREQ_DEFAULT   = TICK_FREQ_1KHZ,
} tick_freq_e;

/**
 ------------------------------------------------------------------------------------------------------------------------
 *                                                   MAX DELAY COUNT
 ------------------------------------------------------------------------------------------------------------------------
 */
#define MAX_DELAY      0xFFFFFFFF

static __IO uint32_t uwtick;  /* Current system timestamp */
static uint32_t uwtick_priority   = 0U; /* Invalid PRIO */
static tick_freq_e uwtick_freq = TICK_FREQ_DEFAULT;  /* 1KHz */

/**
 ************************************************************************************************************************
 *                                                   SYSTICK CONFIG
 *
 * Description: Configure systick priority and frequency
 *
 * Arguments  : priority systick interrupt priority
 *
 * Returns    : -EERROR Configure systick fail
 *
 *              EOK Configure systick success
 ************************************************************************************************************************
 */
error_t systick_config(uint32_t priority)
{
    /* setup systick timer for 1000Hz interrupts */
    if (SysTick_Config(SystemCoreClock / 1000U))
    {
        return -EERROR;
    }
    /* configure the systick handler priority */
    if (priority < (1UL << __NVIC_PRIO_BITS)) {
        NVIC_SetPriority(SysTick_IRQn, priority);
        uwtick_priority = priority;
    } else {
        return -EERROR;
    }
    return EOK;
}

/**
 ************************************************************************************************************************
 *                                                   GET SYSTEM TIMESTAMP
 *
 * Description: Get the current time stamp of the system
 *
 * Arguments  : NONE
 *
 * Returns    : Current system timestamp
 ************************************************************************************************************************
 */
uint32_t systick_get_millisecond(void) {
    return uwtick;
}

/**
 ************************************************************************************************************************
 *                                                   GET SYSTICK INTERRUPT PRIORITY
 *
 * Description: Get systick interrupt priority.
 *
 * Arguments  : NONE
 *
 * Returns    : Systick interrupt priority.
 ************************************************************************************************************************
 */
uint32_t systick_get_priority(void) {
    return uwtick_priority;
}

/**
 ************************************************************************************************************************
 *                                                   MILLISECOND DELAY
 *
 * Description: Millisecond delay
 *
 * Arguments  : delay millilitrimum
 *
 * Returns    : NONE
 *
 * Note(s)    : The Maximum Delayed Milliseconds Are 0xFFFFFFFF
 ************************************************************************************************************************
 */
void delay_ms(uint32_t delay) {
    uint32_t tickstart = systick_get_millisecond();
    uint32_t wait = delay;

    /* Add a freq to guarantee minimum wait */
    if (wait < MAX_DELAY)
    {
        wait += (uint32_t)(uwtick_freq);
    }

    while ((systick_get_millisecond() - tickstart) < wait)
    {
    }
}

/**
 ************************************************************************************************************************
 *                                                   SYSTICK EXCEPTION HANDLE
 *
 * Description: This function handles SysTick exception
 *
 * Arguments  : NONE
 *
 * Returns    : NONE
 ************************************************************************************************************************
 */
void SysTick_Handler(void) {
    uwtick += uwtick_freq;
}
