#include <hal/board.h>
#include <sdram/sdram.h>
#include "syslog.h"
#ifdef CONFIG_STM32H750_ART_PI

/* init befor system in module_task_init */
int board_init_pre(void)
{
    int ret = 0;
    syslog(LOG_INFO, "board_init_pre start ...");
    bsp_InitExtSDRAM();
    syslog(LOG_INFO, "board_init_pre end ...");
    return ret;
}
/* driver init */
int board_init_later(void)
{
    int ret = 0;

    return ret;
}

/* after all task init */
int board_init_final(void)
{
    int ret = 0;

    return ret;
}




#endif // CONFIG_STM32H750_ART_PI