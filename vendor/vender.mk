# Build path
-include tools/.config

APPS_DIR 		= vendor/apps
COMMON_DIR 		= vendor/common
BOARD_DIR 		= vendor/frameworks/board
SYSTEM_DIR 		= vendor/frameworks/system
DRIVERS_DIR 	= vendor/drivers
COMPONENT_DIR 	= vendor/component
SERVICE_DIR 	= vendor/service

include $(wildcard $(APPS_DIR)/Make.defs)
include $(wildcard $(BOARD_DIR)/Make.defs)
include $(wildcard $(SYSTEM_DIR)/Make.defs)
include $(wildcard $(DRIVERS_DIR)/Make.defs)
include $(wildcard $(COMPONENT_DIR)/Make.defs)
include $(wildcard $(SERVICE_DIR)/Make.defs)

C_INCLUDES  += -I$(COMMON_DIR)


menuconfig:
	@echo "Running Python-based menuconfig..."
	@cd tools && python -m menuconfig Kconfig
	@cd tools && python kconfig.py
	@copy .\tools\config.h .\vendor\common\config.h

.DEFAULT_GOAL := all