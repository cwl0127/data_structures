#include <stdio.h>
#include <stdlib.h>
#include "hash_db.h"

typedef struct _student
{
	char name[10];
	char sex;
	float height, weight;
} student_t;

int db_id_to_idx(unsigned char id[6]) //通过ID得到数组索引
{
	int i;
	int sum = 0;
	for (i = 0; i < 6; i++)
	{
		sum += id[0];
	}
	return sum % 250;
}

int student_info_generate(unsigned char *p_id, student_t *p_student)
{
	int i;
	for (i = 0; i < 6; i++) 
	{ //随机产生一个学号
		p_id[i] = rand();
	}
	for (i = 0; i < 9; i++) 
	{
		p_student->name[i] = (rand() % ('z' - 'a')) + 'a';
	}
	p_student->name[i]= '\0';
	p_student->sex = (rand() & 0x01) ? 'F' : 'M';
	p_student->height = (float)rand() / rand();
	p_student->weight = (float)rand() / rand();
	return 0;
}

int main(void)
{
	student_t stu;
	unsigned char id[6];
	int i;
	hash_db_t hash_students;

	hash_db_init(&hash_students, 250, 6, sizeof(student_t), (hash_func_t)db_id_to_idx);

	for(i = 0; i < 100; i++) 
	{    //添加100个学生信息
		student_info_generate(id, &stu); //设置学生的信息，当前一随机数作为测试 
		if (hash_db_search(&hash_students, id, &stu) == 0) 
		{ //查找到该ID已存在的学生记录
			printf("该ID的记录已存在！\n");
			continue;
		}
		printf("增加记录：ID : %02x%02x%02x%02x%02x%02x    ",id[0],id[1],id[2],id[3],id[4],id[5]);
		printf("ؑ信息：%s %c %.2f %.2f\n", stu.name, stu.sex, stu.height, stu.weight);
		if (hash_db_add(&hash_students, id, &stu) != 0) 
		{
			printf("添加失败");
		}
	}
	printf("查找ID为：%02x%02x%02x%02x%02x%02x的信息\n",id[0],id[1],id[2],id[3],id[4],id[5]);
	if (hash_db_search(&hash_students, id, &stu) == 0) 
	{
		printf("学生信息：%s %c %.2f %.2f\n", stu.name, stu.sex, stu.height, stu.weight);
	} 
	else 
	{
		printf("未找到该ID的记录\n");
	}
	hash_db_deinit(&hash_students);
	return 0;    
}