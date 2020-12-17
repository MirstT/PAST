#include<stdio.h>
#include<malloc.h>
#include"circlelist.h"

typedef struct Value
{
	CircleListNode header;
	int v;
}Value;

void main()
{
	int i = 0;
	CircleList* list = CircleList_Create();

	Value v1, v2, v3, v4, v5, v6, v7, v8;
	v1.v = 1; v2.v = 2; v3.v = 3; v4.v = 4;
	v5.v = 5; v6.v = 6; v7.v = 7; v8.v = 8;

	CircleList_Insert(list, (CircleListNode*)&v1, CircleList_Length(list));
	CircleList_Insert(list, (CircleListNode*)&v2, CircleList_Length(list));
	CircleList_Insert(list, (CircleListNode*)&v3, CircleList_Length(list));
	CircleList_Insert(list, (CircleListNode*)&v4, CircleList_Length(list));
	CircleList_Insert(list, (CircleListNode*)&v5, CircleList_Length(list));
	CircleList_Insert(list, (CircleListNode*)&v6, CircleList_Length(list));
	CircleList_Insert(list, (CircleListNode*)&v7, CircleList_Length(list));
	CircleList_Insert(list, (CircleListNode*)&v8, CircleList_Length(list));


	for ( i = 0; i < CircleList_Length(list); i++)
	{

		Value *pv = (Value*)CircleList_Next(list);
		printf("%d\n", pv->v);
	}


	printf("\n");

	CircleList_Reset(list);
	while (CircleList_Length(list)>0)
	{

		Value*pv = NULL;
		for ( i = 1; i < 3; i++)
		{
			CircleList_Next(list);
		}
		pv = (Value*)CircleList_Current(list);
		printf("%d\n", pv->v);
		CircleList_DeleteNode(list, (CircleListNode*)pv);
	}

	CircleList_Destory(list);
	return;

}


