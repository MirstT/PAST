//#include<stdlib.h>
//#include<stdio.h>
//#include<string.h>
//
//typedef struct Node
//{
//	int		data;
//	struct	Node *next;
//}SLIST;
//
//SLIST *Creat_SList();
//int SList_Print(SLIST*pHead);
//int Slist_NodeInsert(SLIST*pHead, int x, int y);
//int SList_NodeDel(SLIST*pHead, int y);
//int Slist_Destory(SLIST*pHead);
//
//SLIST *Creat_SList()
//{
//	int data = 0;
//	SLIST *pHead = NULL, *pM = NULL, *pCur;
//	pHead = (SLIST*)malloc(sizeof(SLIST));
//	pHead->data = 0;
//	pHead->next = NULL;
//
//	printf("\n Please enter the data of node(-1;quit)");
//	scanf_s("%d", &data);
//
//	pCur = pHead;
//	while (data!=-1)
//	{
//		pM = (SLIST*)malloc(sizeof(SLIST));
//		pM->data = data;
//		pM->next = NULL;
//
//		pCur->next = pM;
//
//		printf("\n Please enter the data of node(-1:quit)");
//		scanf_s("%d", data);
//	}
//	return pHead;
//}
//
//int SList_Print(SLIST *pHead)
//{
//	SLIST *p = NULL;
//
//	if (pHead == NULL)
//	{
//		return -1;
//	}
//	p = pHead->next;
//	printf("\nBegin:");
//	while (p)
//	{
//		printf("%d", p->data);
//		p = p->next;
//	}
//	printf("End ");
//	return 0;
//}
//
//int Slist_NodeInsert(SLIST *pHead, int x, int y)
//{
//	SLIST *pCur = NULL, *pPre = NULL, *pM = NULL;
//	if (pHead == NULL)
//	{
//		return -1;
//	}
//
//	pPre = pHead;
//	pCur = pHead->next;
//
//	pM = (SLIST*)malloc(sizeof(SLIST));
//	pM->data = y;
//	pM->next = NULL;
//
//	while (pCur)
//	{
//		if (pCur->data == x)
//		{
//			break;
//		}
//		pPre = pCur;
//		pCur = pCur->next;
//	}
//
//	pM->next = pPre->next;//pCur
//	pPre->next = pM;
//
//	return 0;
//}
//
//int SList_NodeDel(SLIST *pHead, int y)
//{
//	SLIST *pCur = NULL, *pPre = NULL;
//	if (pHead == NULL)
//	{
//		return -1;
//	}
//
//	pPre = pHead;
//	pCur = pHead->next;
//
//	while (pCur)
//	{
//		if (pCur->data == y)
//		{
//			break;
//		}
//
//		pPre = pCur;
//		pCur = pCur->next;
//	}
//
//	if (pCur == NULL)
//	{
//		printf("没有找到节点 y:%d", y);
//		return -2;
//	}
//
//	pPre->next = pCur->next;
//	free(pCur);
//	return 0;
//}
//
//int Slist_Destory(SLIST *pHead)
//{
//	SLIST *pTmp = NULL;
//	SLIST *pCur = pHead;
//	if (pHead == NULL)
//	{
//		return-1;
//	}
//
//	while (pCur)
//	{
//
//		pTmp = pCur->next;
//		free(pCur);
//		pCur = pTmp;
//	}
//	return 0;
//}
//
//void main()
//{
//	int ret = 0;
//	SLIST *pHead = NULL;
//
//	pHead = Creat_SList();
//	ret = SList_Print(pHead);
//
//	ret = Slist_NodeInsert(pHead, 20, 19);
//	ret = SList_Print(pHead);
//
//	ret = SList_NodeDel(pHead, 19);
//	ret = SList_Print(pHead);
//
//	ret = Slist_Destory(pHead);
//	system("pause");
//}
