/*
 * Copyright (c) 2021, Eureka1024 <eureka1024@qq.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2021-08-05     Eureka1024    the first version
 * 2021-11-15     Eureka1024    Add blocking delay function
 */
#ifndef _NO_OS_H
#define _NO_OS_H

#include "tb_interface.h"
#include "NoOsLib.h"

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
    uint32_t TaskTick;        //task tick
    uint32_t JumpLabel;       //jump label
    struct NoOsTaskDef* Next; //point to next task
}NoOsTaskDef;


#define NoOsTaskBegin()   switch(CurrentTask->JumpLabel) { case 0:

#define NoOsTaskEnd()    } CurrentTask->JumpLabel = 0;

extern volatile uint32_t NoOsTick; //NoOs's clock tick
extern NoOsTaskDef* CurrentTask;
void InitNoOs(void);
void StartNoOsScheduler(void);
int InitNoOsTask(NoOsTaskDef* NewTask, void(*Callback)(void), uint32_t Priority);
uint32_t GetNoOsTick(void);

#endif
