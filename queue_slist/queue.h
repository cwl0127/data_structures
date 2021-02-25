#ifndef _QUEUE_H
#define _QUEUE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define    KEY_MSG     (uint8_t)0x01         //按键消息类型
#define    UART1_MSG   (uint8_t)0x02         //串口1消息类型 
#define    UART2_MSG   (uint8_t)0x03         //串口2消息类型
#define    UART3_MSG   (uint8_t)0x04         //串口3消息类型
#define    INT0_MSG    (uint8_t)0x05         //外部中断0消息类型
#define    INT1_MSG    (uint8_t)0x06         //外部中断1消息类型
#define    LVD_MSG     (uint8_t)0x07         //低电压消息类型
#define    TIMER_MSG   (uint8_t)0x80         //定时器消息
#define    NONE_MSG    (uint8_t)0xFF         //空消息

typedef struct message
{
  uint8_t type;         /*消息类型*/
  uint16_t value;       /*消息值*/
} msg_t;

typedef msg_t queueElementT;
typedef struct queueCDT * queueADT;

queueADT newQueue(void);
void freeQueue(queueADT queue);
bool inQueue(queueADT queue, queueElementT value);
bool outQueue(queueADT queue, queueElementT *p_alue);
bool queueIsEmpty(queueADT queue);
bool queueIsFull(queueADT queue);
size_t getQueueLength(queueADT queue);

#endif
