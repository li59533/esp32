#include <stdio.h>
#include "clog.h"
#include "rtos_tools.h"
#include "task_list.h"
#include "system_param.h"


void app_main()
{
    RTOS_Delay_ms(1000);
    DEBUG("Version:\n");
    RTOS_Delay_ms(1000);
    DEBUG("Start\n");
    SystemParam_Init();
    SystemParam_Read();

    RTOS_Init();
}

