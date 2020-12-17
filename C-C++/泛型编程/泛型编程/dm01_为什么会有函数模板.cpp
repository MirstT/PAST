//#include<iostream>
//using namespace std;
//
//
//
////函数逻辑一样，参数不一样！
//void myswap1(int &a, int &b)
//{
//	int c = 0;
//	c = a;
//	a = b;
//	b = c;
//
//}
//void myswap2(char &a, char &b)
//{
//	char c = 0;
//	c = a;
//	a = b;
//	b = c;
//
//}
//
//
////泛型编程
////template 开始泛型编程
//template <typename T>
//void myswap(T &a, T&b)
//{
//	T c;
//	c = a;
//	a = b;
//	b = c;
//	cout << "hello.......函数模板" << endl;
//}
//
////显示类型调用
////自动类型推导
//
//void main()
//{
//
//	{
//		int x = 10;
//		int y = 20;
//
//
//		//myswap<int>(x, y);  //显示类型调用
//		myswap(x, y);  //自动类型推导
//
//		printf("x:%d y:%d\n", x, y);
//
//
//	}
//
//	{
//		char a = 'a';
//		char b = 'b';
//
//		//myswap<char>(a, b);  //显示类型调用
//		myswap(a, b);  //自动类型推导
//
//		printf("a:%c b:%c\n", a, b);
//
//
//	}
//
//	system("pause");
//}
//
//
//
//
//void main11()
//{
//
//	{
//		int x = 10;
//		int y = 20;
//
//		myswap1(x, y);
//		printf("x:%d y:%d\n", x, y);
//	}
//
//	{
//		char a = 'a';
//		char b = 'b';
//
//		myswap2(a, b);
//		printf("a:%c b:%c\n", a, b);
//	}
//
//
//	system("pause");
//}
//
//
//
