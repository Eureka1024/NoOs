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
 
#include "NoOs.h"

volatile uint32_t NoOsTick;   //Record system ticks

NoOsTaskDef  IdleTask;    //Idle task
NoOsTaskDef* CurrentTask; //Point to current task

/**
 * @brief  Callback function for idle task.
 * @param  None.
 * @retval None.
 */
void IdleTaskCallback(void)
{

}

/**
 * @brief  Initialize NoOs.
 * @param  None.
 * @retval None.
 */
void InitNoOs(void)
{
    IdleTask.Callback = IdleTaskCallback; //Callback function for idle tasks
    IdleTask.Priority = 3;     //The default priority of idle tasks is 3
    IdleTask.WaitTimes = IdleTask.Priority; //Wait times
    IdleTask.TaskTick = GetNoOsTick(); //Task tick
    IdleTask.JumpLabel = 0;            //Jump label
    IdleTask.Next = &IdleTask;  //One way circular linked list
    
    CurrentTask = &IdleTask; //Init CurrentTask
    NoOsTick = 0;   //Init NoOsTick
}

/**
 * @brief  Insertion of linked list.
 * @param  Target: the target node strcut.
 * @param  New: the new node strcut.
 * @retval None.
 */
static void ListInsertAfter(NoOsTaskDef* Target, NoOsTaskDef* New)
{
    New->Next = Target->Next;
    Target->Next = New;
}

/**
 * @brief  Initialize a new NoOs's task.
 * @param  NewTask: the new task.
 * @param  Callback: the callback function of of new task.
 * @param  Priority: task's priority.
 * @retval None.
 */
int InitNoOsTask(NoOsTaskDef* NewTask, void(*Callback)(void), uint32_t Priority)
{
    //Avoid repeating initialization tasks
    if (NewTask->Priority != 0) return FALSE;

    NewTask->Callback = Callback;
    NewTask->Priority = Priority;
    NewTask->WaitTimes = NewTask->Priority;
    NewTask->TaskTick = GetNoOsTick();
    NewTask->JumpLabel = 0;

    ListInsertAfter(&IdleTask,NewTask);
    
    return TRUE;
}

/**
 * @brief  Scheduling NoOs's task.
 * @param  None.
 * @retval None.
 */
void StartNoOsScheduler(void)
{
    while(1)
    {
        CurrentTask = CurrentTask->Next;
        
        if ((CurrentTask->WaitTimes --) == 0)
        {
            CurrentTask->WaitTimes = CurrentTask->Priority;
            CurrentTask->Callback();
        }
    }
}

/**
 * @brief  Get system clock tick.
 * @param  None.
 * @retval NoOs's clock tick.
 */
uint32_t GetNoOsTick(void)
{
    return NoOsTick;
}
