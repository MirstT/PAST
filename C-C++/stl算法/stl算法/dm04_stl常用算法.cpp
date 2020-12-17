#include<iostream>
using namespace std;
#include<string>
#include<vector>
#include<list>
#include<set>
#include<algorithm>
#include<functional>
#include<iterator>
#include<numeric>

void printV(vector <int> &v)
{
	for(vector<int>::iterator it=v.begin();it!=v.end();it++)
	{
		cout << *it << " ";
	}
}

void printL(list <int> &v)
{
	for (list<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
}

class CMyShow
{
public:
	CMyShow()
	{
		num = 0;
	}

	void operator()(int &n)
	{
		num++;
		cout << n << " ";
	}

	void printNum()
	{
		cout << "num:" << num << endl;
	}
private:
	int num;
};


void showElem(int &n)
{
	cout << n << " ";
}

void main41_foreach_transform()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(3);
	v1.push_back(5);

	printV(v1);
	cout << endl;


	for_each(v1.begin(), v1.end(), showElem);
	cout << endl;


	for_each(v1.begin(), v1.end(), CMyShow());
	cout << endl;


	CMyShow mya;
	CMyShow my1 = for_each(v1.begin(), v1.end(), mya);
	CMyShow my2 = for_each(v1.begin(), v1.end(), CMyShow());
	cout << endl;

	mya.printNum();
	my1.printNum();
	my2.printNum();


	my1 = for_each(v1.begin(), v1.end(), CMyShow());
	cout << endl;
	my1.printNum();


}


int increase(int &i)
{
	return i + 100;
}

void main42_transfrom()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(3);
	v1.push_back(5);

	printV(v1);
	cout << endl;

	transform(v1.begin(), v1.end(), v1.begin(), increase);
	printV(v1);
	cout << endl;


	transform(v1.begin(), v1.end(), v1.begin(), negate<int>());
	printV(v1);
	cout << endl;


	list<int> mylist;
	mylist.resize(v1.size());

	transform(v1.begin(), v1.end(), v1.begin(), bind2nd(multiplies<int>(),10));
	printV(v1);
	cout << endl;

	transform(v1.begin(), v1.end(), mylist.begin(), bind2nd(multiplies<int>(), 10));
	printL(mylist);
	cout << endl;


	transform(v1.begin(), v1.end(), ostream_iterator<int>(cout, " "), negate<int>());
	cout << endl;
}


int showElem2(int n)
{
	cout << n << " ";
	return n;
}

void main43_transfrom_pk_foreach()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(3);
	v1.push_back(5);

	vector<int> v2 = v1;

	for_each(v1.begin(), v1.end(), showElem);

	transform(v2.begin(), v2.end(), v2.begin(), showElem2);

}



void main44_adjacent_find()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(5);

	vector<int>::iterator it= adjacent_find(v1.begin(), v1.end());
	if (it == v1.end())
	{
		cout << "没有找到" << endl;
	}
	else
	{
		cout << *it << endl;
	}
	int index = distance(v1.begin(), it);
	cout << "index:" << index << endl;

}


void main45_binary_search()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(3);
	v1.push_back(5);
	v1.push_back(7);
	v1.push_back(9);


	bool b=binary_search(v1.begin(), v1.end(), 7);

	if (b == true)
	{
		cout << " 找到了" << endl;
	}
	else
	{
		cout << " 没找到" << endl;
	}


}


void main46_count()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(3);
	v1.push_back(5);
	v1.push_back(7);
	v1.push_back(9);
	v1.push_back(7);
	v1.push_back(7);


	int num = count(v1.begin(), v1.end(), 7);
	cout << num << endl;
}


bool GreatThree(int iNum)
{
	if (iNum > 3)
	{
		return true;
	}
	return false;
}

void main46_coutif()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(3);
	v1.push_back(5);
	v1.push_back(7);
	v1.push_back(9);
	v1.push_back(7);
	v1.push_back(7);


	int num = count_if(v1.begin(), v1.end(), GreatThree);
	cout <<"num:"<< num << endl;


}



void main47_find()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(3);
	v1.push_back(5);
	v1.push_back(7);
	v1.push_back(9);
	v1.push_back(7);
	v1.push_back(7);


	vector<int>::iterator it= find(v1.begin(), v1.end(), 5);
	cout << "*it:" << *it << endl;

}



