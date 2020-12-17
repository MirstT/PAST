#include<iostream>
using namespace std;
#include<set>
#include<functional>
void main91()
{
	set<int> set1;

	for (int i = 0; i < 5; i++)
	{
		int tmp = rand();
		set1.insert(tmp);
	}

	set1.insert(100);
	set1.insert(100);
	set1.insert(100);


	for (set<int>::iterator it = set1.begin(); it != set1.end(); it++)
	{
		cout << *it << " ";
	}


	cout << endl;
	while (!set1.empty())
	{
		set<int>::iterator it = set1.begin();
		cout << *it << " ";
		set1.erase(set1.begin());
	}
}


void main92()
{
	set<int> set1;
	set<int, less<int>> set2;
	set<int, greater<int>> set3;

	for (int i = 0; i < 5; i++)
	{
		int tmp = rand();
		set3.insert(tmp);
	}

	for (set<int, greater<int>>::iterator it = set3.begin(); it != set3.end(); it++)
	{
		cout << *it << endl;
	}
}


class Student
{
public:
	Student(char * name, int age)
	{
		strcpy_s(this->name, 32, name);
		this->age = age;
	}
public:
	char name[32];
	int age;
};


struct FuncStudent
{
	bool operator()(const Student&left, const Student&right)
	{
		if (left.age < right.age)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};


void main93()
{
	set<Student,FuncStudent> set1;
	Student s1((char*)"s1", 31);
	Student s2((char*)"s2", 21);
	Student s3((char*)"s3", 41);
	Student s4((char*)"s4", 11);
	Student s5((char*)"s5", 31);


	set1.insert(s1);
	set1.insert(s2);
	set1.insert(s3);
	set1.insert(s4);

	for (set<Student, FuncStudent>::iterator it = set1.begin(); it != set1.end(); it++)
	{
		cout << it->age << "\t" << it->name << endl;
	}
}
void main94()
{
	Student s1((char*)"s1", 31);
	Student s2((char*)"s2", 21);
	Student s3((char*)"s3", 41);
	Student s4((char*)"s4", 11);
	Student s5((char*)"s5", 31);

	set<Student, FuncStudent> set1;
	
	pair<set<Student, FuncStudent>::iterator, bool> pair1 = set1.insert(s1);
	if (pair1.second == true)
	{
		cout << "插入s1成功" << endl;
	}
	else
	{
		cout << "插入s2失败" << endl;
	}

	set1.insert(s2);
	pair<set<Student, FuncStudent>::iterator, bool> pair5 = set1.insert(s5);
	if (pair5.second == true)
	{
		cout << "插入s1成功" << endl;
	}
	else
	{
		cout << "插入s2失败" << endl;
	}


	for (set<Student, FuncStudent>::iterator it = set1.begin(); it != set1.end(); it++)
	{
		cout << it->age << "\t" << it->name << endl;
	}
}

void main95()
{
	set<int> set1;
	for (int i = 0; i < 10; i++)
	{
		set1.insert(i + 1);
	}

	for (set<int>::iterator it = set1.begin(); it != set1.end(); it++)
	{
		cout << *it << endl;
	}
	cout << endl;


	set<int>::iterator it0 = set1.find(5);
	cout << "it0:" << *it0 << endl;

	set1.erase(5);


	int num1 = set1.count(5);
	cout << "num1:" << num1 << endl;

	set<int>::iterator it1 = set1.lower_bound(5);
	cout << "it1:" << *it1 << endl;

	set<int>::iterator it2 = set1.upper_bound(5);
	cout << "it2:" << *it2 << endl;


	pair<set<int>::iterator,set<int>::iterator> mypair= set1.equal_range(5);
	set<int>::iterator it3 = mypair.first;
	cout << "it3:" << *it3 << endl;

	set<int>::iterator it4 = mypair.second;
	cout << "it4:" << *it4 << endl;
}



void main()
{


	//main91();
	//main92();
	//main93();
	//main94();
	main95();


	system("pause");
}