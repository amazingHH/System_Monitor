/***************************************************************
 * IPC_Common.c
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
#include"IPC_Common.h"

static int com(int flags, string id)
{
    key_t key=ftok(PATHNAME,PROJ_ID);
    if(key<0)
    {
        perror("ftok");
        return -1;
    }
    int msgid=msgget(key,flags);
    if(msgid<0)
    {
        perror("msgget");
        return -2;
    }
    return msgid;
}
 
int creat(string id)
{
    return com(IPC_CREAT|IPC_EXCL|0666, id);
}
 
int destory(int msgid)
{
   if(msgctl(msgid,IPC_RMID,NULL)<0)
   {
        perror("msgctr");
        return -1;
   }
}
 
int get(string id)
{
    return com(IPC_CREAT, id);
}
 
int send(int msgid,int who,char *msg)
{
     struct msgbuf buf;
     buf.mtype=who;
     strcpy(buf.mtext,msg);
     if(msgsnd(msgid,(void*)&buf,sizeof(buf.mtext),0)<0)
     {
         perror("msgsnd");
         return -1;
     }
}
 
int recv(int msgid,int type,char out[])
{
     struct msgbuf buf;
     if(msgrcv(msgid,(void*)&buf,sizeof(buf.mtext),type,0)<0)
     {
         perror("msgrcv");
         return -1;
     }
     strcpy(out,buf.mtext);
     return 0;
}