void main47_findif()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(3);
	v1.push_back(5);
	v1.push_back(7);
	v1.push_back(9);
	v1.push_back(7);
	v1.push_back(7);


	vector<int>::iterator it = find(v1.begin(), v1.end(), 5);
	cout << "*it:" << *it << endl;

	vector<int>::iterator it2 = find_if(v1.begin(), v1.end(), GreatThree);
	cout << "*it:" << *it2 << endl;

}


void main_merge()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(3);
	v1.push_back(5);

	vector<int> v2;
	v2.push_back(2);
	v2.push_back(4);
	v2.push_back(6);

	vector<int> v3;
	v3.resize(v1.size() + v2.size());

	merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());

	printV(v3);

}


class Student
{

public:
	Student(string name, int id)
	{
		m_name = name;
		m_id = id;
	}
	void printT()
	{
		cout << "name:" << m_name<<" id:"<<m_id<<endl;
	}

public:
	string m_name;
	int m_id;
};

bool CompareS(Student &s1, Student &s2)
{
	return (s1.m_id < s2.m_id);
}


void main_sort()
{

	Student s1((char*)"老大", 1);
	Student s2((char*)"老二", 2);
	Student s3((char*)"老三", 3);
	Student s4((char*)"老四", 4);

	vector<Student> v1;
	v1.push_back(s4);
	v1.push_back(s1);
	v1.push_back(s3);
	v1.push_back(s2);

	for (vector<Student>::iterator it = v1.begin(); it != v1.end(); it++)
	{
		it->printT();
	}

	sort(v1.begin(), v1.end(), CompareS);


	for (vector<Student>::iterator it = v1.begin(); it != v1.end(); it++)
	{
		it->printT();
	}
}


void main_random_shuffle()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(3);
	v1.push_back(5);
	v1.push_back(7);

	random_shuffle(v1.begin(), v1.end());


	printV(v1);


	string str = "abcdefg";
	random_shuffle(str.begin(), str.end());
	cout << "str:" << str << endl;

}


void main_reverse()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(3);
	v1.push_back(5);
	v1.push_back(7);

	reverse(v1.begin(), v1.end());

	printV(v1);

}



void main52_copy()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(3);
	v1.push_back(5);
	v1.push_back(7);


	vector<int> v2;
	v2.resize(v1.size());

	copy(v1.begin(), v1.end(), v2.begin());
	printV(v2);

}

void main53_replace()
{
	vector<int> v1;

	v1.push_back(1);
	v1.push_back(3);
	v1.push_back(5);
	v1.push_back(7);
	v1.push_back(3);
	v1.push_back(3);


	replace(v1.begin(), v1.end(), 3, 8);
	printV(v1);


}

bool great_equal_5(int &n)
{
	if (n >= 5)
	{
		return true;
	}
	return false;
}



void main53_replaceif()
{
	vector<int> v1;

	v1.push_back(1);
	v1.push_back(3);
	v1.push_back(5);
	v1.push_back(7);
	v1.push_back(3);
	v1.push_back(3);


	replace(v1.begin(), v1.end(), 3, 8);

	replace_if(v1.begin(), v1.end(), great_equal_5, 1);

	printV(v1);


}


void main54_swap()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(3);
	v1.push_back(5);

	vector<int> v2;
	v2.push_back(2);
	v2.push_back(4);
	v2.push_back(6);


	printV(v1);
	printV(v2);
	cout << endl;
	swap(v1, v2);
	printV(v1);
	printV(v2);

}


void main55_accumulate()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(3);
	v1.push_back(5);

	int tmp = accumulate(v1.begin(), v1.end(), 100);
	cout << tmp << endl;

}


void main56_fill()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(3);
	v1.push_back(5);

	fill(v1.begin(), v1.end(), 8);
	printV(v1);

}


void main57_union()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(3);
	v1.push_back(5);

	vector<int> v2;
	v2.push_back(1);
	v2.push_back(4);
	v2.push_back(6);

	vector<int> v3;
	v3.resize(v1.size() + v2.size());

	//set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
	//set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
	set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());

	printV(v3);

}

void main()
{
	//main41_foreach_transform();
	//main42_transfrom();
	//main43_transfrom_pk_foreach();
	//main44_adjacent_find();
	//main45_binary_search();
	//main46_count();
	//main46_coutif();
	//main47_find();
	//main47_findif();
	//main_merge();
	//main_sort();
	//main_random_shuffle();



	//main_reverse();

	//main52_copy();
	//main53_replace();

	//main53_replaceif();

	//main54_swap();

	//main55_accumulate();

	//main56_fill();


	main57_union();


	system("pause");
}