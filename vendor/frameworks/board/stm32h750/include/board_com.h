/*
 *    This header file for board dir file call, board dir rely on function
 */

#ifndef __BOARD_COM_H_
#define __BOARD_COM_H_

#include <common.h>
#include "system.h"
#ifdef CONFIG_STM32_HAL
#include "stm32h7xx_hal.h"
#endif

#ifdef CONFIG_STM32H750_ART_PI
#include "board_art_pi.h"
#endif // CONFIG_STM32H750_ART_PI

#ifdef CONFIG_STM32_HAL
#define HAL_DELAY_MS(n)           HAL_Delay(n)
#else
#error "need choose platform for delay function"
#endif // CONFIG_STM32_HAL

#endif // !__BOARD_COM_H_
