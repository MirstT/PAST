#include<iostream>
using namespace std;
#include<queue>


void main61()
{

	queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);

	cout << "��ͷԪ��:" << q.front() << endl;
	cout << "���еĴ�С" << q.size() << endl;
	while (!q.empty())
	{
		int tmp = q.front();
		cout << tmp << " ";
		q.pop();
	}

}




void main()
{

	main61();
	system("pause");

}