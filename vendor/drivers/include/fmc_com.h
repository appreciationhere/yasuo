#ifndef _FMC_H__
#define _FMC_H__

#include <common.h>

struct fmc_dev_s
{
    const struct fmc_ops_s* ops; /* FMC vtable */
};

struct fmc_msg_s
{
    uint32_t CommandMode;
    uint32_t Bank;
    uint32_t RefreshNum;
    uint32_t RegVal;
};

/* This structure contains the full state of I2C as needed for a specific
 * transfer.  It is passed to I2C methods so that I2C transfer may be
 * performed in a thread safe manner.
 */
struct fmc_ops_s
{
    int (*transfer)(struct fmc_dev_s *dev,
                        struct fmc_msg_s *msgs, int count);
    int (*refresh)(struct fmc_dev_s *dev, uint32_t RefreshRate);
};

#ifdef CONFIG_SDRAM_W9825G6KH
#include <fmc/sdram_w9825g6kh.h>
#endif // CONFIG_SDRAM_W9825G6KH

#endif // !_FMC_H__
