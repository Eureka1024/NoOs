/*
 * Copyright (c) 2021, Eureka1024 <eureka1024@qq.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2021-08-05     Eureka1024    the first version
 */
 
#include "NoOs.h"

volatile uint8_t  OneNoOsTickFlag;//���һ��ϵͳ�δ�ĵ���
volatile uint32_t NoOsTick;       //��¼�δ�ʱ����

NoOsTaskDef  IdleTask;    //��������
NoOsTaskDef* CurrentTask; //ָ��ǰִ�е�����

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
    IdleTask.Next = &IdleTask;  //���ɵ�ѭ������
    IdleTask.RemainingTick = 1; //���ɸ���
    IdleTask.InitTick = 1;      //���ɸ���
    IdleTask.Callback = IdleTaskCallback;
    CurrentTask = &IdleTask;   
    NoOsTick = 0;
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
 * @param  InitTick: task's initialized tick.
 * @retval None.
 */
void InitNoOsTask(NoOsTaskDef* NewTask, void(*Callback)(void), uint32_t InitTick)
{
    if ((NewTask->InitTick == 0) && (InitTick != 0)) //�����ظ���ʼ������&&�������������
    {
        NewTask->Callback = Callback;
        NewTask->RemainingTick = InitTick;
        NewTask->InitTick = InitTick;
        ListInsertAfter(&IdleTask,NewTask);
    }
}

/**
 * @brief  Scheduling NoOs's task.
 * @param  None.
 * @retval None.
 */
void SchedulingTask(void)
{
    if(OneNoOsTickFlag)
    {
        OneNoOsTickFlag = 0;
        
        while(1)
        {
            CurrentTask = CurrentTask->Next;
            
            if ((-- CurrentTask->RemainingTick) == 0)
            {
                CurrentTask->RemainingTick = CurrentTask->InitTick;
                CurrentTask->Callback();
                
                if (CurrentTask == &IdleTask)
                {
                    break;
                }
            }
        }
    }
}

/**
 * @brief  Get system clock tick.
 * @param  None.
 * @retval Clock tick.
 */
uint32_t GetNoOsTick(void)
{
    return NoOsTick;
}
