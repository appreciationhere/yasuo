#ifndef _BSP_FMC_H__
#define _BSP_FMC_H__

/**
  * @brief FMC for stm32h750 Initialization Function
  * @param instance: switch instance you want
  * @retval the point of fmc_dev_s
  */
void* bsp_board_fmc_init(int instance);

#endif // !_BSP_FMC_H__