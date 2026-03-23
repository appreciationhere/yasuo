#ifndef _BSP_FMC_H__
#define _BSP_FMC_H__

#include <common.h>

#ifdef CONFIG_STM32H750
#include "fmc.h"
#define BSP_FMC_SDRAM_CMD_CLK_ENABLE          FMC_SDRAM_CMD_CLK_ENABLE
#define BSP_FMC_SDRAM_CMD_PALL                FMC_SDRAM_CMD_PALL
#define BSP_FMC_SDRAM_CMD_AUTOREFRESH_MODE    FMC_SDRAM_CMD_AUTOREFRESH_MODE
#define BSP_FMC_SDRAM_CMD_LOAD_MODE           FMC_SDRAM_CMD_LOAD_MODE

#endif // CONFIG_STM32H750

/**
  * @brief FMC for stm32h750 Initialization Function
  * @param instance: switch instance you want
  * @retval the point of fmc_dev_s
  */
void* bsp_board_fmc_init(int instance);

#endif // !_BSP_FMC_H__