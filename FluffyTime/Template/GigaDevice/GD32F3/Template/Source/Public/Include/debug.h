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
 * File    : debug.h
 * Version : V1.0.0
 *********************************************************************************************************
 * Note(s) : (1) #,##,__VA_ARGS__,##__VA_ARGS__
 *              (a) '#'符号（字符串化操作符）：'#'符号是一种预处理运算符，用于将宏参数转换为字符串
 *              (b) '##'符号（标记粘合操作符）：'##' 符号也是一种预处理运算符，用于在宏定义中连接两个标记
 *                  （tokens）。当在宏定义中使用 ## 符号时，它会将前一个标记与后一个标记合并成一个标记
 *                  eg. #define CONCAT(x, y) x##y  -> CONCAT(10,20) = 1020
 *              (c) __VA_ARGS__（可变参数宏）：__VA_ARGS__ 是一个特殊的宏参数，在宏定义中用于表示可变数量
 *                  的参数。它允许宏接受可变数量的参数，并在宏的展开部分中使用这些参数。
 *                  eg. #define PRINT_ARGS(...) printf(__VA_ARGS__)
 *                      PRINT_ARGS("Hello %s!\n", "world"); -> printf("Hello %s!\n", "world");
 *              (d) ##__VA_ARGS__（粘合操作符和可变参数宏的组合）：有时候我们想要将 ## 符号与 __VA_ARGS__
 *                  一起使用，以处理可变数量的参数。这样可以确保当可变参数为空时，预处理器不会引发错误。
 *                  eg. #define DEBUG_PRINT(fmt, ...) printf("DEBUG: " fmt, ##__VA_ARGS__)
 *                      DEBUG_PRINT("Value: %d\n", 10); -> printf("DEBUG: Value: %d\n", 10);
 *                      DEBUG_PRINT("Hello\n"); -> printf("DEBUG: Hello\n");
 *
 *            (2) 终端中打印不同颜色的文本,通常通过使用特殊的转义序列来实现
 *                  ANSI转义序列来控制文本的颜色。ANSI转义序列以\033[开头，后面跟着一些数字和字符，用于指定
 *                  不同的样式和颜色
 *                ->重置所有样式：\033[0m
 *                ->设置文本样式: \033[<code>m
 *                      0： 重置所有样式
 *                      1： 粗体（加粗）
 *                      2： 正常（常规字体）
 *                      3： 斜体
 *                      4： 下划线
 *                      5： 闪烁（某些终端可能不支持）
 *                      7： 反显（前景色与背景色交换）
 *                      8： 隐藏（隐藏文本）
 *                      --字体颜色--
 *                      30: BLACK
 *                      31: RED
 *                      32: GREEN
 *                      33: YELLOW
 *                      34: BLUE
 *                      35: PURPLE(紫色)
 *                      36: CYAN(青色)
 *                      37: WHITE(白色)
 *                      --背景颜色--
 *                      40: BLACK
 *                      41: RED
 *                      42: GREEN
 *                      43: YELLOW
 *                      44: BLUE
 *                      45: PURPLE(紫色)
 *                      46: CYAN(青色)
 *                      47: WHITE(白色)
 *                ->设置文本颜色：\033[38;5;<color_code>m，其中 <color_code> 是颜色代码
 *                      0-255：16进制颜色值（例如：33，99，255）
 *                      256-511：从256色调色板中选择颜色的索引值（例如：256，500）
 *                ->设置背景颜色：\033[48;5;<color_code>m，其中 <color_code> 是颜色代码。
 *
 *              (3) Use debug
 *                  use as following code:
 *                  In your config.h file, enable/disable CONFIG_DEBUG_EN macro, and then include this
 *                  header file.
 *
 *                  #define DBG_TAG           "MOD_TAG"
 *                  #define DBG_LVL           DBG_INFO
 *                  #include <debug.h>        // must after of DBG_LVL, DBG_TAG or other options
 *
 *                  Then in your C/C++ file, you can use LOG_X macro to print out logs:
 *                  LOG_D("this is a debug log!");
 *                  LOG_E("this is a error log!");
 *
 *********************************************************************************************************
 */
#ifndef __DEBUG_H__
#define __DEBUG_H__

/**
 ************************************************************************************************************************
 *                                                 INCLUDE HEADER FILES
 ************************************************************************************************************************
 */
#include "public.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 ************************************************************************************************************************
 ************************************************************************************************************************
 *                                                   # D E F I N E S
 ************************************************************************************************************************
 ************************************************************************************************************************
 */

/**
 ========================================================================================================================
 *                                                   DEBUG ENABLE
 ========================================================================================================================
 */
#if defined(CONFIG_DEBUG_ENABLE) && !defined(DBG_ENABLE)
#define DBG_ENABLE
#endif

#if defined(CONFIG_DEBUG_DISABLE) && defined(DBG_ENABLE)
#undef DBG_ENABLE
#endif

/**
 ========================================================================================================================
 *                                                   COLOR ENABLE
 ========================================================================================================================
 */
#if defined(CONFIG_DEBUG_COLOR_ENABLE) && !defined(DBG_COLOR)
#define DBG_COLOR
#endif

/**
 ========================================================================================================================
 *                                                   DEBUG TAG
 ========================================================================================================================
 */
#ifdef DBG_TAG
#ifndef DBG_SECTION_NAME
#define DBG_SECTION_NAME    DBG_TAG
#endif
#else
/* compatible with old version */
#ifndef DBG_SECTION_NAME
#define DBG_SECTION_NAME    "DBG"
#endif
#endif /* DBG_TAG */

/**
 ========================================================================================================================
 *                                                   DEBUG LEVEL
 ========================================================================================================================
 */
#define DBG_ERROR           0
#define DBG_WARNING         1
#define DBG_INFO            2
#define DBG_LOG             3

#ifdef DBG_LVL
#ifndef DBG_LEVEL
#define DBG_LEVEL         DBG_LVL
#endif
#else
/* compatible with old version */
#ifndef DBG_LEVEL
#define DBG_LEVEL         DBG_WARNING
#endif
#endif /* DBG_LVL */

#ifdef DBG_ENABLE
/**
 ========================================================================================================================
 *                                                   DEBUG COLOR
 *
 * Note(s) : (1) The color for terminal (foreground)
 *                  BLACK   30
 *                  RED     31
 *                  GREEN   32
 *                  YELLOW  33
 *                  BLUE    34
 *                  PURPLE  35
 *                  CYAN    36
 *                  WHITE   37
 ========================================================================================================================
 */
#ifdef DBG_COLOR
#define _DBG_COLOR(n)        kprint("\033["#n"m")
#define _DBG_LOG_HDR(lvl_name, color_n)                    \
    do {                                                   \
        kprint("\033["#color_n"m");                        \
        kprintf("[" lvl_name "/" DBG_SECTION_NAME "] ");   \
    } while(0)
#define _DBG_LOG_X_END                                     \
    kprint("\033[0m\r\n")
#else
#define _DBG_COLOR(n)
#define _DBG_LOG_HDR(lvl_name, color_n)                    \
    do {                                                   \
        kprint("\033["#color_n"m");                        \
        kprintf("[" lvl_name "/" DBG_SECTION_NAME "] ");   \
    } while(0)
#define _DBG_LOG_X_END                                     \
    kprint("\r\n")
#endif /* DBG_COLOR */

#define dbg_log(level, fmt, ...)                            \
    if ((level) <= DBG_LEVEL)                               \
    {                                                       \
        switch(level)                                       \
        {                                                   \
            case DBG_ERROR:   _DBG_LOG_HDR("E", 31); break; \
            case DBG_WARNING: _DBG_LOG_HDR("W", 33); break; \
            case DBG_INFO:    _DBG_LOG_HDR("I", 32); break; \
            case DBG_LOG:     _DBG_LOG_HDR("D", 0); break;  \
            default: break;                                 \
        }                                                   \
        kprint(fmt, ##__VA_ARGS__);                         \
        _DBG_COLOR(0);                                      \
    }

#define dbg_here                                            \
    if ((DBG_LEVEL) <= DBG_LOG){                            \
        kprint(DBG_SECTION_NAME " Here %s:%d\r\n",          \
            __FUNCTION__, __LINE__);                        \
    }

#define dbg_log_line(lvl, color_n, fmt, ...)                \
    do                                                      \
    {                                                       \
        _DBG_LOG_HDR(lvl, color_n);                         \
        kprint(fmt, ##__VA_ARGS__);                        \
        _DBG_LOG_X_END;                                     \
    }                                                       \
    while (0)

#define dbg_raw(...)         kprint(__VA_ARGS__);
#else
#define dbg_log(level, fmt, ...)
#define dbg_here
#define dbg_enter
#define dbg_exit
#define dbg_log_line(lvl, color_n, fmt, ...)
#define dbg_raw(...)
#endif /* DBG_ENABLE */

/**
 ========================================================================================================================
 *                                                   LOG_X API.
 ========================================================================================================================
 */
#if (DBG_LEVEL >= DBG_LOG)
#define LOG_D(fmt, ...)      dbg_log_line("D", 0, fmt, ##__VA_ARGS__)
#else
#define LOG_D(...)
#endif

#if (DBG_LEVEL >= DBG_INFO)
#define LOG_I(fmt, ...)      dbg_log_line("I", 32, fmt, ##__VA_ARGS__)
#else
#define LOG_I(...)
#endif

#if (DBG_LEVEL >= DBG_WARNING)
#define LOG_W(fmt, ...)      dbg_log_line("W", 33, fmt, ##__VA_ARGS__)
#else
#define LOG_W(...)
#endif

#if (DBG_LEVEL >= DBG_ERROR)
#define LOG_E(fmt, ...)      dbg_log_line("E", 31, fmt, ##__VA_ARGS__)
#else
#define LOG_E(...)
#endif

#define LOG_RAW(...)         dbg_raw(__VA_ARGS__)

#define LOG_HEX(name, width, buf, size)

#ifdef __cplusplus
}
#endif

#endif /* __DEBUG_H__ */
