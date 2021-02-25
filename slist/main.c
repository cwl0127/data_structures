#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "slist.h"

typedef struct _student
{
	char name[10];
	char sex;
	float height, weight;
}student_t;

typedef struct _slist_student
{
	slist_node_t node;
	student_t student;
}slist_student_t;

int student_info_read (student_t *p_student) /* 读取学生记录，随机产生，仅供测试 */
{
	int i;

	for (i = 0; i < 9; i++) 
	{ /* 随机名字，由'A'~'Z'组成 */
		p_student->name[i] = (rand() % ('z' - 'a')) + 'a';
	}
	p_student->name[i]= '\0';
	p_student->sex = (rand() & 0x01) ? 'F' : 'M'; /* 随机性别 */
	p_student->height = (float)rand() / rand();
	p_student->weight = (float)rand() / rand();
	return 0;
}

int list_node_process (void *p_arg, slist_node_t *p_node)
{
	student_t *p_s = &(((slist_student_t *)p_node)->student);
	printf("%s : %c %.2f %.2f\n", p_s->name, p_s->sex, p_s->height, p_s->weight);
	return 0;
}

int main(int argc, char *argv[])
{
	slist_head_t head;
	slist_student_t s1, s2, s3, s4, s5;
	srand(time(NULL));
	slist_init(&head);

	student_info_read(&s1.student);
	student_info_read(&s2.student);
	student_info_read(&s3.student);
	student_info_read(&s4.student);
	student_info_read(&s5.student);

	slist_add_head(&head, &s1.node);
	slist_add_head(&head, &s2.node);
	slist_add_head(&head, &s3.node);
	slist_add_head(&head, &s4.node);
	slist_add_head(&head, &s5.node);

	slist_foreach(&head, list_node_process, NULL); // 䙽শ䬮㺘ˈ⭘ᡧ৲ᮠѪ NULL
	return 0;
}
