/***************************************************************
 * IPC_Proxy.h
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

#ifndef _IPC_PROXY_H_
#define _IPC_PROXY_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "math.h"
#include "IPC_Proxy_Base.h"
#include "IPC_Common.h" 

class IPC_Proxy : public Proxy_Basework{
public:
    Err_Type IPC_Bulk_Send(int msgid,int who,char *msg);
    Err_Type IPC_Bulk_Rcv(int msgid,int who,char *msg);
    Err_Type IPC_Despatch_Send(int msgid,int who,char *msg);
    Err_Type IPC_Despatch_Rcv(int msgid,int who,char *msg);
private:
    Err_Type IPC_Message_Package(unsigned char * data);
    Err_Type IPC_Message_Unpackage(unsigned char * data);

};

#endif