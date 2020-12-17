#include<iostream>
using namespace std;

//异常是跨函数的
//接受异常后，可以不处理，继续向上抛出异常
//异常是按照类型进行catch

//异常捕捉严格按照类型匹配 不会进行隐式类型转换




void main()
{
	try
	{
		throw 'Z';
	}
	catch (int e)
	{
		cout << "捕获int类型异常" << endl;
	}
	catch (...)
	{
		cout << " 未知 类型异常" << endl;
	}

	system("pause");
}




void divide(int x, int y)
{
	if (y == 0)
	{
		throw x; //抛出 int 类型 异常
	}

	cout << "divide 结果:" << x/y << endl;

}


void myDivide(int x, int y)
{
	try
	{
		divide(x, y);
	}
	catch (...)
	{
		cout << "我接收了divide的异常，但我没有处理，我向上抛！" << endl;
		throw;
	}
}

void main21()
{
	try
	{
		//divide(10, 2);
		myDivide(100, 0);// 异常是跨函数的！！！！！！
	}

	catch (int e)
	{
		cout << e << "被零除" << endl;
	}
	catch (...)
	{
		cout << "其它未知类型异常" << endl;
	}



	system("pause");
}