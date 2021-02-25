#include "queue.h"
#include <stdlib.h>
#include "slist.h"

#define MAXQSIZE 100
struct queueCDT 
{
	slist_head_t list_head; /* 链表头结点 */
	slist_node_t *p_rear; /* 指向队列的尾结点 */
};

typedef struct _queue_node_t
{
	slist_node_t node;
	queueElementT data;
} queue_node_t;

queueADT newQueue(void)
{
	queueADT queue;
	queue = (queueADT)malloc(sizeof(struct queueCDT));
	slist_init(&queue->list_head);
	queue->p_rear = &(queue->list_head);
	return queue;
}

void freeQueue(queueADT queue)
{
	while (!queueIsEmpty(queue))
	{
		slist_node_t *p_node = slist_begin_get(&queue -> list_head);
		slist_del(&queue -> list_head, p_node);
		free((queue_node_t *)p_node);
	}
	free(queue);
}

bool inQueue(queueADT queue, queueElementT value)
{
	if(queueIsFull(queue)) 
	{
		return false;
	}
	queue_node_t *p_node = (queue_node_t *)malloc(sizeof(queue_node_t));
	p_node -> data = value;
	slist_add(&queue->list_head, queue->p_rear,&(p_node->node));
	queue->p_rear = queue->p_rear->p_next;
	return true;
}

bool outQueue(queueADT queue, queueElementT *p_value)
{
	if(queueIsEmpty(queue)) 
	{
		return false;
	}
	slist_node_t *p_node = slist_begin_get(&queue -> list_head);
	*p_value = ((queue_node_t *)p_node) -> data;
	slist_del(&queue -> list_head, p_node);
	free(p_node);
	return true;
}

bool queueIsEmpty(queueADT queue)
{
	return (slist_begin_get(&queue -> list_head) == slist_end_get(&queue -> list_head));
}

bool queueIsFull(queueADT queue)
{
	/* 链队列不会满 */
	return false;
}

static int _numElems_node(void *p_arg, slist_node_t *p_node)
{
	(*(size_t *)p_arg)++;
	return 0;
}

size_t getQueueLength(queueADT queue)
{
	size_t count = 0;
	slist_foreach(&queue->list_head, _numElems_node, &count);
	return count;
}
