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
////��ģ������ʱ����Ҫ���廯ģ���ࡣC++��������Ҫ֪��������������;�����ʲô���ӵ�
////========��Ҫ֪��������ռ���ڴ��С�Ƕ���
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
//void UseA(A<int> &a)//<int> ����д����Ҫ�����ڴ�
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
//	//ģ���ࣨ����������ͻ��ģ�====����ĵ���=====�������ı���
//
//	A<int> a1(1),a2(23),a3(5555555);//ģ���ǳ���ģ���Ҫ�������;���
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