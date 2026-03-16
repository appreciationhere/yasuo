#include "system.h"
#include "cli.h"
#include <fmc_com.h>
int do_cmd_sdram_test(struct cli_obj *o, int argc, char *argv[])
{
    if (argc < 2)
    {
        syslog(LOG_ERROR, "please input two argv sdram_test r or w !!!");
        return -1;
    }
    if ('r' == argv[1][0])
    {
        syslog(LOG_INFO, "ReadSpeedTest start...");
        ReadSpeedTest();
    }
    else if ('w' == argv[1][0])
    {
        syslog(LOG_INFO, "WriteSpeedTest start...");
        WriteSpeedTest();
    }
    
    return 0;
}
cmd_register("sdram_test", do_cmd_sdram_test, "sdram_test r or w");

