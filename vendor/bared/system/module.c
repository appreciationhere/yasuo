#include "module.h"
#include "syslog.h"

static void nop_process(void);

task_item_t*            g_p_task_item;
unsigned char           g_task_num_all;

//第一个初始化�?
const init_item_t init_tbl_start SECTION("init.item.0") = {
    "", nop_process
};
//最后个初始化项
const init_item_t init_tbl_end SECTION("init.item.4") = {
    "", nop_process
};

//第一个任务项
const task_item_t task_tbl_start SECTION("task.item.0") = {
    "", nop_process
};
//最后个任务�?
const task_item_t task_tbl_end SECTION("task.item.2") = {
    "", nop_process
};

/*
 * @brief       空处�?,用于定位段入�?
 */
static void nop_process(void) {}

static volatile unsigned int tick;               //系统滴答计时

/*
 * @brief   增加系统节拍�?(定时器中断中调用,1ms 1�?)
 */
void systick_increase(unsigned int ms)
{
	tick += ms;
}

/*
 * @brief       获取系统滴答时钟�?(通常单位�?1ms)
 */
unsigned int get_tick(void)
{
	return tick;
}

/*
 * @brief       超时判断
 * @param[in]   start   - 起始时间
 * @param[in]   timeout - 超时时间(ms)
 */
bool is_timeout(unsigned int start, unsigned int timeout)
{
    return get_tick() - start > timeout;
}

/*
 * @brief       模块初始处理
 *              初始化模块优化级 system_init > driver_init > module_init
 * @param[in]   none
 * @return      none
 */
void module_task_init(void)
{
    const init_item_t *it = &init_tbl_start;
    syslog(LOG_INFO, "module_task_init start ...");
    while (it < &init_tbl_end) {
        syslog(LOG_INFO, "module_task_init name:%s", it->name);
        it++->init();
    }
    syslog(LOG_INFO, "module_task_init end");
}

/*
 * @brief       任务轮询处理
 * @param[in]   none
 * @return      none
 */
void module_task_process(void)
{
    const task_item_t *t;
    for (t = &task_tbl_start + 1; t < &task_tbl_end; t++) {
        g_p_task_item = t;
        if  ((get_tick() - *t->timer) >= t->interval) {
            *t->timer = get_tick();
            t->handle();
        }
    }
}

task_item_t* module_get_task_item(void)
{
    return g_p_task_item;
}