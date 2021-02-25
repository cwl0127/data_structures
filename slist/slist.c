#include "slist.h"
#include <stdlib.h>

int slist_init(slist_head_t *p_head)
{
	if (p_head == NULL)
	{
		return -1;
	}
	p_head->p_next = NULL;
	return 0;
}

int slist_add(slist_head_t *p_head, slist_node_t *p_pos, slist_node_t *p_node)
{
	p_node->p_next = p_pos->p_next;
	p_pos->p_next = p_node;
	return 0;
}

int slist_add_tail(slist_head_t *p_head, slist_node_t *p_node)
{
	slist_node_t *p_tmp = slist_tail_get(p_head); /* 找到尾结点 */
	return slist_add(p_head, p_tmp, p_node); /* 添加结点至尾结点之后 */
}

int slist_add_head(slist_head_t *p_head, slist_node_t *p_node)
{
	return slist_add(p_head, p_head, p_node); /* 添加结点至头结点之后 */
}

int slist_del(slist_head_t *p_head, slist_node_t *p_node)
{
	slist_node_t *p_prev = slist_prev_get(p_head, p_node); /* 找到待删除结点的上一个结点 */
	if (p_prev) 
	{
		p_prev->p_next = p_node->p_next;
		p_node->p_next = NULL;
		return 0;
	}
	return -1;
}

slist_node_t *slist_prev_get(slist_head_t *p_head, slist_node_t *p_pos)
{
	slist_node_t *p_tmp = p_head;
	while ((p_tmp != NULL) && (p_tmp->p_next != p_pos))
	{
		p_tmp = p_tmp->p_next;
	}
	return p_tmp;    
}

slist_node_t *slist_next_get(slist_head_t *p_head, slist_node_t *p_pos)
{
	if (p_pos) 
	{
		return p_pos->p_next;
	}
	return NULL;
}

slist_node_t *slist_tail_get(slist_head_t *p_head)
{
	return slist_prev_get(p_head, NULL);
}

slist_node_t *slist_begin_get(slist_head_t *p_head)
{
	return slist_next_get(p_head, p_head);
}

slist_node_t *slist_end_get (slist_head_t *p_head)
{
	return NULL;
}

int slist_foreach(slist_head_t *p_head,
				  slist_node_process_t pfn_node_process,
				  void *p_arg)
{
	slist_node_t *p_tmp, *p_end;
	int ret;

	if ((p_head == NULL) || (pfn_node_process == NULL))
	{
		return -1;
	}
	p_tmp = slist_begin_get(p_head);
	p_end = slist_end_get(p_head);
	while (p_tmp != p_end)
	{
		ret = pfn_node_process(p_arg, p_tmp);
		if (ret < 0) 
			return ret; /* 不再继续遍历 */
		p_tmp = slist_next_get(p_head, p_tmp); /* 继续下一个结点 */
	}
	return 0;
}


