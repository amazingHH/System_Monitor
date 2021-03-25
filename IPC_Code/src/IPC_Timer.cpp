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

#include "IPC_Timer.h"

static TIMER_ST Timer_Array[100] = {};
unsigned char Timer_Index = 0;

void * Timer_Main_Loop(void *arg)
{
    int i = 0;
    while(1)
    {
        for(i = 0; i< 100; i++)
        {
            if (Timer_Array[i].m_state == TIMER_START)
            {
                struct timeval end;
                gettimeofday(&end,NULL);
                if (((end.tv_sec-Timer_Array[i].m_start.tv_sec) * 10^6 + end.tv_usec - Timer_Array[i].m_start.tv_usec) > Timer_Array[i].m_duration)
                {
                    Timer_Array[i].m_eclapsed_state = ECLAPSED_YES;
                    Timer_Array[i].m_state = TIMER_STOP;
                    Timer_Array[i].m_duration = 0;
                }
            }
        }
    }
}
 
IPC_Timer::IPC_Timer(){
    IPC_Timer::Timer_Initial();
    printf("IPC_Timer Construction\n");
}

IPC_Timer::~IPC_Timer(){
    printf("~IPC_Timer \n");
    IPC_Timer::Timer_Mutex_Destory();
    printf("Timer_Mutex destory \n");
}

Err_Type IPC_Timer::Timer_Initial(void)
{
    int i = 0;
    pthread_t tid1;
    int thread_err = 0;
    memset(Timer_Array, 0, 100 * sizeof(TIMER_ST));
    for (i = 0; i < 100; i++)
    {
        Timer_Array[i].m_handler = BASE_LINE + i;
    }
    thread_err = pthread_create(&tid1, NULL, Timer_Main_Loop, NULL);
    return No_Err;
}

Err_Type IPC_Timer::Timer_Register(int *handler)
{
    *handler = Timer_Array[Timer_Index].m_handler;
}


Err_Type IPC_Timer::Timer_Start(int handler, int duration)
{
    int i = 0;
    pthread_mutex_lock(&m_Timer_Mutex);
    for (i = 0; i < 100; i++)
    {
        if (Timer_Array[i].m_handler == handler)
        {
            Timer_Array[i].m_duration = duration;
            Timer_Array[i].m_state =  TIMER_START;
            Timer_Array[i].m_eclapsed_state = ECLAPSED_NO;
            gettimeofday(&(Timer_Array[i].m_start),NULL);
            break;
        }
    }
    pthread_mutex_unlock(&m_Timer_Mutex);

}



Err_Type IPC_Timer::Timer_Mutex_Init(void)
{
    Err_Type ret = No_Err;
    int mutex_ret = 0;
#ifdef linux_x64
    mutex_ret = pthread_mutex_init(&m_Timer_Mutex, NULL);
#endif
    if(mutex_ret != 0)
    {
        ret = Err;
    }
    return ret;
}

Err_Type IPC_Timer::Timer_Mutex_Destory(void)
{
    Err_Type ret = No_Err;
    int mutex_ret = 0;
#ifdef linux_x64
    mutex_ret = pthread_mutex_destroy(&m_Timer_Mutex);
#endif
    if(mutex_ret != 0)
    {
        ret = Err;
    }
    return ret;
}

Timer_Eclapsed IPC_Timer::Timer_State_Check(int handler)
{
    int i = 0;
    Timer_Eclapsed ret = ECLAPSED_IDEL;
    for (i = 0; i< 100; i++)
    {
        if(Timer_Array[i].m_handler == handler)
        {
            ret = Timer_Array[i].m_eclapsed_state;
        }
    }
    return ret;
}