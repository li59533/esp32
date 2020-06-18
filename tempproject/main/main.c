#include <stdio.h>
#include "clog.h"
#include "rtos_tools.h"
#include "task_list.h"

void app_main()
{
    RTOS_Delay_ms(1000);
    DEBUG("Version:\n");
    RTOS_Delay_ms(1000);
    DEBUG("Start\n");

    RTOS_Init();
}

