#include "hash_db.h"
#include <stdlib.h>
#include <string.h>

/* 寻找结点的上下文，仅内部使用 */
struct _node_find_ctx 
{
	const void *key; //查找关键字
	unsigned int key_len; //关键字长度
	slist_node_t *p_result; //用于存储查找到的结点
};

/**
 * @brief 遍历链表的回调函数，查找指定结点
 */
static int __hash_db_node_find (void *p_arg, slist_node_t *p_node)
{
	struct _node_find_ctx *p_info = (struct _node_find_ctx *)p_arg; //用户参数为寻找结点的上下文
	char *p_mem = (char *)p_node + sizeof(slist_node_t); //关键字存储在结点之后

	if (memcmp(p_mem, p_info->key, p_info->key_len) == 0) 
	{
		p_info->p_result = p_node;
		return -1; //找到该结点，终止遍历
	}
	return 0;
}


/**
 * @brief 哈希表初始化
 */
int hash_db_init(hash_db_t *p_hash, 
				 unsigned int size,
				 unsigned int key_len,
				 unsigned int value_len,
				 hash_func_t pfn_hash)
{
	int i;
	if ((p_hash == NULL) || (pfn_hash == NULL))
	{
		return -1;
	}
	p_hash->p_head = (slist_head_t *)malloc(size * sizeof(slist_head_t));
	if (p_hash->p_head == NULL) 
	{
		return -1;
	}
	for (i = 0; i < size; i++)
	{
		slist_init(&p_hash->p_head[i]);
	}
	p_hash->size = size;
	p_hash->key_len = key_len;
	p_hash->value_len = value_len;
	p_hash->pfn_hash = pfn_hash;
	return 0;
}

int hash_db_add(hash_db_t *p_hash, const void *key, const void *value)
{
	int idx = p_hash -> pfn_hash(key); //使用哈希函数通过关键字得到哈希值
	/* 分配内存，存储链表结点+关键字+记录 */
	char *p_mem = (char *)malloc(sizeof(slist_node_t) + p_hash -> key_len + p_hash -> value_len);
	if (p_mem == NULL)
	{
		return -1;
	}
	memcpy(p_mem + sizeof(slist_node_t), key, p_hash -> key_len); //存储关键字
	memcpy(p_mem + sizeof(slist_node_t) + p_hash->key_len, value, p_hash->value_len); //存储记录
	return slist_add_head(&p_hash -> p_head[idx], (slist_node_t *)p_mem); //将结点加入链表
}

int hash_db_del(hash_db_t *p_hash, const void *key)
{
	int idx = p_hash->pfn_hash(key); //得到关键字对应哈希表的索引
	struct _node_find_ctx info = {key, p_hash->key_len, NULL}; //设置遍历链表的上下文信息
	slist_foreach(&p_hash->p_head[idx], __hash_db_node_find, &info); //遍历，寻找关键字对应的结点
	if (info.p_result != NULL) 
	{
		slist_del(&p_hash->p_head[idx], info.p_result); //从链表中删除该结点
		free(info.p_result); //释放结点空间
		return 0;
	}
	return -1;
}

int hash_db_search(hash_db_t *p_hash, const void *key, void *value)
{
	int idx = p_hash->pfn_hash(key); ////得到关键字对应哈希表的索引
	struct _node_find_ctx info = {key, p_hash->key_len, NULL}; //设置遍历链表的上下文信息
	slist_foreach(&p_hash->p_head[idx], __hash_db_node_find, &info); //遍历，寻找关键字对应的结点

	if (info.p_result != NULL) 
	{   //找到对应结点，将存储的记录值拷贝到用户提供的空间中
		memcpy(value, (char *)info.p_result+sizeof(slist_node_t)+p_hash->key_len, p_hash->value_len);
		return 0;
	}
	return -1;
}

int hash_db_deinit(hash_db_t *p_hash)
{
	int i;
	slist_node_t *p_node;
	for (i = 0; i < p_hash->size; i++) 
	{ //释放哈希表中各个表项中存储的所有结点

		while (slist_begin_get(&p_hash->p_head[i]) != slist_end_get(&p_hash->p_head[i])) 
		{
			p_node = slist_begin_get(&p_hash->p_head[i]);
			slist_del(&p_hash->p_head[i], p_node); //释放第一个结点
			free(p_node);
		}
	}
	free(p_hash->p_head); //释放链表头结点数组空间
	return 0;
}