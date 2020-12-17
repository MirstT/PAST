#include<iostream>
using namespace std;

#include"vector"
#include"algorithm"

void main11()
{
	vector<int> v1; //ÈÝÆ÷
	v1.push_back(1);
	v1.push_back(3);
	v1.push_back(5);
	v1.push_back(3);


	for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++) //µü´úÆ÷
	{
		cout << *it << " ";
	}

	//Ëã·¨
	int num1=count(v1.begin(), v1.end(), 3);
	cout << "num1:" << num1 << endl;

}

class Teacher
{
public:
	int age;
	char name[64];
public:
	void printT()
	{
		cout << "age:" << age << endl;
	}
};


void main12()
{



	Teacher t1, t2, t3;
	t1.age = 31;
	t2.age = 32;
	t3.age = 33;

	vector<Teacher> v1; //ÈÝÆ÷
	v1.push_back(t1);
	v1.push_back(t2);
	v1.push_back(t3);



	for (vector<Teacher>::iterator it = v1.begin(); it != v1.end(); it++) //µü´úÆ÷
	{
		cout << it->age << " ";
	}

	//Ëã·¨
	/*int num1 = count(v1.begin(), v1.end(), 3);
	cout << "num1:" << num1 << endl;
*/
}




void main13()
{



	Teacher t1, t2, t3;
	t1.age = 31;
	t2.age = 32;
	t3.age = 33;
	Teacher *p1, *p2, *p3;
	p1 = &t1;
	p2 = &t1;
	p3 = &t3;

	vector<Teacher *> v1; //ÈÝÆ÷
	v1.push_back(p1);
	v1.push_back(p2);
	v1.push_back(p3);



	for (vector<Teacher *>::iterator it = v1.begin(); it != v1.end(); it++) //µü´úÆ÷
	{
		cout << (*it)->age << " ";
	}

	//Ëã·¨
	/*int num1 = count(v1.begin(), v1.end(), 3);
	cout << "num1:" << num1 << endl;
	*/
}
void main()
{
	//mian11();
	//main12();
	main13();

	system("pause");
}