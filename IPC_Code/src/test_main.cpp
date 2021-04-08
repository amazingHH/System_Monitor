#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "IPC_Timer.h"
#include "IPC_Common.h"



int main(void)
{
    int Timer_Handler = 0;
    IPC_Timer Timer_1;
    Err_Type ret = No_Err;
    Timer_Eclapsed timer_ret = ECLAPSED_IDEL;
    printf("1 \n");
    ret = Timer_1.Timer_Register(&Timer_Handler);
    printf("2 \n");
    while(1)
    {
        printf("3 \n");
        ret = Timer_1.Timer_Start(Timer_Handler, 3);
        printf("4 \n");
        sleep(2);
        timer_ret = Timer_1.Timer_State_Check(Timer_Handler);
        printf("timer ret is %d\n", timer_ret);
        if(timer_ret == ECLAPSED_YES)
        {
            printf("the timer is over \n");
        }
        printf("\n\n\n\n");
    }
    printf("Hello World \n");
    return 1;
}

