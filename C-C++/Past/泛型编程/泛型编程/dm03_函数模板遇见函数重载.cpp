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
//
//
//void myswap(int a, char c)
//{
//	cout << "a:" << a << " c:" << c << endl;
//	cout << "hello.........普通函数" << endl;
//}
//
//
////显示类型调用
////自动类型推导
//
//void main()
//{
//
//	int		a = 10;
//	char	c = 'z';
//
//	myswap(a, c);//普通函数的调用：可以进行隐式的类型转换
//
//	myswap(c, a);
//
//	myswap(a, a);//调用函数模板（本质是类型参数化），将严格按照类型进行匹配，不会进行自动类型转换
//
//
//
//
//
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
