// out_of_range
#include "iostream"
using namespace std;
#include <stdexcept>  
//
//class Teacher
//{
//public:
//	Teacher(int age)  //���캯��, ͨ���쳣���� �������
//	{
//		if (age > 100)
//		{
//			throw out_of_range("����̫��");
//		}
//		this->age = age;
//	}
//protected:
//private:
//	int age;
//};
//
//void main()
//{
//	try
//	{
//		Teacher t1(102);
//	}
//	catch (out_of_range e)
//	{
//
//		cout << e.what() << endl;
//	}
//
//	exception e;
//	system("pause");
//}

//
//class Dog
//{
//public:
//	Dog()
//	{
//		parr = new int[1024 * 1024 * 100]; //4MB
//	}
//private:
//	int *parr;
//};
//
//int main()
//{
//	Dog *pDog;
//	try {
//		for (int i = 1; i<1024; i++) //40GB!
//		{
//			pDog = new Dog();
//			cout << i << ": new Dog �ɹ�." << endl;
//		}
//	}
//	catch (bad_alloc err)
//	{
//		cout << "new Dog ʧ��: " << err.what() << endl;
//	}
//
//	return 0;
//
//}
