#include<iostream>
using namespace std;
#include<queue>


void main61()
{

	queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);

	cout << "队头元素:" << q.front() << endl;
	cout << "队列的大小" << q.size() << endl;
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