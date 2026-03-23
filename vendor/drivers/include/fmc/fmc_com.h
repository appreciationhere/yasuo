#ifndef _FMC_COM_H__
#define _FMC_COM_H__

#include <common.h>

struct fmc_dev_s;

struct fmc_msg_s
{
    uint32_t CommandMode;
    uint32_t Bank;
    uint32_t RefreshNum;
    uint32_t RegVal;
};
/* This structure contains the full state of FMC as needed for a specific
 * transfer.  It is passed to FMC methods so that FMC transfer may be
 * performed in a thread safe manner.
 */
struct fmc_ops_s
{
    int (*transfer)(struct fmc_dev_s *dev,
                        struct fmc_msg_s *msgs, int count);
    int (*refresh)(struct fmc_dev_s *dev, uint32_t RefreshRate);
};

struct fmc_dev_s
{
    const struct fmc_ops_s* ops; /* FMC vtable */
};



#endif // !_FMC_COM_H__
