#ifndef _NOOS_LIB_H
#define _NOOS_LIB_H
#include "NoOs.h"

#define NoOsDelayMs(nMs)                                \
{                                                       \
    if ((GetNoOsTick() - CurrentTask->TaskTick) < nMs)  \
    {                                                   \
        return ;                                        \
    }                                                   \
    CurrentTask->TaskTick = GetNoOsTick();              \
}

#endif