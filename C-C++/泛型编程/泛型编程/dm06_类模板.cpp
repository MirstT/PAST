//#include<iostream>
//using namespace std;
//
//
//
//template<typename T>
//class A
//{
//public:
//	A(T a,T b=0)
//	{
//		this->a = a;
//		this->b =b;
//	}
//
//	void printA()
//	{
//		cout << "a:" << a << endl;
//	}
//protected:
//	T a;
//	T b;
//
//};
//
//
////子模版派生时，需要具体化模板类。C++编译器需要知道父类的数据类型具体是什么样子的
////========》要知道弗雷所占的内存大小是多少
//class B :public A<int>
//{
//public:
//	B(int a = 10, int b = 20) :A<int>(a)
//	{
//		this->b = b;
//	}
//	void printB()
//	{
//		cout << "a:" << a << " b:" << b << endl;
//	}
//
//protected:
//
//private:
//	int b;
//
//};
//
//template<typename T>
//class C :public A<T>
//{
//public:
//	C(T c, T a) :A<T>(a)
//	{
//		this->c = c;
//	}
//
//	void printC()
//	{
//		cout << "c:" << c << endl;
//	}
//
//protected:
//	T c;
//
//};
//
//
//
//void UseA(A<int> &a)//<int> 必须写，需要分配内存
//{
//	a.printA();
//}
//
//
//
//int main()
//{
//	C<int> c1(1, 2);
//	c1.printC();
//
//
//	cout <<endl<< "====================================================" << endl;
//	B b1;
//	b1.printB();
//	b1.printA();
//
//	//模板类（本身就是类型化的）====具体的的类=====定义具体的变量
//
//	A<int> a1(1),a2(23),a3(5555555);//模板是抽象的，需要进行类型具体
//	a1.printA();
//
//	UseA(a1);
//	UseA(a2);
//	UseA(a3);
//
//
//	system("pause");
//	return 0;
//}