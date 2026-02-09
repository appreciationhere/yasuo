#include "system.h"
#include "async_work.h"
#include "tty.h"
#include "tlsf.h"

struct sys_async_work_data_t
{
    async_work_t system_async_work;
    work_node_t system_work_node[CONFIG_ASYNC_WORK_NOTES_MAX];
};

static struct sys_async_work_data_t sys_async_work;
static cli_obj_t cli;                               /*命令行对象 */
static tlsf_t tlfs_sys;

static void system_async_work_cb(async_work_t *w, void *object, void *params)
{
    sys_async_work_func_t cb = (sys_async_work_func_t)object;
    if (cb) {
        cb(params);
    }
}
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
    async_work_init(&sys_async_work.system_async_work, sys_async_work.system_work_node,\
                    CONFIG_ASYNC_WORK_NOTES_MAX);
}
bool system_async_work_add(sys_async_work_func_t work, void *params)
{
    bool ret = 0;
    ret = async_work_add(&sys_async_work.system_async_work, (void*)work, params, system_async_work_cb);
    ASSERT(ret);     
    return ret;
}

void system_async_handle(void)
{
    async_work_process(&sys_async_work.system_async_work);
}

void system_mm_init(void)
{
    su_mm_init(&Image$$RW_RAM$$ZI$$Limit, );
}

int su_mm_init(void* start, void* end)
{
    int ret = 0;
    tlfs_sys = tlsf_create_with_pool(start, (uint32_t)start - (uint32_t)end);
    ASSERT(tlfs_sys);
    return ret;
}

void* su_malloc(uint32_t size)
{
    return tlsf_malloc(&tlfs_sys, size);}

void su_free(void* note)
{
    tlsf_free(&tlfs_sys, note);
}

void system_handler(void)
{
    module_task_process();
    system_idle_process();
}

void bsp_init(void)
{
    tty.init(0);
}

driver_init("bsp_init", bsp_init);

system_init("init_async_work", system_async_work_init);
system_init("init_mm", system_mm_init);

task_register("async_work", system_async_handle, 1);
