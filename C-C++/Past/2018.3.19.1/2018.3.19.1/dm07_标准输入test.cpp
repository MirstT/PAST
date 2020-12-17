#include<iostream>
using namespace std;

void main()
{
	///*char ch;
	//while ((ch=cin.get())!=EOF)
	//{
	//	cout << ch << endl;
	//}*/
	//char a;
	//char b;
	/*int c;*/

	//cin.get(a).get(c).get(a);

	//char buf1[256];
	//char buf2[256];

	//cin >> buf1;
	//cin.getline(buf2, 256);
	//cout << buf1 << endl;
	//cout << buf2 << endl;
	//cout << c << endl;
	//cout << c << endl;
	//cout << a << endl;




	char c = cin.get();
	if ((c >= '0') && (c <= '9'))
	{
		int n;
		cin.putback(c);
		cin >> n;
		cout << "sssss"<<n << '\n';
	}
	else
	{
		char str[256];
		cin.putback(c);
		cin.getline(str,256);
		cout << "23333" << str << '\n';
	}

	system("pause");

}