
#ifndef _BSP_FMC_SDRAM_H
#define _BSP_FMC_SDRAM_H

#define W9825G_SDRAM_TEST   1

#if W9825G_SDRAM_TEST

void ReadSpeedTest(void);

void WriteSpeedTest(void);

#endif // W9825G_SDRAM_TEST

void bsp_InitExtSDRAM(void);

#endif

