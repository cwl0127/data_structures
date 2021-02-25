#include <stdio.h>
#include <string.h>
#include "queue.h"

int main(int argc, char* argv[])
{
	Queue* queue = queue_new();
	if (queue == NULL) {
		printf("Creat queue failed.\n");
		return 0;
	}
	for (int i = 1; i < argc; ++i)
	{
		queue_push_head(queue, argv[i], strlen(argv[i])+1);//字符串结尾的'/0'需要计入长度
	}
	
	while(!queue_is_empty(queue)) 
	{
		char buf[100];
		if (queue_pop_tail(queue,buf,sizeof(buf)) == 1) 
		{
			printf("%s\n",buf);
		}
	}
	
	printf("%s\n",queue_is_empty(queue)?"Now queue is empty.":"Queue is not empty.");
	for (int i = 0; i < 100; ++i)
	{
		queue_push_head(queue, &i,sizeof(i));
	}
	while(!queue_is_empty(queue)) 
	{
		int getval;
		if (queue_pop_tail(queue,&getval,sizeof(int)) == 1) 
		{
			printf("%d ",getval);
		}
	}
	return 0; 
}