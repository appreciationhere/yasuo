#ifndef _BOARD_APT_PI_H
#define _BOARD_APT_PI_H


#define GPIO_LED_BLUE_PORT        GPIOI
#define GPIO_LED_BLUE_PIN         GPIO_PIN_8

#define GPIO_LED_RED_PORT        GPIOC
#define GPIO_LED_RED_PIN         GPIO_PIN_15

#define SDRAM_ADDR_SART         ((uint32_t)0XC0000000)
#define SDRAM_ADDR_LEN          (32*0X400*0X400)

#endif // !_BOARD_APT_PI_H