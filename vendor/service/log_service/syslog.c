#include "syslog.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#ifdef CONFIG_SYSLOG_PRINT_USART
#include "usart.h"
#endif
#include "system.h"
void syslog(uint32_t level, const char *format, ...)
{
    char buffer[CONFIG_SYSLOG_PRINT_BUFFER_SIZE + 2];
    va_list args;

    va_start(args, format);
    
    int len = vsnprintf(buffer, sizeof(buffer), format, args);
    ASSERT(len <= CONFIG_SYSLOG_PRINT_BUFFER_SIZE);
    memcpy(buffer+len, "\r\n", 2);
    len += 2;
    va_end(args);

    if (len > 0 && len < (int)sizeof(buffer))
    {
        #ifdef CONFIG_SYSLOG_PRINT_EN
        #ifdef CONFIG_SYSLOG_PRINT_USART
            usart_print_send((uint8_t*)buffer, len);
        #endif
        #endif
    }
}
