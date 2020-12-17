#include<iostream>
using namespace std;
#include<list>

void main71()
{
	list<int> l;
	cout << "list 的大小" << l.size() << endl;
	for (int i = 0; i < 10; i++)
	{
		l.push_back(i);
	}

	cout << "list的大小：" << l.size() << endl;

	list<int>::iterator it = l.begin();
	while (it!=l.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;

	it = l.begin();
	it++;
	it++;
	it++;
	//it += 5;

	l.insert(it, 100);

	for (list<int>::iterator it = l.begin(); it != l.end(); it++)
	{
		cout << *it << " ";
	}



}

void main72()
{
	list<int> l;
	cout << "list 的大小" << l.size() << endl;
	for (int i = 0; i < 10; i++)
	{
		l.push_back(i);
	}

	cout << "list的大小：" << l.size() << endl;

	for (list<int>::iterator it = l.begin(); it != l.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;

	list<int>::iterator it1 = l.begin();
	list<int>::iterator it2 = l.begin();
	it2++;
	it2++;
	it2++;

	l.erase(it1, it2);


	for (list<int>::iterator it = l.begin(); it != l.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
	/*l.erase(l.begin(), l.begin() + 3);*/

	l.insert(l.begin(), 3, 100);


	for (list<int>::iterator it = l.begin(); it != l.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;




	l.erase(l.begin());
	l.remove(100);



	for (list<int>::iterator it = l.begin(); it != l.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}


void main()
{
	//main71();
	main72();


	system("pause");

}