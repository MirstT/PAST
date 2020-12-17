#include<iostream>
using namespace std;
#include<map>
#include<string>

class Person
{
public:
	string	name;
	int		age;
	string	tel;
	double	saly;

};

void main1201()
{
	Person p1, p2, p3, p4, p5;
	p1.name = "王1";
	p1.age = 31;

	p2.name = "王2";
	p2.age = 31;

	p3.name = "张3";
	p3.age = 33;

	p4.name = "张4";
	p4.age = 34;

	p5.name = "赵5";
	p5.age = 35;

	multimap<string, Person> map2;

	map2.insert(make_pair("sale", p1));
	map2.insert(make_pair("sale", p2));

	map2.insert(make_pair("development", p3));
	map2.insert(make_pair("development", p4));

	map2.insert(make_pair("financial", p5));

	for (multimap<string, Person>::iterator it = map2.begin(); it != map2.end(); it++)
	{
		cout << it->first << "\t" << it->second.name << endl;
	}
	cout << "遍历结束" << endl;

	int num2 = map2.count("development");
	cout << "development部门人数：" << num2 <<endl;

	cout << "development部门员工信息" << endl;
	multimap<string,Person>::iterator it2=map2.find("development");
	int tag = 0;
	while (it2!=map2.end()&&tag<num2)
	{
		cout << it2->first << "\t" << it2->second.name << endl;
		it2++;
		tag++;
	}
}

void main1202()
{
	Person p1, p2, p3, p4, p5;
	p1.name = "王1";
	p1.age = 31;

	p2.name = "王2";
	p2.age = 32;

	p3.name = "张3";
	p3.age = 33;

	p4.name = "张4";
	p4.age = 34;

	p5.name = "赵5";
	p5.age = 35;

	multimap<string, Person> map2;

	map2.insert(make_pair("sale", p1));
	map2.insert(make_pair("sale", p2));

	map2.insert(make_pair("development", p3));
	map2.insert(make_pair("development", p4));

	map2.insert(make_pair("financial", p5));


	
	for (multimap<string, Person>::iterator it = map2.begin(); it != map2.end(); it++)
	{
		cout << it->first << "\t" << it->second.name << endl;
		if (it->second.age == 32)
		{
			it->second.name = "name32";
		}
	}
	cout << "遍历结束" << endl;


	for (multimap<string, Person>::iterator it = map2.begin(); it != map2.end(); it++)
	{
		cout << it->first << "\t" << it->second.name << endl;
		/*if (it->second.age == 32)
		{
			it->second.name = "name32";
		}*/
	}


}

void main()
{
	//main1201();
	main1202();
	system("pause");
}