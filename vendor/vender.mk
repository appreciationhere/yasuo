# Build path
BARED_SERVICE_DIR = vendor/bared/service
BARED_SYSTEM_DIR = vendor/bared/system

COMMON_DIR = vendor/common

C_SOURCES += $(BARED_SERVICE_DIR)/nsh_service/nsh_service.c
C_SOURCES += $(BARED_SERVICE_DIR)/log_service/syslog.c
C_SOURCES += $(BARED_SERVICE_DIR)/log_service/log_service.c

C_SOURCES += $(wildcard $(BARED_SERVICE_DIR)/nsh_service/*.c)
C_SOURCES += $(wildcard $(BARED_SERVICE_DIR)/log_service/*.c)
C_SOURCES += $(wildcard $(BARED_SYSTEM_DIR)/*.c)


C_INCLUDES  += -I$(COMMON_DIR)
C_INCLUDES += -I$(BARED_SERVICE_DIR)/log_service
C_INCLUDES += -I$(BARED_SYSTEM_DIR)
