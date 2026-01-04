# Build path
BARED_SERVICE_DIR = vendor/bared/service
COMMON_DIR = vendor/common

C_SOURCES += $(BARED_SERVICE_DIR)/nsh_service/nsh_service.c

C_INCLUDES  += -I$(COMMON_DIR)

