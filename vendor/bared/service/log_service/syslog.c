#include "syslog.h"
#include <stdarg.h>
#ifdef CONFIG_SYSLOG_PRINT_USART
#include "usart.h"
#endif
void syslog(uint32_t level, const char *format, ...)
{
    char buffer[CONFIG_SYSLOG_PRINT_BUFFER_SIZE];
    va_list args;

    va_start(args, format);
    
    int len = vsnprintf(buffer, sizeof(buffer), format, args);
    
    va_end(args);
    
    if (len > 0 && len < (int)sizeof(buffer))
    {
        #ifdef CONFIG_SYSLOG_PRINT_EN
        #ifdef CONFIG_SYSLOG_PRINT_USART
            usart_print_send(buffer, len);
        #endif
        #endif
    }
}
