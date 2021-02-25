#ifndef _HASH_DB_H
#define _HASH_DB_H

#include "slist.h"

typedef unsigned int (*hash_func_t) (const void *key); //哈希函数类型，返回值为整数，参数为关键字
struct _hash_db
{
	slist_head_t *p_head;   //指向数组首地址
	unsigned int size;      //数组成员数
	unsigned int value_len; //一条记录的长度
	unsigned int key_len;   //关键字的长度
	hash_func_t pfn_hash;   //哈希函数
};
typedef struct _hash_db hash_db_t; //指向哈希表对象的指针类型

int hash_db_init(hash_db_t *p_hash, //哈希表初始化
unsigned int size,
unsigned int key_len,
unsigned int value_len,
hash_func_t pfn_hash);

int hash_db_add(hash_db_t *p_hash, const void *key,const void *value); //添加记录
int hash_db_del(hash_db_t *p_hash, const void *key); //删除记录
int hash_db_search(hash_db_t *p_hash, const void *key, void *value); //查找记录
int hash_db_deinit(hash_db_t *p_hash); //解初始化

#endif