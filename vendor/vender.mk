# Build path
-include tools/.config

BARED_SERVICE_DIR = vendor/bared/service
BARED_SYSTEM_DIR = vendor/bared/system
BARED_DRIVER_DIR = vendor/bared/driver

COMMON_DIR = vendor/common
COMPONENT_DIR = vendor/component

C_SOURCES += $(wildcard $(BARED_SERVICE_DIR)/nsh_service/*.c)
C_SOURCES += $(wildcard $(BARED_SERVICE_DIR)/log_service/*.c)
ifeq ($(CONFIG_SYSLOG_PRINT_EN),y)
C_SOURCES += $(wildcard $(BARED_SYSTEM_DIR)/*.c)
endif
C_SOURCES += $(wildcard $(BARED_DRIVER_DIR)/**/*.c)
C_SOURCES += $(wildcard $(COMPONENT_DIR)/**/*.c)


C_INCLUDES  += -I$(COMMON_DIR)
C_INCLUDES  += -I$(COMPONENT_DIR)/mm
C_INCLUDES += -I$(BARED_SERVICE_DIR)/log_service
C_INCLUDES += -I$(BARED_SERVICE_DIR)/nsh_service
C_INCLUDES += -I$(BARED_SYSTEM_DIR)
C_INCLUDES += -I$(BARED_DRIVER_DIR)/inc


menuconfig:
	@echo "Running Python-based menuconfig..."
	@cd tools && python -m menuconfig Kconfig
	@cd tools && python kconfig.py
	@copy .\tools\config.h .\vendor\common\config.h

.DEFAULT_GOAL := all