#ifndef  _H_SYSTEM1_H__
#define _H_SYSTEM1_H__

#include "module.h"
#include "syslog.h"
#include "cli.h"
#include "circbuf.h"
#include "qlink.h"

#define ASSERT(n) {if (0 == (n)){syslog(LOG_ERR,"assert at file %s:%s[%d]", __FILE__,\
                     __func__, __LINE__);while(1);}};


#define MALLOC(n)       su_malloc(n)    
#define FREE(n)         su_free(n)
#define GET_TICK_MS     get_tick

#define assert(n)       ASSERT(n)

typedef void (*sys_async_work_func_t)(void *params);

typedef void (*timer_func_t)(void *params);

typedef struct
{
    uint32_t            loop_time;
    uint32_t            timeout_tick;
    timer_func_t        timeout_func;
    unsigned char       tid;
    bool                activing;
    struct qlink_node   r_node;
    struct qlink_node   node;
} timer_item_t;

bool system_async_work_add(sys_async_work_func_t work, void *params);

void system_handler(void);
uint32_t sys_msleep(uint32_t ms);

/* mm manager */
int su_mm_init(void* start, void* end);
void* su_malloc(uint32_t size);
void su_free(void* note);

/* timer interface */
void timer_proc(void);
void* timer_creat(void);
int timer_start(void* timer, timer_func_t cb, uint32_t first, uint32_t time);
int timer_again(void* timer);
int timer_stop(void* timer);
int timer_destroy(void* timer);

#endif // ! _H_SYSTEM_H__

