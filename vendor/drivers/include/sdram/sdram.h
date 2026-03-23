#ifndef _SDRAM_SDRAM_H__
#define _SDRAM_SDRAM_H__
#include <common.h>

#ifdef CONFIG_SDRAM_W9825G6KH
#include <sdram/sdram_w9825g6kh.h>
#endif // CONFIG_SDRAM_W9825G6KH

#define SDRAM_TEST_FUC      1

int board_sdram_init(int devno, int busno);

#if SDRAM_TEST_FUC

void ReadSpeedTest(void);

void WriteSpeedTest(void);

#endif // SDRAM_TEST_FUC

#endif // !_SDRAM_H__