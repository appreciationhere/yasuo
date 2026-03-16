#include "system.h"
#include "qlink.h"

#define GET_TICK                get_tick     
#define GET_TID                 module_get_task_id
#define PRINT_DEBUG(fmt,...)    syslog(LOG_INFO, ##__VA_ARGS__)

struct timer_moudle_s
{
    struct qlink q_ready;
    struct qlink q_alive;
};

static struct timer_moudle_s s_timer;

void timer_proc(void)
{
    struct qlink_node* pos = qlink_peek(&s_timer.q_ready);
    uint32_t now_tick = GET_TICK();
    while (NULL != pos) {
        timer_item_t* item = container_of(pos, timer_item_t, r_node);
        now_tick = GET_TICK();
        if (item->timeout_tick > now_tick) {
            break;
        }
        item->timeout_func(item);
        pos = qlink_get(&s_timer.q_ready);
        if (item->loop_time > 0)
            timer_start(item, item->timeout_func, item->loop_time, item->loop_time);
        pos = qlink_peek(&s_timer.q_ready);
    }
}

void* timer_creat(void)
{
    timer_item_t* item = MALLOC(sizeof(timer_item_t));
    memset(item, 0, sizeof(*item));
    item->tid = GET_TID();
    qlink_put(&s_timer.q_alive, &item->node);
    return item;
}

int timer_start(void* timer, timer_func_t cb, uint32_t first, uint32_t time)
{
    int ret = 0;
    timer_item_t* item = (timer_item_t*)timer;
    item->timeout_func = cb;
    item->loop_time = time;
    item->activing = true;
    item->timeout_tick = GET_TICK() + first;
    struct qlink_node* pos = qlink_peek(&s_timer.q_ready);
    struct qlink_node* prev_pos = NULL;
    while (NULL != pos) {
        timer_item_t* head = container_of(pos, timer_item_t, r_node);
        if (head->timeout_tick > item->timeout_tick) {
            break;
        }
        prev_pos = pos;
        pos = pos->next;
    }
    qlink_insert(&s_timer.q_ready, prev_pos, &item->r_node);
    return ret;
}

int timer_again(void* timer)
{
    int ret = 0;
    timer_item_t* item = (timer_item_t*)timer;
    timer_stop(item);
    timer_start(item, item->timeout_func, item->loop_time, item->loop_time);
    return ret;
}

int timer_stop(void* timer)
{
    int ret = 0;
    timer_item_t* item = (timer_item_t*)timer;
    qlink_remove(&s_timer.q_ready, &item->r_node);
    return ret;
}
int timer_destroy(void* timer)
{
    int ret = 0;
    timer_item_t* item = (timer_item_t*)timer;
    timer_stop(timer);
    qlink_remove(&s_timer.q_alive, &item->node);
    FREE(timer);
    return ret;
}
void timer_dump(void)
{
    PRINT_DEBUG("%s start ...", __func__);
}