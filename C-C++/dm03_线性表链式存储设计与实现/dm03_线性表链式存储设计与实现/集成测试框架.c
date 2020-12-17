#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include"linklist.h"

typedef struct Teacher
{
	LinkListNode	node;
	int				age;
	char			namep[64];
}Teacher;


void main()
{
	int len = 0, ret = 0;

	LinkList* list = NULL;
	LinkListNode* node = NULL;

	Teacher t1, t2, t3, t4, t5;

	list = LinkList_Create();
	if (list == NULL)
	{
		return;
	}

	len = LinkList_Length(list);

	ret = LinkList_Insert(list, (LinkListNode*)&t1,0);
	ret = LinkList_Insert(list, (LinkListNode*)&t2, 0);
	ret = LinkList_Insert(list, (LinkListNode*)&t3, 0);
	ret = LinkList_Insert(list, (LinkListNode*)&t4, 0);
	ret = LinkList_Insert(list, (LinkListNode*)&t5, 0);


	for (int i = 0; i < LinkList_Length(list); i++)
	{
		Teacher *tmp = (Teacher *)LinkList_Get(list, i);
		if (tmp == NULL)
		{
			return;
		}
		printf("tmp->age:%d\n", tmp->age);
	}

	while (LinkList_Length(list)>0)
	{
		LinkList_Delete(list, 0);
	}

	system("pause");

	return;
}