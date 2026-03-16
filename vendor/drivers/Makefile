ifeq ($(CONFIG_SDRAM_W9825G6KH), y)
C_SOURCES += $(wildcard $(DRIVERS_DIR)/fmc/sdram_w9825g6kh.c)
endif
ifeq ($(CONFIG_UART_TTY), y)
C_SOURCES += $(wildcard $(DRIVERS_DIR)/tty/uart_tty.c)
endif
C_INCLUDES  += -I$(DRIVERS_DIR)/include
