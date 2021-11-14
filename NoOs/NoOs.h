/*
 * Copyright (c) 2021, Eureka1024 <eureka1024@qq.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2021-08-05     Eureka1024    the first version
 */

#ifndef _NO_OS_H
#define _NO_OS_H

#include "tb_interface.h"

#define TRUE  1
#define FALSE 0

/**
 * NoOs task struct
 */
typedef struct NoOsTaskDef
{
	void (*Callback)(void);   //callback function of task 
    uint32_t Priority;        //priority of task
	uint32_t WaitTimes;       //wait times
    struct NoOsTaskDef* Next; //point to next task
    uint32_t TaskTick;        //task tick
}NoOsTaskDef;

extern volatile uint32_t NoOsTick; //NoOs's clock tick

void InitNoOs(void);
void StartNoOsScheduler(void);
int InitNoOsTask(NoOsTaskDef* NewTask, void(*Callback)(void), uint32_t Priority);
uint32_t GetNoOsTick(void);

#endif
