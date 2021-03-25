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

#include "IPC_Proxy_Base.h"

char* G_IPC_ID[IPC_CLIENT_NUM] = {
MONITOR,
AUDIO,
MEDIA,
HMI,
NEEDLE,
};

Proxy_Basework::~Proxy_Basework()
{
	printf("~Proxy_Basework \n");
}

Err_Type Proxy_Basework :: IPC_Rigester(void)
{
    int client_index = 0;
	Err_Type retval = No_Err;
    for(client_index = 0; client_index < IPC_CLIENT_NUM; client_index++)
    {
        Proxy_Basework::Handler_arr[client_index] = creat(G_IPC_ID[client_index]);
	    if ((Handler_arr[client_index] == -1) || (Handler_arr[client_index] == -2))
	    {
	        retval = Err;
	        return retval;
	    }
    }
	return retval;
}

Err_Type Proxy_Basework::IPC_Initial(void)
{
	Err_Type retval = No_Err;
	retval = Proxy_Basework :: IPC_Rigester();
	if (retval == Err)
	{
		retval = Err;
		return retval;
	}
	return retval;
}

Err_Type Proxy_Basework::FAH_Send(int msgid,int who,char *msg)
{
	Err_Type retval = No_Err;
	retval = static_cast<Err_Type>(send(msgid,who,msg));
	if (retval == -1)
	{
	    retval = Err;
		return retval;
	}
	return retval;
}

Err_Type Proxy_Basework::FAH_Recv(int msgid,int type,char *out)
{
    Err_Type retval = No_Err;
	retval = static_cast<Err_Type>(recv(msgid,type,out));
	if (retval == -1)
	{
	    retval = Err;
		return retval;
	}
	return retval;

}

Err_Type Proxy_Basework::Get_Handler(char* id)
{
    Err_Type retval = No_Err;
	retval = static_cast<Err_Type>(get(id));
	if (retval == -1)
	{
	    retval = Err;
		return retval;
	}
	return retval;

}

