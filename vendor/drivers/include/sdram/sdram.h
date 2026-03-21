#ifndef _SDRAM_H__
#define _SDRAM_H__

#ifdef CONFIG_SDRAM_W9825G6KH
#include <sdram/sdram_w9825g6kh.h>
#endif // CONFIG_SDRAM_W9825G6KH

void bsp_InitExtSDRAM(void);



#endif // !_SDRAM_H__