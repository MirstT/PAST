#include<iostream>
using namespace std;
#include<set>

void main1001()
{
	multiset<int> set1;

	int tmp = 0;

	printf("�����룺");
	scanf_s("%d", &tmp);
	while (tmp != 0)
	{
		set1.insert(tmp);
		printf("�����룺");
		scanf_s("%d", &tmp);
	}

	for (multiset<int>::iterator it = set1.begin(); it != set1.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;

	while (!set1.empty())
	{
		multiset<int>::iterator it = set1.begin();
		cout << *it << " ";
		set1.erase(it);
	}

}



void main()
{
	main1001();
	system("pause");
}