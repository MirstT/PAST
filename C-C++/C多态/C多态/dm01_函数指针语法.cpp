
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main01()
{
	int a[10];  //a������Ԫ��   &a��������  a+1 =+4   &a+1 =+40 
	{
		//������������
		typedef int(myTypeArray)[10];
		myTypeArray myArray;

		myArray[0] = 10;
		printf("%d\n", myArray[0]);
	}


	{
		typedef int(*PTypeArray)[10];
		PTypeArray myPArray; 
		myPArray = &a;
		/*{int b = 10;
		int *p = NULL;
		p = &b; }*/
		(*myPArray)[0] = 20;
		printf("a[0]:%d\n", a[0]);

	}


	{
		int(*MyPointer)[10];
		MyPointer = &a;

		(*MyPointer)[0] = 40;
		printf("a[0]:%d\n", a[0]);
	}




	system("pause");
	return;
}


//����ָ��
//1 ���庯������
//2 ���庯��ָ������
//3 ���庯��ָ�루ָ��һ����������ڵ�ַ��

int add(int a, int b)
{
	printf("fuc add....\n");
	return a + b;
}

void main11()
{
	add(1, 2);  //ֱ�ӵ���  ���������Ǻ�������ڵ�ַ

	// ���庯������
	{
		typedef int(MyFuncType)(int a, int b);
		MyFuncType *myPointerFunc = NULL;

		myPointerFunc = &add;
		myPointerFunc(3, 4);//��ӵ���

		myPointerFunc = add;//ϸ�� C�������Ƶģ�������ʷ�汾......
		myPointerFunc(3, 4);

	}

	{
		//���庯��ָ������
		typedef int(*MyPointerFuncType)(int a, int b);
		MyPointerFuncType myPonterFun;
		myPonterFun = add;
		myPonterFun(3, 4);
	}


	{
		//����ָ��
		int(*MyPonjterFunc)(int a, int b);
		MyPonjterFunc = add;
		MyPonjterFunc(5, 6);

	}

	system("pause");
	return;

}