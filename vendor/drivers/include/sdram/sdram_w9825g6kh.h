
#ifndef _BSP_FMC_SDRAM_H
#define _BSP_FMC_SDRAM_H
#include <fmc/fmc_com.h>
struct sdram_w9825g_config_s {
    struct fmc_ops_s *bus;
};

int sdram_w9825g6kh_init(int devno, struct sdram_w9825g_config_s* config);

#endif

