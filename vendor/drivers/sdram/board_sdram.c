#include <sdram/sdram.h>
#include <hal/bsp_fmc.h>

int board_sdram_init(int devno, int busno)
{
    int ret = 0;
    #ifdef CONFIG_SDRAM_W9825G6KH
    struct sdram_w9825g_config_s config;
    config.bus = bsp_board_fmc_init(busno);
    
    #endif // CONFIG_SDRAM_W9825G6KH
    return ret;
}