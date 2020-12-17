#include<iostream>
using namespace std;
#include<string>
#include<vector>
#include<list>
#include<set>
#include<algorithm>
#include<functional>


void main21()
{
	plus<int> intAdd;
	int x = 10;
	int y = 20;
	int z = intAdd(x, y);
	cout << "z:" << z << endl;

	plus<string> stringAdd;
	string s1 = "aaa";
	string s2 = "bbb";
	string s3 = stringAdd(s1, s2);
	cout << "s3:" << s3 << endl;

	vector<string> v1;
	v1.push_back("bbb");
	v1.push_back("aaa");
	v1.push_back("ccc");
	v1.push_back("zzz");
	v1.push_back("ccc");
	v1.push_back("ccc");


	sort(v1.begin(), v1.end(), greater<string>());

	for (vector<string>::iterator it = v1.begin(); it != v1.end(); it++)
	{
		cout << *it << endl;
	}

	string sc = "ccc";

	int num=count_if(v1.begin(), v1.end(), bind2nd(equal_to<string>(),sc));
	cout << "num:" << num << endl;
}


struct IsGreat
{
public:
	IsGreat(int i)
	{
		m_num = i;
	}
	bool operator()(int &num)
	{
		if (num > m_num)
		{
			return true;
		}
		return false;
	}

private:
	int m_num;

};

void main22()
{
	vector<int> v1;
	for(int i=0;i<10;i++)
	{
		v1.push_back(i + 1);
	}
	for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;

	int num1 = count(v1.begin(), v1.end(), 3);
	cout << "num1:" << num1 << endl;

	int num2 = count_if(v1.begin(), v1.end(), IsGreat(2));
	cout << "num2:" << num2 << endl;

	int num3 = count_if(v1.begin(), v1.end(), bind2nd(greater<int>(), 2));
	cout << "num3:" << num3 << endl;	

	int num4 = count_if(v1.begin(), v1.end(), bind2nd(modulus<int>(), 2));
	cout << "num4:" << num4 << endl;

	int num5 = count_if(v1.begin(), v1.end(),not1( bind2nd(modulus<int>(), 2)));
	cout << "num5:" << num5 << endl;
}
void main()
{
	//main21();
	main22();

	system("pause");
}