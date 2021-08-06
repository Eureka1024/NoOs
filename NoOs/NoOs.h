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

#include <stdint.h>

/**
 * NoOs����ṹ��
 */
typedef struct NoOsTaskDef
{
	void (*Callback)(void);  //����ص�����
	struct NoOsTaskDef* Next;//ָ����һ������
	uint32_t RemainingTick;  //ʣ��ʱ��Ƭ
	uint32_t InitTick;       //ʱ��Ƭ����ֵ
}NoOsTaskDef;

extern volatile uint8_t  OneNoOsTickFlag;
extern volatile uint32_t NoOsTick;

void InitNoOs(void);
void SchedulingTask(void);
void InitNoOsTask(NoOsTaskDef* NewTask, void(*Callback)(void), uint32_t InitTick);
uint32_t GetNoOsTick(void);

#endif
