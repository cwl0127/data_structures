#include <stdio.h>
#include "queue.h"

int main(int argc, char *argv[])
{
	queueADT queue;
	int i;
	msg_t msg;

	queue = newQueue();
	for(i = 0; i < 16; i++) 
	{
		msg.type = (uint8_t)i;
		msg.value = 2 * i;
		inQueue(queue, msg);
	}
	printf("The length is %d\n", (int)getQueueLength(queue));
	while (!queueIsEmpty(queue)) 
	{
		outQueue(queue, &msg);
		printf("msg.type: %u\tmsg.value: %u\n", msg.type, msg.value);
	}
	freeQueue(queue);
	return 0;
}