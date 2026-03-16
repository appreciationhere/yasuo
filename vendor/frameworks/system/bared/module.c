#include "system.h"

static void nop_process(void);

struct task_moudle_s    g_task_moudle;

#define GET_TICK                  get_tick     
#define INF(format, ...)          syslog(LOG_INFO, format, ##__VA_ARGS__)     

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
    const task_item_t *t;
    unsigned char i = 0;

    extern int board_init_pre(void);
    board_init_pre();
    
    INF("module_task_init start ...");
    while (it < &init_tbl_end) {
        INF("module_task_init name:%s", it->name);
        it++->init();
    }
    for (t = &task_tbl_start + 1; t < &task_tbl_end; ++t) {
        ++g_task_moudle.tid_num;
    }
    g_task_moudle.head = su_malloc(g_task_moudle.tid_num * sizeof(struct task_node_s));
    for (t = &task_tbl_start + 1, i = 0; t < &task_tbl_end; ++t, ++i) {
        g_task_moudle.head[i].runTime = 0;
        g_task_moudle.head[i].task = t;
        g_task_moudle.head[i].tid = i;
        g_task_moudle.head[i].status = TASK_STATUS_READY;
    }
    INF("module_task_init end");

    extern int board_init_final(void);
    board_init_final();
}

/*
 * @brief       任务轮询处理
 * @param[in]   none
 * @return      none
 */
void module_task_process(void)
{
    const task_item_t *t;
    unsigned char i = 0;
    for (i = 0, t = &task_tbl_start + 1; t < &task_tbl_end; ++t, ++i) {
        if  ((get_tick() - *t->timer) >= t->interval && 
                TASK_STATUS_READY == g_task_moudle.head[i].status) {
            g_task_moudle.startTime = get_tick();
            g_task_moudle.tid = i;
            g_task_moudle.head[i].status = TASK_STATUS_RUN;
            t->handle();
            *t->timer = get_tick();
            g_task_moudle.head[i].runTime += get_tick() - g_task_moudle.startTime;
            g_task_moudle.head[i].status = TASK_STATUS_READY;
        }
    }
}

void module_task_status_change(unsigned char tid, unsigned char status) 
{
    g_task_moudle.head[tid].status = status;
}

struct task_node_s* module_get_task_node(unsigned char tid)
{
    return &g_task_moudle.head[tid];
}

unsigned char module_get_task_id(void)
{
    return g_task_moudle.tid;
}