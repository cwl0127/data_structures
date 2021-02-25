#include <stdio.h>
#include "queue.h"

int main(int argc, char *argv[])
{
	queueADT queue;
	int temp, i;

	queue = newQueue();
	for(i = 0; i < 16; i++) 
	{
		inQueue(queue, i);
	}
	printf("The length is %d\n", (int)getQueueLength(queue));
	while (!queueIsEmpty(queue)) 
	{
		outQueue(queue, &temp);
		printf("%d ", temp);
	}
	freeQueue(queue);
	return 0;
}