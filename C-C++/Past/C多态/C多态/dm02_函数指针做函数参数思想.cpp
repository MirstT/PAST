#include<stdlib.h>
#include<stdio.h>
#include<string.h>


int myadd1(int a, int b) //任务的实现者
{

	printf("func add()1 do...\n");
	return a + b;
}

int myadd2(int a, int b) //任务的实现者
{

	printf("func add()2 do...\n");
	return a + b;
}

int myadd3(int a, int b) //任务的实现者
{

	printf("func add()3 do...\n");
	return a + b;
}

int myadd4(int a, int b) //任务的实现者
{

	printf("func add()4 do...\n");
	return a + b;
}

typedef int(*MyTypeFuncAdd)(int a, int b);




int MainOp(MyTypeFuncAdd myFuncAdd)
{
	myFuncAdd(5, 6);
	return 0;
}

int MainOp2(int(*MyPointerFuncAdd)(int a, int b))
{
	int c = MyPointerFuncAdd(5, 6);//间接调用
	return c; 
}



// 任务的调用和编写可以分开！
void main()
{
	myadd1(1, 2);//直接调用

	MyTypeFuncAdd myFuncAdd = myadd1;
	myFuncAdd(3, 4);// 间接调用




	MainOp(myadd1);
	MainOp2(myadd1);//任务调用


	MainOp(myadd2);
	MainOp(myadd3);//框架不变，功能变！ 多态虚函数表！！！！

	system("pause");
}


// 通过函数指针做 函数参数      回调函数