/*
 * Copyright (c) 2021, Eureka1024 <eureka1024@qq.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2021-11-15     Eureka1024    Add blocking delay function
 * 2021-11-15     Eureka1024    Add events as synchronization mechanism
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

/**
 * NoOs event struct
 */
typedef struct NoOsEventDef
{
    uint32_t OsSet;
}NoOsEventDef;

#define NoOsEventSend(Event, Set)   (Event)->OsSet |= Set  //Send event

#define NoOsEventRecv(Event, Set, Option)               \
{                                                       \
case __LINE__ :                                         \
    CurrentTask->JumpLabel = __LINE__;                  \
    if(Option == NOOS_EVENT_FLAG_AND)                   \
    {                                                   \
        if(((Event)->OsSet & Set) != Set)               \
        {                                               \
            return ;                                    \
        }                                               \
    }                                                   \
    else                                                \
    {                                                   \
        if(!((Event)->OsSet & Set))                     \
        {                                               \
            return ;                                    \
        }                                               \
    }                                                   \
    (Event)->OsSet &= ~Set;                             \
}

#endif
