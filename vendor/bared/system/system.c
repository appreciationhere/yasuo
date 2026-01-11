#include "system.h"
#include "async_work.h"

static async_work_t system_async_work;
static work_node_t system_work_node[CONFIG_ASYNC_WORK_NOTES_MAX];
static sys_async_work_func_t work_cb[CONFIG_ASYNC_WORK_NOTES_MAX];

static void system_idle_process(void)
{
    static uint32_t cnt_s = 0;
    static uint32_t last_ticl = 0;
    if (get_tick() - last_ticl > 1000) {
        syslog(LOG_INFO, "now second: %lu", cnt_s);
        ++cnt_s;
        last_ticl = get_tick();
    }
}

void system_async_work_init(void)
{
    async_work_init(&system_async_work, system_work_node, CONFIG_ASYNC_WORK_NOTES_MAX);
}
bool system_async_work_add(void *object, void *params, sys_async_work_func_t work)
{
    // return async_work_add(&system_async_work, object, params, work);
    return 1;
}

void system_async_handle(void)
{
    async_work_process(&system_async_work);
}

void system_handle(void)
{
    module_task_process();
    system_idle_process();
}

system_init("init_async_work", system_async_work_init);

task_register("async_work", system_async_handle, 1);


