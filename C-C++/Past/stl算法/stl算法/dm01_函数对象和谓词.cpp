#include<iostream>
using namespace std;
#include<string>
#include<vector>
#include<list>
#include<set>
#include<algorithm>
#include<functional>


template <typename T>
class ShowElemt
{
public:
	ShowElemt()
	{
		n = 0;
	}
	void operator()(T&t)
	{
		n++;
		//printN();
		cout << t << " ";
	}
	void printN()
	{
		cout << "n:" << n << endl;
	}
private:
	int n;

};


template<typename T>
void FuncShowElemt(T&t)
{
	cout << t << " " ;
}

void FuncShowElemt2(int&t)
{
	cout << t << " ";
}

void main01()
{
	int a = 10;
	ShowElemt<int> showElemt;
	showElemt(a);


	FuncShowElemt<int>(a);
	FuncShowElemt2(a);
}


void main02()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(3);
	v1.push_back(5);

	for_each(v1.begin(), v1.end(), ShowElemt<int>());
	cout << endl;
	for_each(v1.begin(), v1.end(), FuncShowElemt2);
	cout << endl;


	ShowElemt<int> show1;
	show1=for_each(v1.begin(), v1.end(), show1);
	show1.printN();
}


template<typename T>
class IsDiv
{
public:
	IsDiv(const T &divisor)
	{
		this->divisor = divisor;
	}
	bool operator()(T &t)
	{
		return (t%divisor == 0);
	}

private:
	T divisor;
};

void main03()
{
	vector<int> v2;
	for (int i = 10; i < 33; i++)
	{
		v2.push_back(i);
	}
	int a = 4;
	IsDiv<int> myDiv(a);
	vector<int>::iterator it;
	it = find_if(v2.begin(), v2.end(), IsDiv<int>(a));
	if (it == v2.end())
	{
		cout << "容器中没有值是4的元素" << endl;
	}
	else
	{
		cout << "第一个被4整除的元素是：" << *it << endl;
	}

}


template<typename T>
class SumAdd
{
public:
	T operator()(T &t1, T &t2)
	{
		return t1 + t2;
	}
};

void main04()
{
	vector<int> v1, v2;
	vector<int> v3;
	v1.push_back(1);
	v1.push_back(3);
	v1.push_back(5);

	v2.push_back(2);
	v2.push_back(4);
	v2.push_back(6);

	v3.resize(10);

	transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), SumAdd<int>());

	for (vector<int>::iterator it = v3.begin(); it != v3.end(); it++)
	{
		cout << *it << endl;
	}
}

bool MyCompare(const int &a, const int &b)
{
	return a < b;
}


void main05()
{
	vector<int> v1(10);
	for (int i = 0; i < 10; i++)
	{
		int tmp = rand() % 100;
		v1[i] = tmp;
	}

	for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;

	for_each(v1.begin(), v1.end(), ShowElemt<int>());
	cout << endl;

	for_each(v1.begin(), v1.end(), FuncShowElemt<int>);
	cout << endl;

	for_each(v1.begin(), v1.end(), FuncShowElemt2);
	cout << endl;

	sort(v1.begin(), v1.end(), MyCompare);
	for_each(v1.begin(), v1.end(), FuncShowElemt2);
	cout << endl;

}

struct CompareNoCase
{
	bool operator()(const string &str1, const string &str2) const
	{
		string str1_;
		str1_.resize(str1.size());
		transform(str1.begin(), str1.end(), str1_.begin(), tolower);

		string str2_;
		str2_.resize(str2.size());
		transform(str2.begin(), str2.end(), str2_.begin(), tolower);
		return (str1_ < str2_);
	}
};


void main06()
{
	set<string> set1;
	set1.insert("bbb");
	set1.insert("aaa");
	set1.insert("ccc");

	set<string>::iterator it = set1.find("aaa"); //find 默认区分大小写
	if (it == set1.end())
	{
		cout << "没有查找到 " << endl;
	}
	else
	{
		cout << " 查找到" << endl;
	}


	set<string, CompareNoCase> set2;
	set2.insert("bbb");
	set2.insert("aaa");
	set2.insert("ccc");


	set<string, CompareNoCase>::iterator it2 = set2.find("aAa"); //find 默认区分大小写
	if (it2 == set2.end())
	{
		cout << "没有查找到 " << endl;
	}
	else
	{
		cout << "不区分大小写的 查找到" << endl;
	}

}

void main()
{

	//main01();
	//main02();
	//main03();
	//main04();
	//main05();
	main06();


	system("pause");
}

