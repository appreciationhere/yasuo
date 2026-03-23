#include <sdram/sdram.h>
#include <drv_com.h>

#define GBG_TAG				"[sdram]"
#define LOG_I(fmt, ...)      DRV_LOG_INF(GBG_TAG fmt, ##__VA_ARGS__)
#define LOG_E(fmt, ...)      DRV_LOG_ERR(GBG_TAG fmt, ##__VA_ARGS__)
#define LOG_D(fmt, ...)      DRV_LOG_DBG(GBG_TAG fmt, ##__VA_ARGS__)
#define LOG_M(fmt, ...) \
    DRV_LOG_INF(GBG_TAG "[%s][%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)

int board_sdram_init(int devno, int busno)
{
    int ret = 0;
    #ifdef CONFIG_SDRAM_W9825G6KH
    struct sdram_w9825g_config_s config;
    config.bus = bsp_board_fmc_init(busno);
    ret = sdram_w9825g6kh_init(devno, &config);
    if (ret >= 0) {
        LOG_E("init sdram_w9825g6kh_init success !!! ");
    }
    else {
        LOG_E("init sdram_w9825g6kh_init fail ret:%d !!! ", ret);
        goto _end;
    }
    #endif // CONFIG_SDRAM_W9825G6KH
_end:
    return ret;
}