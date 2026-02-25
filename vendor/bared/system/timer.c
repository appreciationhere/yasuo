#include "system.h"
#include "qlink.h"

#define MALLOC(s)               su_malloc(s)
#define FREE(s)                 su_free(s)
#define GET_TICK                get_tick     

struct timer_moudle_s
{
    struct qlink q;
};

static struct timer_moudle_s s_timer;

void timer_proc(void)
{
    struct qlink_node* pos = s_timer.q.front;
    uint32_t now_tick = GET_TICK();
    while (NULL != pos) {
        
    }
}

void* timer_creat(void)
{

}

int timer_start(void* timer, uint32_t first, uint32_t time)
{

}

int timer_again(void* timer)
{

}

int timer_stop(void* timer)
{

}
int timer_destroy(void* timer)
{

}