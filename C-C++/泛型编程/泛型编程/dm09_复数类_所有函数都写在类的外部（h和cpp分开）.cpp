//#include<iostream>
//using namespace std;
//
//template<typename T>
//class Complex;
//template<typename T>
//Complex<T> MySub(Compex<T>&c1, Complex<T>&c2);
//
//template<typename T>
//class Complex
//{
//
//	friend Complex MySub<T>(Complex<T> &c1, Complex<T> &c2);
//	friend ostream& operator<< <T>(ostream &out, Complex &c3);
//
//public:
//	Complex(T a, T b);
//
//	Complex operator+ (Complex &c2);
//
//	void printCom();
//protected:
//private:
//	T a;
//	T b;
//};
//
////���캯����ʵ�֣�д������ⲿ
//template <typename T>
//Complex<T>::Complex(T a, T b)
//{
//	this->a = a;
//	this->b = b;
//}
//
//template<typename T>
//void Complex<T>::printCom()
//{
//	cout << a << "+" << b << "i" << endl;
//}
//
//template<typename T>
//Complex<T> Complex<T>::operator+ (Complex<T> &c2)
//{
//	return Complex(a + c2.a, b + c2.b);
//}
//
//
////��Ԫ����ʵ��
//template<typename T>
//ostream& operator<<(ostream &out, Complex<T> &c3)
//{
//	out << c3.a << "+" << c3.b << "i" << endl;
//	return out;
//}
///////////////////////////////////////////////////////////////
//
////���� ��Ԫ����
//template <typename T>
//Complex<T> MySub(Complex<T> &c1, Complex<T> &c2)
//{
//	return Complex<T>(c1.a - c2.a, c1.b - c2.b);
//}
//
//int main()
//{
//	int ret = 0;
//	Complex<int> c1(1, 2);
//	Complex<int> c2(3, 4);
//	Complex<int> c3 = c1 + c2;
//	cout << c3 << endl;
//
//
//
//	//������Ԫ����
//	{
//		Complex<int>c4 = MySub<int>(c1, c2);
//
//		cout << c4 << endl;
//	}
//
//
//
//
//	system("pause");
//	return ret;
//}