# Build path
-include tools/.config

BOARD_DIR 		= vendor/frameworks/board
SYSTEM_DIR 		= vendor/frameworks/system
DRIVERS_DIR 	= vendor/drivers
COMPONENT_DIR 	= vendor/component
SERVICE_DIR 	= vendor/service

include $(wildcard $(BOARD_DIR)/Make.defs)
include $(wildcard $(SYSTEM_DIR)/Make.defs)
include $(wildcard $(DRIVERS_DIR)/Make.defs)
include $(wildcard $(COMPONENT_DIR)/Make.defs)
include $(wildcard $(SERVICE_DIR)/Make.defs)


C_SOURCES += $(wildcard $(BARED_SERVICE_DIR)/nsh_service/*.c)
C_SOURCES += $(wildcard $(BARED_SERVICE_DIR)/log_service/*.c)
ifeq ($(CONFIG_SYSLOG_PRINT_EN),y)
C_SOURCES += $(wildcard $(BARED_SYSTEM_DIR)/*.c)
endif
C_SOURCES += $(wildcard $(BARED_DRIVER_DIR)/**/*.c)
C_SOURCES += $(wildcard $(COMPONENT_DIR)/**/*.c)


C_INCLUDES  += -I$(COMPONENT_DIR)/mm
C_INCLUDES += -I$(BARED_SERVICE_DIR)/log_service
C_INCLUDES += -I$(BARED_SERVICE_DIR)/nsh_service
C_INCLUDES += -I$(BARED_SYSTEM_DIR)
C_INCLUDES += -I$(BARED_DRIVER_DIR)/inc


menuconfig:
	@echo "Running Python-based menuconfig..."
	@cd tools && python -m menuconfig Kconfig
	@cd tools && python kconfig.py
	@copy .\tools\config.h .\vendor\frameworks\include\common\config.h

.DEFAULT_GOAL := all