#include "system.h"
#include "log_service.h"

static void log_service_init(void)
{
    syslog(LOG_INFO, "log_service_init start ...");

    syslog(LOG_INFO, "log_service_init end");
}

module_init("log_service", log_service_init);

