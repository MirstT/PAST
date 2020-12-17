#include<iostream>
using namespace std;
#include"dm09_complex.h"


//构造函数的实现，写在类的外部
template <typename T>
Complex<T>::Complex(T a, T b)
{
	this->a = a;
	this->b = b;
}

template<typename T>
void Complex<T>::printCom()
{
	cout << a << "+" << b << "i" << endl;
}

template<typename T>
Complex<T> Complex<T>::operator+ (Complex<T> &c2)
{
	return Complex(a + c2.a, b + c2.b);
}


//友元函数实现
template<typename T>
ostream& operator<<(ostream &out, Complex<T> &c3)
{
	out << c3.a << "+" << c3.b << "i" << endl;
	return out;
}