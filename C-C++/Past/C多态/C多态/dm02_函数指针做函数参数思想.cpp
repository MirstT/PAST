#include<stdlib.h>
#include<stdio.h>
#include<string.h>


int myadd1(int a, int b) //�����ʵ����
{

	printf("func add()1 do...\n");
	return a + b;
}

int myadd2(int a, int b) //�����ʵ����
{

	printf("func add()2 do...\n");
	return a + b;
}

int myadd3(int a, int b) //�����ʵ����
{

	printf("func add()3 do...\n");
	return a + b;
}

int myadd4(int a, int b) //�����ʵ����
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
	int c = MyPointerFuncAdd(5, 6);//��ӵ���
	return c; 
}



// ����ĵ��úͱ�д���Էֿ���
void main()
{
	myadd1(1, 2);//ֱ�ӵ���

	MyTypeFuncAdd myFuncAdd = myadd1;
	myFuncAdd(3, 4);// ��ӵ���




	MainOp(myadd1);
	MainOp2(myadd1);//�������


	MainOp(myadd2);
	MainOp(myadd3);//��ܲ��䣬���ܱ䣡 ��̬�麯����������

	system("pause");
}


// ͨ������ָ���� ��������      �ص�����