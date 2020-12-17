#include<iostream>
using namespace std;
#include"MyVector.cpp"




class Teacher
{
public:
	Teacher()
	{
		age = 33;
		strcpy(name,  "");
	}
	Teacher(char*name, int age)
	{
		this->age = age;
		strcpy(this->name, name);
	}

	void printT()
	{
		cout << name << "," << age << endl;
	}

private:
	int age;
	char name[32];
};



void main()
{
	Teacher t1("t1",31), t2("t2", 32), t3("t3", 33), t4("t4", 34);



	system("pause");
}



//void main()
//{
//	MyVector<char> myv1(10);
//	/*for (int i = 97; i < myv1.getlen(); i++)
//	{
//		myv1[i] = 97;
//		cout << myv1[i] << " ";
//	}
//	*/
//
//	myv1[0] = 'a';
//	myv1[1] = 'a';
//	myv1[2] = 'a';
//	myv1[3] = 'a';
//	cout << myv1;
//
//
//	system("pause");
//}


//int main()
//{
//	int ret = 0;
//
//	MyVector<int> myv1(10);
//
//	for (int i = 0; i < myv1.getlen(); i++)
//	{
//		myv1[i] = i + 1;
//		cout << myv1[i] << " ";
//	}
//	cout << endl;
//
//
//
//	MyVector<int> myv2 = myv1;
//	for (int i = 0; i < myv2.getlen(); i++)
//	{
//		cout << myv2[i] << " ";
//	}
//	cout << endl;
//
//
//	system("pause");
//	return ret;
//
//}
