#include <stdio.h>
#include "dlist.h"

typedef struct _dlist_int 
{
	dlist_node_t node; /* 包含链表结点 */
	int data; /* int类型数据 */
}dlist_int_t;

int list_node_process(void *p_arg, dlist_node_t *p_node)
{
	printf("%d ", ((dlist_int_t *)p_node)->data);
	return 0;
}

int main(void)
{
	dlist_head_t head; /* 定义链表头结点 */
	dlist_int_t node1, node2, node3;
	dlist_init(&head);

	node1.data = 1;
	dlist_add(&head, &head, &(node1.node));
	node2.data = 2;
	dlist_add(&head, &(node1.node), &(node2.node));
	node3.data = 3;
	dlist_add(&head, &(node2.node), &(node3.node));
	printf("Before delete node.\n");
	dlist_foreach(&head, list_node_process, NULL);
	dlist_del(&head, &(node2.node));
	printf("\nAfter delet node.\n");
	dlist_foreach(&head, list_node_process, NULL); /* 遍历链表，用户参数为NULL */
	return 0;
}