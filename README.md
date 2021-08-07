# NoOs #

[![GitHub](https://img.shields.io/github/license/RT-Thread/rt-thread.svg)](https://github.com/Eureka1024/NoOs/LICENSE)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg?style=flat)](https://github.com/Eureka1024/NoOs)

[toc]



## 简介

NoOs 名字的寓意取自于："NoOs is not an operating system"。虽然不是传统意义的操作系统，但是 NoOs 的目标是提供类似RTOS的开发方式，其代码量比较小，使用简单易懂，占用资源非常小，适用于资源较小的嵌入式系统，能够帮助你快速实现产品。因为是纯 C 语言实现，易于移植到不同的平台。

遵循 Apache License 2.0 开源许可协议，可以免费在商业产品中使用，并且不需要公开私有代码。



## 代码目录

NoOs 源代码的结构如下所示:

| Name | Description           |
| ---- | --------------------- |
| NoOs | NoOs 的源代码和头文件 |



## API 说明

外部使用的 API 极少，只有四个，所以使用起来相当的简单。

- **void InitNoOs(void);**

  描述：初始化 NoOs 系统。

- **void SchedulingTask(void);**

  描述：用于调度加入调度器的任务。

- **void InitNoOsTask(NoOsTaskDef* NewTask, void(*Callback)(void), uint32_t InitTick);**

  描述：用于初始化新的任务并将其加入调度器。

  输入参数：

  - NewTask：新任务
  - Callback：新任务的回调函数
  - InitTick：每运行一次任务需要等待的系统时钟心跳的次数

- **uint32_t GetNoOsTick(void);**

  描述：获取系统时钟心跳的次数。



## 移植

因为 NoOs 是纯 C 语言实现的，所以在不同的硬件设备间移植起来很简单。

详细移植过程如下所示：

- 将源代码目录中的 NoOs.c 加入项目工程目录。

  以 STM32 在 Keil MDK5 开发为例：

  ![image-20210807092758057](https://gitee.com/Eureka1024/my-image-hosting-service/raw/master/img/20210807092758.png)



- 将源代码目录中的 NoOs.h 加入项目工程头文件包含路径。

  以 STM32 在 Keil MDK5 开发为例：

  ![image-20210807093328520](https://gitee.com/Eureka1024/my-image-hosting-service/raw/master/img/20210807093328.png)

- 在 main.c 函数中加入 InitNoOs() 函数，用于初始化 NoOs 系统，在无限循环 While(1) 中调用 SchedulingTask() 函数，用于调度任务。

  以 STM32 在 Keil MDK5 开发为例：

  ```c
  #include "NoOs.h"
  
  int main(void)
  {
    /* MCU Configuration--------------------------------------------------------*/
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();
    /* Configure the system clock */
    SystemClock_Config();
    /* Initialize all configured peripherals */
    MX_GPIO_Init();
  
    /* Init NoOs */
    InitNoOs();
  
    while (1)
    {
      SchedulingTask();
    }
  }
  ```

  

## 快速上手

以建立一个 LED 闪烁显示的任务为例，使用的硬件依然是 STM32。

首先完成任务运行基础：

- 使用 STM32CubeMx 建立 STM32 工程，完成基本设置，配置好 LED 控制引脚 对应的 GPIO 引脚，设置 SysTick 时钟，默认是 1ms 中断一次。
- 按上节移植过程配置好 NoOs 运行的基本条件。

建立 LED 显示任务：

- 定义 LED 任务的结构体

  ```c
  NoOsTaskDef LedDisplayTask;
  ```

- 定义 LED 任务的回调函数(其中GetNoOsTick()用于实现非阻塞延时)，功能是让 LED 灯 1Hz 频率闪烁。 

  ```c
  void LedDisplayCallback(void)
  {
      static uint32_t LedDelayTick;
      
      if((GetNoOsTick() - LedDelayTick) > 500)
      {
          LedDelayTick = GetNoOsTick();
          HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_8);
      }
  }
  
  ```

- 在 main() 中的 InitNoOs() 后调用任务初始化函数，成功将其加入任务调度中。

  ```c
  InitNoOsTask(&LedDisplayTask, LedDisplayCallback, 1); 
  ```

下面是完整的代码：

```c
#include "NoOs.h"

NoOsTaskDef LedDisplayTask;

void LedDisplayCallback(void)
{
    static uint32_t LedDelayTick;
    
    if((GetNoOsTick() - LedDelayTick) > 500)
    {
        LedDelayTick = GetNoOsTick();
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_8);
    }
}

int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  /* Configure the system clock */
  SystemClock_Config();
  /* Initialize all configured peripherals */
  MX_GPIO_Init();

  /* Init NoOs */
  InitNoOs();
  
  /* Init LedDisplay task */
  InitNoOsTask(&LedDisplayTask, LedDisplayCallback, 1); 
    
  while (1)
  {
    SchedulingTask();
  }
}
```

实现效果如下所示：

![led2](https://gitee.com/Eureka1024/my-image-hosting-service/raw/master/img/20210807103518.gif)



## 更多示例

**敬请期待！**



## License

NoOs 是一个开源软件，遵循 Apache-2.0 许可版本。许可证信息和版权信息一般可以在代码的开头看到::

```c
/*
 * Copyright (c) 2021, Eureka1024 <eureka1024@qq.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * ......
 */
```


