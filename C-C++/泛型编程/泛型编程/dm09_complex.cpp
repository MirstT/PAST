#include<iostream>
using namespace std;
#include"dm09_complex.h"


//���캯����ʵ�֣�д������ⲿ
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


//��Ԫ����ʵ��
template<typename T>
ostream& operator<<(ostream &out, Complex<T> &c3)
{
	out << c3.a << "+" << c3.b << "i" << endl;
	return out;
}