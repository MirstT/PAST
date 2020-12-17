//#include<iostream>
//#include<map>
//#include<ctime>
//
//using namespace std;
//
//void main()
//{
//	time_t t;
//	srand((unsigned int)time(&t));
//	int a[100] = { 0 };
//	for (int i = 0; i < 100; i++)
//	{
//		a[i] = rand() % 100;
//	}
//
//	for (int i = 0; i < 100; i++)//打印
//	{
//		cout << a[i] << "\t";
//	}
//
//	map<int, int> M;
//	for (int i = 0; i < 100; i++)
//	{
//		pair<map<int, int>::iterator, bool> pairIt = M.insert(pair<int, int>(a[i], 1));
//		if (pairIt.second != true)
//		{
//			M[a[i]]++;
//		}
//	}
//
//	int max = 0;//存储频率
//	int n = 0;//下标
//	int data = 0;//a[i]
//	for (int i = 0; i < 100; i++)
//	{
//		if (M[a[i]]>max)
//		{
//			n = i;
//			data = a[i];
//			max = M[a[i]];
//		}
//	}
//
//	cout << "出现最多的是：a[" << n << "]=" << data << "　　　出现次数：" << max << endl;
//
//	cin.get();
//}
