#include<iostream>
using namespace std;
#include<map>
#include<string>

void main1101()
{
	map<int, string> map1;

	map1.insert(pair<int, string>(1, "teacher01"));
	map1.insert(pair<int, string>(2, "teacher02"));

	map1.insert(make_pair(3, "teacher03"));
	map1.insert(make_pair(4, "teacher04"));


	map1.insert(map<int, string>::value_type(5, "teacher05"));
	map1.insert(map<int, string>::value_type(6, "teacher05"));

	map1[7] = "teacher07";
	map1[8] = "teacher08";

	for (map<int, string>::iterator it = map1.begin(); it != map1.end(); it++)
	{
		cout << it->first << "\t" << it->second << endl;
	}
	cout << "��������" << endl;


	while (!map1.empty())
	{
		map<int, string>::iterator it = map1.begin();
		cout << it->first << "\t" << it->second << endl;
		map1.erase(it);
	}


}


void main1102()
{
	map<int, string> map1;

	pair<map<int,string>::iterator,bool> mypair1= map1.insert(pair<int, string>(1, "teacher01"));
	map1.insert(pair<int, string>(2, "teacher02"));

	pair<map<int, string>::iterator, bool> mypair3 = map1.insert(make_pair(3, "teacher03"));
	map1.insert(make_pair(4, "teacher04"));




	pair<map<int, string>::iterator, bool> mypair5 = map1.insert(map<int, string>::value_type(5, "teacher05"));
	if (mypair5.second != true)
	{
		cout << "key 5 ����ʧ��" << endl;
	}
	else
	{
		cout << mypair5.first->first << "\t" << mypair5.first->second << endl;
	}

	pair<map<int, string>::iterator, bool> mypair6=map1.insert(map<int, string>::value_type(5, "teacher05"));
	if (mypair6.second != true)
	{
		cout << "key 6 ����ʧ��" << endl;
	}
	else
	{
		cout << mypair6.first->first << "\t" << mypair6.first->second << endl;
	}





	map1[7] = "teacher07";
	map1[7] = "teacher77";

	for (map<int, string>::iterator it = map1.begin(); it != map1.end(); it++)
	{
		cout << it->first << "\t" << it->second << endl;
	}
	cout << "��������" << endl;




}

void main1103()
{
	map<int, string> map1;

	map1.insert(pair<int, string>(1, "teacher01"));
	map1.insert(pair<int, string>(2, "teacher02"));

	map1.insert(make_pair(3, "teacher03"));
	map1.insert(make_pair(4, "teacher04"));


	map1.insert(map<int, string>::value_type(5, "teacher05"));
	map1.insert(map<int, string>::value_type(6, "teacher05"));

	map1[7] = "teacher07";
	map1[8] = "teacher08";

	for (map<int, string>::iterator it = map1.begin(); it != map1.end(); it++)
	{
		cout << it->first << "\t" << it->second << endl;
	}
	cout << "��������" << endl;



	map<int,string>::iterator it2= map1.find(100);
	if (it2 == map1.end())
	{
		cout << "key 100 ��ֵ ������" << endl;
	}
	else
	{
		cout << it2->first << "\t" << it2->second << endl;
	}

	pair<map<int,string>::iterator,map<int,string>::iterator> mypair= map1.equal_range(5);

	if (mypair.first == map1.end())
	{
		cout << "��һ��������>=5��λ�ò�����" << endl;
	}
	else
	{
		cout << mypair.first->first << "\t" << mypair.first->second << endl;
	}

	if (mypair.second == map1.end())
	{
		cout << "�ڶ���������>5��λ�ò�����" << endl;
	}
	else
	{
		cout << mypair.second->first << "\t" << mypair.second->second << endl;
	}

}


void main()
{
	//main1101();
	//main1102();
	main1103();

	system("pause");

}