#include <fmc/fmc_com.h>
#include <board_com.h>
#include "fmc.h"

/* fmc ops */
static int fmc_transfer(struct fmc_dev_s *dev,
                        struct fmc_msg_s *msgs, int count);
int fmc_refresh(struct fmc_dev_s *dev, uint32_t RefreshRate);

const struct fmc_ops_s fmc_ops = {
    .refresh = fmc_refresh,
    .transfer = fmc_transfer
};

static struct fmc_dev_s bsp_fmc0_priv = {
    .ops = &fmc_ops
};

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

// HAL_SDRAM_ProgramRefreshRate(&hsdram1, 2480);


static int fmc_transfer(struct fmc_dev_s *dev,
                        struct fmc_msg_s *msgs, int count)
{
    int ret = 0;
    if (dev != &bsp_fmc0_priv)
    {
        ret = -1;
        return ret;
    }
    for (int i = 0; i < count; ++i)
    {
        ret = SDRAM_SendCommand(msgs[i].CommandMode, msgs[i].Bank, msgs[i].RefreshNum, msgs[i].RegVal);
        if (ret != 0)
        {
            return -ret;
        }
    }
    return ret;
}

int fmc_refresh(struct fmc_dev_s *dev, uint32_t RefreshRate)
{
    int ret = 0;
    if (dev != &bsp_fmc0_priv)
    {
        ret = -1;
        return ret;
    }
    ret = HAL_SDRAM_ProgramRefreshRate(&hsdram1, RefreshRate);
    return -ret;
}

void* bsp_board_fmc_init(int instance)
{
    void* ret = NULL;
    switch (instance)
    {
    case 0:
        ret = &bsp_fmc0_priv;
        break;
    default:
        break;
    }
    return ret;
}