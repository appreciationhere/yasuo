#include "cli.h"
#include "system.h"
#include "tty.h"
#include "nsh_service.h"
#include "cli.h"

static cli_obj_t cli;                               /*命令行对象 */
/* 
 * @brief       命令行任务初始化
 * @return      none
 */ 
int do_cmd_sysinfo(struct cli_obj *o, int argc, char *argv[])
{
    syslog(LOG_INFO, "[sysinfo]argc:%d", argc);
    for (int i = 0; i < argc; ++i)
    {
        syslog(LOG_INFO, "[sysinfo]argv[%d]:%s", i, argv[i]);
    }
    return 0;
}cmd_register("sysinfo",do_cmd_sysinfo, "system infomation");

static void cli_task_init(void)
{
    cli_port_t p = {tty.write, tty.read};           /*读写接口 */

    cli_init(&cli, &p);                             /*初始化命令行对象 */
     
    cli_enable(&cli);
    
    cli_exec_cmd(&cli,"sysinfo");                   /*显示系统信息*/
}

/* 
 * @brief       命令行任务处理
 * @return      none
 */ 
static void cli_task_process(void)
{
    cli_process(&cli);
}

module_init("cli", cli_task_init);                  
task_register("cli", cli_task_process, 10);          /*注册命令行任务*/