#include <stdio.h>
#include "iterator.h"

typedef int element_type_t;

static void __array_iterator_next(iterator_t *p_iter) //让迭代器指向容器的下一个数据
{
	(*(element_type_t **)p_iter)++;
}

static void __array_iterator_prev(iterator_t *p_iter) //让迭代器指向容器的上一个数据
{
	(*(element_type_t **)p_iter)--;
}

static int __visit(void *p_arg, iterator_t it)
{
	printf("%d ", *(int *)it);
	return 0;
}

static int __compare(iterator_t it1, iterator_t it2)
{
	return *(int *)it1 - *(int *)it2;
}

static void __swap(iterator_t it1, iterator_t it2)
{
	int data = *(int *)it2;
	*(int *)it2 = *(int *)it1;
	*(int *)it1 = data;
}

int main(void)
{
	iterator_if_t iterator_if;
	int a[5] = {5, 4, 3, 2, 1};
		
	iterator_if_init(&iterator_if, __array_iterator_next, __array_iterator_prev);

	printf("\nBefore bubble sort:\n");
	iter_foreach(&iterator_if, a, a+5, __visit, NULL);
	iter_sort(&iterator_if, a, a+5, __compare, __swap);

	printf("\nAfter bubble sort:\n");
	iter_foreach(&iterator_if,a, a+5, __visit, NULL);

	return 0;
}