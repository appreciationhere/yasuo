# Build path
BARED_SERVICE_DIR = vendor/bared/service
BARED_SYSTEM_DIR = vendor/bared/system
BARED_DRIVER_DIR = vendor/bared/driver

COMMON_DIR = vendor/common

C_SOURCES += $(wildcard $(BARED_SERVICE_DIR)/nsh_service/*.c)
C_SOURCES += $(wildcard $(BARED_SERVICE_DIR)/log_service/*.c)
C_SOURCES += $(wildcard $(BARED_SYSTEM_DIR)/*.c)
C_SOURCES += $(wildcard $(BARED_DRIVER_DIR)/**/*.c)


C_INCLUDES  += -I$(COMMON_DIR)
C_INCLUDES += -I$(BARED_SERVICE_DIR)/log_service
C_INCLUDES += -I$(BARED_SERVICE_DIR)/nsh_service
C_INCLUDES += -I$(BARED_SYSTEM_DIR)
C_INCLUDES += -I$(BARED_DRIVER_DIR)/inc
