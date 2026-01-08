#include "log_service.h"
#include "system.h"

void log_service_init(void)
{
    syslog(LOG_INFO, "log_service_init start ...");

    syslog(LOG_INFO, "log_service_init end");
}

module_init("log_service", log_service_init);

