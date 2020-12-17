#pragma once
#include<iostream>
using namespace std;

template<typename T>
class Complex
{
	//friend Complex MySub<T>(Complex<T> &c1, Complex<T> &c2);
	friend ostream& operator<< <T>(ostream &out, Complex &c3);
public:
	Complex(T a, T b);
	void printCom();
	Complex operator+ (Complex &c2);
protected:
private:
	T a;
	T b;
};