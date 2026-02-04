/******************************************************************************
 * @brief    tty串口打印驱动
 *
 * Copyright (c) 2020, <morro_luo@163.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs: 
 * Date           Author       Notes 
 * 2015-07-03     Morro
 ******************************************************************************/

#ifndef	_TTY_H_
#define	_TTY_H_

#define TTY_RXBUF_SIZE		 128
#define TTY_TXBUF_SIZE		 256

/*接口声明 --------------------------------------------------------------------*/
typedef struct {
    void (*init)(int instence);                                   
    unsigned int (*write)(const void *buf, unsigned int len);    
    unsigned int (*read)(void *buf, unsigned int len);           
    bool (*tx_isfull)(void);                                    /*发送缓冲区满*/
    bool (*rx_isempty)(void);                                   /*接收缓冲区空*/
}tty_t;

void tty_push_data(unsigned char* data, unsigned int len);

extern const tty_t tty;

#endif
