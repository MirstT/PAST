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
//
//
//void myswap(int a, char c)
//{
//	cout << "a:" << a << " c:" << c << endl;
//	cout << "hello.........��ͨ����" << endl;
//}
//
//
////��ʾ���͵���
////�Զ������Ƶ�
//
//void main()
//{
//
//	int		a = 10;
//	char	c = 'z';
//
//	myswap(a, c);//��ͨ�����ĵ��ã����Խ�����ʽ������ת��
//
//	myswap(c, a);
//
//	myswap(a, a);//���ú���ģ�壨���������Ͳ������������ϸ������ͽ���ƥ�䣬��������Զ�����ת��
//
//
//
//
//
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
