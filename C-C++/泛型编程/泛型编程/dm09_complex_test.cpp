#include<iostream>
using namespace std;
#include"dm09_complex.cpp"



int main()
{
	int ret = 0;


	Complex<int> c1(1, 2);
	Complex<int> c2(3, 4);
	Complex<int> c3 = c1 + c2;
	cout << c3 << endl;

	system("pause");
	return ret;

}