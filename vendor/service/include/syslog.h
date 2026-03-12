#ifndef _H_SYSLOG_H__
#define _H_SYSLOG_H__

#include "common.h"

#define LOG_ERROR     5
#define LOG_INFO      6
#define LOG_DEBUG     7


#define SYSTEM_LOG_TAG              "sys"
#define DRIVER_LOG_TAG              "drv"
#define HAL_LOG_TAG                 "hal"
#define APPLICATION_LOG_TAG         "appli"

void syslog(uint32_t level, const char *format, ...);
#endif // !_H_LOG_SERVICE_H__
