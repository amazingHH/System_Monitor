/***************************************************************
 * IPC_Proxy_Base.cpp
 *
 * Copyright (C) 2020-2120 Francois Alex Hao <297008410@qq.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 or version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>
#include "math.h"
#include "IPC_Common.h"


#define BASE_LINE 0x2188

enum Timer_State{
TIMER_IDLE = 0,
TIMER_STOP,
TIMER_START,
TIMER_MAX
};

enum Timer_Eclapsed{
ECLAPSED_IDEL = 0,
ECLAPSED_NO,
ECLAPSED_YES,
ECLAPSED_MAX,
};

typedef struct Timer{
int m_handler;
Timer_State m_state;
int m_duration;
struct timeval m_start;
Timer_Eclapsed m_eclapsed_state;
}TIMER_ST; 

class IPC_Timer{

private:
    
    Err_Type Timer_Mutex_Init(void);
    Err_Type Timer_Mutex_Destory(void);
    Err_Type Timer_Initial(void);
    pthread_mutex_t m_Timer_Mutex =  PTHREAD_MUTEX_INITIALIZER;

public:
    IPC_Timer();
    ~IPC_Timer();
    Err_Type Timer_Register(int *handler);
    Err_Type Timer_Start(int handler, int duration);
    Err_Type Timer_Check(int handler);
    Err_Type Timer_Stop(int handler);
    Timer_Eclapsed Timer_State_Check(int handler);


};
