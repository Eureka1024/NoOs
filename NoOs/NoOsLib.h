/*
 * Copyright (c) 2021, Eureka1024 <eureka1024@qq.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2021-11-15     Eureka1024    Add blocking delay function
 */
#ifndef _NOOS_LIB_H
#define _NOOS_LIB_H
#include "NoOs.h"

#define NoOsDelayMs(nMs)                                \
{                                                       \
case __LINE__ :                                         \
    CurrentTask->JumpLabel = __LINE__;                  \
    if((GetNoOsTick() - CurrentTask->TaskTick) < nMs)   \
    {                                                   \
        return ;                                        \
    }                                                   \
    CurrentTask->TaskTick = GetNoOsTick();              \
}

#endif