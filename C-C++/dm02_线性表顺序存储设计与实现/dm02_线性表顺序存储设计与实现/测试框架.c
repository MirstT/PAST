#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include"seqlist.h"

typedef struct Teacher
{
	int age;
	char name[64];
}Teacher;


void main()
{
	int ret = 0, i = 0;
	SeqList* list = NULL;

	Teacher t1,t2,t3,t4,t5;
	t1.age = 31;
	t2.age = 32;
	t3.age = 33;
	t4.age = 34;
	t5.age = 35;


	list = SeqList_Create(10);
	if (list == NULL)
	{
		printf("func SeqList_Create() ret:%d\n", ret);
		return;
	}

	ret = SeqList_Insert(list, (SeqListNode*)&t1, 0);
	ret = SeqList_Insert(list, (SeqListNode*)&t2, 0);
	ret = SeqList_Insert(list, (SeqListNode*)&t3, 0);
	ret = SeqList_Insert(list, (SeqListNode*)&t4, 0);
	ret = SeqList_Insert(list, (SeqListNode*)&t5, 0);

	//ret = SeqList_Insert(list, &t1, 0);
	//ret = SeqList_Insert(list, &t2, 0);
	//ret = SeqList_Insert(list, &t3, 0);
	//ret = SeqList_Insert(list, &t4, 0);
	//ret = SeqList_Insert(list, &t5, 0);


	for (i = 0; i < SeqList_Length(list); i++)
	{
		Teacher* tmp = (Teacher*)SeqList_Get(list, i);
		if (tmp == NULL)
		{
			return;
		}
		printf("tmp->age:%d", tmp->age);

	}

	while (SeqList_Length(list)>0)
	{
		SeqList_Delete(list, 0);
	}




	system("pause");
}


//typedef void SeqList;
//typedef void SeqListNode;
//
//SeqList* SeqList_Create(int capacity);
//
//void SeqList_Destroy(SeqList* list);
//
//void SeqList_Clear(SeqList* list);
//
//int SeqList_Length(SeqList* list);
//
//int SeqList_Capacity(SeqList* list);
//
//int SeqList_Insert(SeqList* list, SeqListNode* node, int pos);
//
//SeqListNode* SeqList_Get(SeqList* list, int pos);
//
//SeqListNode* SeqList_Delete(SeqList* list, int pos);