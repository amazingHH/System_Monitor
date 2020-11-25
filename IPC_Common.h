/***************************************************************
 * IPC_Common.h
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
#ifndef _IPC_COMM_H_
#define _IPC_COMM_H_


#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>

#define SERVER 1
#define CLIENT 2

#define IPC_CLIENT_NUM 4

#define PATHNAME "."
#define AUDIO "usr/bin/local/audio"
#define MEDIA  "usr/bin/local/media"
#define HMI    "usr/bin/local/hmi"
#define NEEDLE    "usr/bin/local/needle"

#define PROJ_ID 0x6666

struct msgbuf
{
    long mtype;
    char mtext[1024];
};

enum {
No_Err,
Err,
} Err_Type;

const string G_IPC_ID[IPC_CLIENT_NUM] = {
AUDIO,
MEDIA,
HMI,
NEEDLE,
};

int creat(string id);      //创建消息队列
int send(int msgid,int who,char*msg);    //发送消息
int recv(int msgid,int type,char out[]); //接收消息
int destory(int msgid);       //销毁消息队列
int get(string id);       //获得消息队列的标识符

#endif

