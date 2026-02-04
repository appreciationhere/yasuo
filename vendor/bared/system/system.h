#ifndef  _H_SYSTEM1_H__
#define _H_SYSTEM1_H__

#include "module.h"
#include "syslog.h"
#include "cli.h"

#define ASSERT(n) {if (0 == (n)){syslog(LOG_ERROR,"assert at file %s:%s[%d]", __FILE__,\
                     __func__, __LINE__);while(1);}};


typedef void (*sys_async_work_func_t)(void *params);

bool system_async_work_add(sys_async_work_func_t work, void *params);

void system_handler(void);

#endif // ! _H_SYSTEM_H__

