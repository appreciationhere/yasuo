#include "fmc.h"
#include <drv_com.h>
#include <fmc_com.h>
#include <hal/board.h>

#define SDRAM_TIMEOUT                    ((uint32_t)0xFFFF)
#define REFRESH_COUNT                    ((uint32_t)1543)    /* SDRAM自刷新计数 */  

#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)

static int SDRAM_SendCommand(uint32_t CommandMode, uint32_t Bank, uint32_t RefreshNum, uint32_t RegVal)
{
    uint32_t CommandTarget = 0;
    FMC_SDRAM_CommandTypeDef Command;
    
    if (Bank == 1) {
        CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
    } else if (Bank == 2) {
        CommandTarget = FMC_SDRAM_CMD_TARGET_BANK2;
    }
    
    Command.CommandMode = CommandMode;
    Command.CommandTarget = CommandTarget;
    Command.AutoRefreshNumber = RefreshNum;
    Command.ModeRegisterDefinition = RegVal;
    
    if (HAL_SDRAM_SendCommand(&hsdram1, &Command, 0x1000) != HAL_OK) {
        return -1;
    }
    
    return 0;
}

void bsp_InitExtSDRAM(void)
{
	uint32_t temp;
/* 1. 时钟使能命令 */
    SDRAM_SendCommand(FMC_SDRAM_CMD_CLK_ENABLE, 1, 1, 0);

    /* 2. 延时，至少100us */
    HAL_Delay(1);
    
    /* 3. SDRAM全部预充电命令 */
    SDRAM_SendCommand(FMC_SDRAM_CMD_PALL, 1, 1, 0);
    
    /* 4. 自动刷新命令 */
    SDRAM_SendCommand(FMC_SDRAM_CMD_AUTOREFRESH_MODE, 1, 8, 0);
    
    /* 5. 配置SDRAM模式寄存器 */   
    temp = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1            |          //设置突发长度：1
                     SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL     |          //设置突发类型：连续
                     SDRAM_MODEREG_CAS_LATENCY_3             |          //设置CL值：3
                     SDRAM_MODEREG_OPERATING_MODE_STANDARD   |          //设置操作模式：标准
                     SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;              //设置突发写模式：单点访问  
    SDRAM_SendCommand(FMC_SDRAM_CMD_LOAD_MODE, 1, 1, temp);
    
    /* 6. 设置自刷新频率 */
    /*
        SDRAM refresh period / Number of rows）*SDRAM时钟速度 – 20
      = 64000(64 ms) / 4096 *108MHz - 20
      = 1667.5 取值1668
    */
    HAL_SDRAM_ProgramRefreshRate(&hsdram1, 2480);
}


#if W9825G_SDRAM_TEST
/*
*********************************************************************************************************
*	函 数 名: WriteSpeedTest
*	功能说明: 写SDRAM速度测试
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void WriteSpeedTest(void)
{
	uint32_t i, j;
	int32_t iTime1, iTime2;
	uint32_t *pBuf;


	/* 设置初始化值并记下开始时间 */
	j = 0;
	pBuf = (uint32_t *)SDRAM_ADDR_SART;
	iTime1 = GET_TICK_MS();
	
	/* 以递增的方式写数据到SDRAM所有空间 */
	for (i = 1024*1024/4; i >0 ; i--)
	{
		*pBuf++ = j++;
		*pBuf++ = j++;
		*pBuf++ = j++;
		*pBuf++ = j++;
		*pBuf++ = j++;
		*pBuf++ = j++;
		*pBuf++ = j++;
		*pBuf++ = j++;	

		*pBuf++ = j++;
		*pBuf++ = j++;
		*pBuf++ = j++;
		*pBuf++ = j++;
		*pBuf++ = j++;
		*pBuf++ = j++;
		*pBuf++ = j++;
		*pBuf++ = j++;	

		*pBuf++ = j++;
		*pBuf++ = j++;
		*pBuf++ = j++;
		*pBuf++ = j++;
		*pBuf++ = j++;
		*pBuf++ = j++;
		*pBuf++ = j++;
		*pBuf++ = j++;	

		*pBuf++ = j++;
		*pBuf++ = j++;
		*pBuf++ = j++;
		*pBuf++ = j++;
		*pBuf++ = j++;
		*pBuf++ = j++;
		*pBuf++ = j++;
		*pBuf++ = j++;	
	}
	iTime2 = GET_TICK_MS();	/* 记下结束时间 */
	
    /* 读取写入的是否出错 */
	j = 0;
	pBuf = (uint32_t *)SDRAM_ADDR_SART;
	for (i = 0; i < 1024*1024*8; i++)
	{
		if(*pBuf++ != j++)
		{
			DRV_LOG_INF("写入出错 j=%d\r\n", j);
			break;
		}
	}
		
	/* 打印速度 */
	DRV_LOG_INF("【32MB数据写耗时】: 方式一:%dms, 写速度: %dMB/s\r\n", 
	                  iTime2 - iTime1, (SDRAM_ADDR_LEN / 1024 /1024 * 1000) / (iTime2 - iTime1));
}
void ReadSpeedTest(void)
{
	uint32_t i;
	int32_t iTime1, iTime2;
	uint32_t *pBuf;
	__IO  uint32_t ulTemp = 0; /* 设置为__IO类型，防止被MDK优化 */

	/* 设置初始化值并记下开始时间 */
	pBuf = (uint32_t *)SDRAM_ADDR_SART;
	iTime1 = GET_TICK_MS();	
	DRV_LOG_INF("test buf1 : %lu", pBuf[1]);
	// pBuf[1] = 100;
	// DRV_LOG_INF("test buf2 : %lu", pBuf[1]);
	/* 读取SDRAM所有空间数据 */	
	// for (i = 1024*1024/4; i >0 ; i--)
	// {
	// 	ulTemp = *pBuf++;
	// 	ulTemp = *pBuf++;
	// 	ulTemp = *pBuf++;
	// 	ulTemp = *pBuf++;
	// 	ulTemp = *pBuf++;
	// 	ulTemp = *pBuf++;
	// 	ulTemp = *pBuf++;
	// 	ulTemp = *pBuf++;

	// 	ulTemp = *pBuf++;
	// 	ulTemp = *pBuf++;
	// 	ulTemp = *pBuf++;
	// 	ulTemp = *pBuf++;
	// 	ulTemp = *pBuf++;
	// 	ulTemp = *pBuf++;
	// 	ulTemp = *pBuf++;
	// 	ulTemp = *pBuf++;
		
	// 	ulTemp = *pBuf++;
	// 	ulTemp = *pBuf++;
	// 	ulTemp = *pBuf++;
	// 	ulTemp = *pBuf++;
	// 	ulTemp = *pBuf++;
	// 	ulTemp = *pBuf++;
	// 	ulTemp = *pBuf++;
	// 	ulTemp = *pBuf++;
		
	// 	ulTemp = *pBuf++;
	// 	ulTemp = *pBuf++;
	// 	ulTemp = *pBuf++;
	// 	ulTemp = *pBuf++;
	// 	ulTemp = *pBuf++;
	// 	ulTemp = *pBuf++;
	// 	ulTemp = *pBuf++;
	// 	ulTemp = *pBuf++;
	// }
	iTime2 = GET_TICK_MS();	/* 记下结束时间 */

	/* 打印速度 */
	DRV_LOG_INF("【32MB数据读耗时】: 方式一:%dms, 读速度: %dMB/s\r\n", 
	        iTime2 - iTime1,  (SDRAM_ADDR_LEN / 1024 /1024 * 1000) / (iTime2 - iTime1));
}
#endif