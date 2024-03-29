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
 * File    : service.h
 * Version : V1.0.0
 *********************************************************************************************************
 * Note(s) : (1)
 *********************************************************************************************************
 */
#ifndef __SERVICE_H__
#define __SERVICE_H__

/**
 *********************************************************************************************************
 *                                                 INCLUDE HEADER FILES
 *********************************************************************************************************
 */
#include "public.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 ************************************************************************************************************************
 ************************************************************************************************************************
 *                                        F U N C T I O N   P R O T O T Y P E S
 ************************************************************************************************************************
 ************************************************************************************************************************
 */
void board_console_output(const char *str); /* Strough output interface definition */
int kprint(const char *fmt, ...);
int kprintf(const char *fmt, ...); /* Will print the system timestamp */

#ifdef __cplusplus
}
#endif

#endif /* __SERVICE_H__ */
