#include "queue.h"
#include <stdlib.h>

#define MAXQSIZE 100
struct queueCDT
{
	queueElementT *data;
	int front;
	int rear;
};

queueADT newQueue(void)
{
	queueADT queue;
	queue = (queueADT)malloc(sizeof(struct queueCDT));
	queue->data = (queueElementT *)malloc(MAXQSIZE * sizeof(queueElementT));
	queue->front = 0;
	queue->rear = 0;
	return queue;
}

void freeQueue(queueADT queue)
{
	free(queue->data);
	free(queue);
}

bool inQueue(queueADT queue, queueElementT value)
{
	if (queueIsFull(queue))
	{
		return false;
	}
	queue->data[queue->rear] = value;
	queue->rear = (queue->rear + 1) % MAXQSIZE;
	return true;
}

bool outQueue(queueADT queue, queueElementT *p_value)
{
	if (queueIsEmpty(queue))
	{
		return false;
	}
	*p_value = queue->data[queue->front];
	queue->front = (queue->front + 1) % MAXQSIZE;
	return true;
}

bool queueIsEmpty(queueADT queue)
{
	return (queue->rear == queue->front);
}

bool queueIsFull(queueADT queue)
{
	return ((queue->rear + 1) % MAXQSIZE == queue->front);
}

size_t getQueueLength(queueADT queue)
{
	return (queue->rear - queue->front + MAXQSIZE) % MAXQSIZE;
}
