//#include<iostream>
//using namespace std;
//
//
//
////�����߼�һ����������һ����
//void myswap1(int &a, int &b)
//{
//	int c = 0;
//	c = a;
//	a = b;
//	b = c;
//
//}
//void myswap2(char &a, char &b)
//{
//	char c = 0;
//	c = a;
//	a = b;
//	b = c;
//
//}
//
//
////���ͱ��
////template ��ʼ���ͱ��
//template <typename T>
//void myswap(T &a, T&b)
//{
//	T c;
//	c = a;
//	a = b;
//	b = c;
//	cout << "hello.......����ģ��" << endl;
//}
//
////��ʾ���͵���
////�Զ������Ƶ�
//
//void main()
//{
//
//	{
//		int x = 10;
//		int y = 20;
//
//
//		//myswap<int>(x, y);  //��ʾ���͵���
//		myswap(x, y);  //�Զ������Ƶ�
//
//		printf("x:%d y:%d\n", x, y);
//
//
//	}
//
//	{
//		char a = 'a';
//		char b = 'b';
//
//		//myswap<char>(a, b);  //��ʾ���͵���
//		myswap(a, b);  //�Զ������Ƶ�
//
//		printf("a:%c b:%c\n", a, b);
//
//
//	}
//
//	system("pause");
//}
//
//
//
//
//void main11()
//{
//
//	{
//		int x = 10;
//		int y = 20;
//
//		myswap1(x, y);
//		printf("x:%d y:%d\n", x, y);
//	}
//
//	{
//		char a = 'a';
//		char b = 'b';
//
//		myswap2(a, b);
//		printf("a:%c b:%c\n", a, b);
//	}
//
//
//	system("pause");
//}
//
//
//
