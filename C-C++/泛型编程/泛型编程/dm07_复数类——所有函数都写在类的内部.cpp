//#include<iostream>
//using namespace std;
//
//template<typename T>
//class Complex
//{
//
//	friend Complex MySub(Complex &c1, Complex &c2)
//	{
//		return Complex(c1.a - c2.a, c1.b - c2.b);
//	}
//
//
//
//	friend ostream& operator<<(ostream &out, Complex &c3)
//	{
//		out << c3.a << "+" << c3.b <<"i"<< endl;
//		return out;
//	}
//public:
//	Complex(T a , T b )
//	{
//		this->a = a;
//		this->b = b;
//	}
//
//	Complex operator+ (Complex &c2)
//	{
//		return Complex (a + c2.a, b + c2.b);
//	}
//
//	void printCom()
//	{
//		cout << a << "+" << b <<"i"<< endl;
//	}
//protected:
//private:
//	T a;
//	T b;
//};
//
//// ����<< >> ֻ������Ԫ��������������������ض�Ҫд�ɳ�Ա���������� ��Ҫ������Ԫ����������
////ostream& operator<<(ostream &out, Complex &c3)
////{
////	out << "a:" << c3.a << " b:" << c3.b << endl;
////	return out;
////}
//
//
//int main()
//{
//	int ret = 0;
//	Complex<int> c1(1, 2);
//	Complex<int> c2(3, 4);
//
//	Complex<int> c3 = c1 + c2;
//
//	cout << c3 << endl;
//
//
//	//������Ԫ����
//	{
//		Complex<int>c4 = MySub(c1, c2);
//
//		cout << c4 << endl;
//	}
//
//	system("pause");
//	return ret;
//}