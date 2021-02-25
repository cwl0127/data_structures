#ifndef _SLIST_H
#define _SLIST_H

typedef struct _slist_node
{
	struct _slist_node *p_next; /* 指向下一个结点的指针 */
}slist_node_t;

typedef slist_node_t slist_head_t;
typedef int (*slist_node_process_t)(void *p_arg, slist_node_t *p_node);

int slist_init(slist_head_t *p_head);
int slist_add(slist_head_t *p_head, slist_node_t *p_pos, slist_node_t *p_node);
int slist_add_tail(slist_head_t *p_head, slist_node_t *p_node);
int slist_add_head(slist_head_t *p_head, slist_node_t *p_node);
int slist_del(slist_head_t *p_head, slist_node_t *p_node);

slist_node_t *slist_prev_get(slist_head_t *p_head, slist_node_t *p_pos);
slist_node_t *slist_next_get(slist_head_t *p_head, slist_node_t *p_pos);
slist_node_t *slist_tail_get(slist_head_t *p_head);
slist_node_t *slist_begin_get(slist_head_t *p_head);
slist_node_t *slist_end_get (slist_head_t *p_head);
int slist_foreach(slist_head_t *p_head,
				  slist_node_process_t pfn_node_process,
				  void *p_arg);

#endif