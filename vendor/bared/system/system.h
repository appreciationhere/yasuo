#ifndef  _H_SYSTEM1_H__
#define _H_SYSTEM1_H__

#include "module.h"
#include "syslog.h"
#include "async_work.h"

#define ASSERT(n) {if (0 == n){syslog("assert at file %s:%s[%d]", __FILE__,\
                     __func__, __LINE__);while(1);}};

#endif // ! _H_SYSTEM_H__

