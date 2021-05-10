#include <stdio.h>
#include <string.h>
#include "queue.h"

int main(void)
{
	Queue* queue = queue_new();
	if (queue == NULL) {
		printf("Creat queue failed.\n");
		return 0;
	}
	printf("queue size: %u\r\n", queue_size(queue));
	queue_push_head(queue, "www.", strlen("www.") + 1);
	printf("queue size: %u\r\n", queue_size(queue));
	queue_push_head(queue, "sensertek.", strlen("sensertek.") + 1);
	printf("queue size: %u\r\n", queue_size(queue));
	queue_push_head(queue, "com", strlen("com") + 1);
	printf("queue size: %u\r\n", queue_size(queue));
	
	while(!queue_is_empty(queue)) {
		char buf[100];
		if (queue_pop_head(queue,buf,sizeof(buf)) == 1) {
			printf("%s\n",buf);
			printf("queue size: %u\r\n", queue_size(queue));
		}
	}
	
	return 0; 
}