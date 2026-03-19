#ifndef _DRV_COM_H__
#define _DRV_COM_H__

#include "system.h"

#define DRV_DELAY_MS(n)            sys_msleep(n);

#define DRV_LOG_DBG(fmt, ...)      syslog(LOG_DEBUG, fmt, ##__VA_ARGS__)

#define DRV_LOG_INF(fmt, ...)      syslog(LOG_INFO, fmt, ##__VA_ARGS__)

#define DRV_LOG_ERR(fmt, ...)      syslog(LOG_ERR, fmt, ##__VA_ARGS__)

#define DRV_MALLOC                 su_malloc
#define DRV_FREE                   su_free

#endif // !_DRV_COM_H__