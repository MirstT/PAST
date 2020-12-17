#include<stdio.h>
#include<malloc.h>
#include"dlinklist.h"

typedef struct _tag_DLinkList
{
	DLinkListNode header;
	DLinkListNode* slider;
	int length;
}TDLinkList;

DLinkList* DLinkList_Create()
{
	TDLinkList* ret = (TDLinkList*)malloc(sizeof(TDLinkList));
	if (ret == NULL)
	{
		return NULL;
	}

	ret->length = 0;
	ret->header.next = NULL;
	ret->slider = NULL;
	return ret;

}

void DLinkList_Destory(DLinkList* list)
{
	if (list == NULL)
	{
		return;
	}
	free(list);
}

void DLinkList_Clear(DLinkList* list)
{
	TDLinkList* sList = (TDLinkList*)list;
	if (sList == NULL)
	{
		return;
	}
	sList->length = 0;
	sList->header.next = NULL;
	sList->header.pre = NULL;
	sList->slider = NULL;

}

int DLinkList_Length(DLinkList* list)
{
	TDLinkList* sList = (TDLinkList*)list;
	int ret = -1;

	if (sList == NULL)
	{
		return ret;
	}
	ret = sList->length;
	return ret;
}

int DLinkList_Insert(DLinkList* list, DLinkListNode* node, int pos)
{
	int ret = 0, i = 0;
	TDLinkList* sList = (TDLinkList*)list;

	if (list == NULL || node == NULL || pos < 0)
	{
		return -1;
	}


	DLinkListNode* currernt = (DLinkListNode*)sList;
	DLinkListNode* next = NULL;

	//DLinkListNode* currernt = (DLinkListNode*)&(sList->header);
	for (i = 0; (i < pos) && (currernt->next != NULL); i++)
	{
		currernt = currernt->next;
	}
	next = currernt->next;

	node->next = currernt->next;
	currernt->next = node;


	if (next != NULL)
	{
		next->pre = node;
	}
	node->pre = currernt;

	if (sList->length == 0)
	{
		sList->slider = node;
	}

	sList->length++;

	if (currernt == (DLinkListNode*)sList)
	{
		node->pre = NULL;
	}
	return ret;
}

DLinkListNode* DLinkList_Get(DLinkList* list, int pos)
{
	TDLinkList* sList = (TDLinkList *)list;
	DLinkListNode* ret = 0;
	int i = 0;

	if (list == NULL || pos < 0)
	{
		return NULL;
	}

	if ((sList != NULL) && (pos >= 0) && (sList->length >= 0))
	{
		DLinkListNode * current = (DLinkListNode*)sList;

		for (i = 0; i < pos; i++)
		{
			current = current->next;
		}
		ret = current->next;


	}

	return ret;

}

DLinkListNode* DLinkList_Delete(DLinkList* list, int pos)
{
	TDLinkList* sList = (TDLinkList*)list;
	DLinkListNode* ret = NULL;
	int i = 0;

	if ((sList != NULL) && (pos >= 0) && (sList->length > 0))
	{
		DLinkListNode* current = (DLinkListNode*)sList;
		DLinkListNode* next = NULL;

		for (i = 0; i < pos; i++)
		{
			current = current->next;
		}

		//if (current == (DLinkListNode*)sList)
		//{
		//	last = (DLinkListNode*)DLinkList_Get(sList, sList->length - 1);
		//}
		ret = current->next;
		next = ret->next;



		current->next = next;

		if (next != NULL)
		{
			next->pre = current;

			if (current == (DLinkListNode*)sList)
			{
				next->pre = NULL;
			}
		}

		sList->length--;


		if (sList->slider == ret)
		{
			sList->slider = ret->next;
		}

		if (sList->length == 0)
		{
			sList->header.next = NULL;
			sList->slider = NULL;
		}
	}


	return ret;
}

//add
DLinkListNode* DLinkList_DeleteNode(DLinkList* list, DLinkListNode* node)
{
	TDLinkList*sList = (TDLinkList*)list;
	DLinkListNode*ret = NULL;
	int i = 0;

	if (sList != NULL)
	{
		DLinkListNode* current = (DLinkListNode*)sList;

		for (i = 0; i < sList->length; i++)
		{
			if (current->next == node)
			{
				ret = current->next;
				break;
			}
			current = current->next;
		}

		if (ret != NULL)
		{
			DLinkList_Delete(sList, i);
		}

	}
	return ret;
}


DLinkListNode* DLinkList_Reset(DLinkList* list)
{
	TDLinkList* sList = (TDLinkList*)list;
	DLinkListNode* ret = NULL;

	if (sList != NULL)
	{
		sList->slider = sList->header.next;
		ret = sList->slider;
	}

	return ret;
}

DLinkListNode* DLinkList_Current(DLinkList* list)
{
	TDLinkList* sList = (TDLinkList*)list;
	DLinkListNode* ret = NULL;

	if (sList != NULL)
	{
		ret = sList->slider;
	}
	return ret;
}

DLinkListNode* DLinkList_Next(DLinkList* list)
{
	TDLinkList* sList = (TDLinkList*)list;
	DLinkListNode*ret = NULL;

	if ((sList != NULL) && (sList->slider != NULL))
	{
		ret = sList->slider;
		sList->slider = ret->next;
	}

	return ret;
}


DLinkListNode* DLinkList_Pre(DLinkList* list)
{
	TDLinkList* sList = (TDLinkList*)list;
	DLinkListNode*ret = NULL;

	if ((sList != NULL) && (sList->slider != NULL))
	{
		ret = sList->slider;
		sList->slider = ret->pre;
	}

	return ret;
}

