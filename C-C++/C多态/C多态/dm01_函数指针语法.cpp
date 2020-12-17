
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main01()
{
	int a[10];  //a数组首元素   &a整个数组  a+1 =+4   &a+1 =+40 
	{
		//定义数组类型
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


//函数指针
//1 定义函数类型
//2 定义函数指针类型
//3 定义函数指针（指向一个函数的入口地址）

int add(int a, int b)
{
	printf("fuc add....\n");
	return a + b;
}

void main11()
{
	add(1, 2);  //直接调用  函数名就是函数的入口地址

	// 定义函数类型
	{
		typedef int(MyFuncType)(int a, int b);
		MyFuncType *myPointerFunc = NULL;

		myPointerFunc = &add;
		myPointerFunc(3, 4);//间接调用

		myPointerFunc = add;//细节 C是逐步完善的，兼容历史版本......
		myPointerFunc(3, 4);

	}

	{
		//定义函数指针类型
		typedef int(*MyPointerFuncType)(int a, int b);
		MyPointerFuncType myPonterFun;
		myPonterFun = add;
		myPonterFun(3, 4);
	}


	{
		//函数指针
		int(*MyPonjterFunc)(int a, int b);
		MyPonjterFunc = add;
		MyPonjterFunc(5, 6);

	}

	system("pause");
	return;

}