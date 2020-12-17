#include<iostream>
using namespace std;
#include"string"
#include"algorithm"

void main21()
{

	string s1 = "aaaaaaa";
	string s2("bbbbbbb");
	string s3 = s2;
	//string s4 = (10, 'a');

	cout << "s1:" << s1 << endl;
	cout << "s2:" << s2 << endl;
	cout << "s3:" << s3 << endl;
	//cout << "s4:" << s4 << endl;

}

void main22()
{
	string s1 = "abcdefg";

	for (int i = 0; i < s1.length(); i++)
	{
		cout << s1[i] << " ";
	}
	cout << endl;

	for (string::iterator it = s1.begin(); it != s1.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;



	cout << "at之后\n";
	try
	{ 
		for (int i = 0; i < s1.length()+3; i++)
		{
			cout << s1.at(i) << " "; //s1[i] 不抛异常，出现错误，程序中断！！！
		}
	}
	catch (...)
	{
		cout << "发生异常\n";
	}
}


void main23()
{
	string s1 = "aaaaa333333333333";
	//s1==>char*
	printf("s1:%s\n", s1.c_str());
	//char*===>string


	//s1的内容copy buf中
	char buf1[128] = { 0 };
	s1._Copy_s(buf1, 128, 3,6);
	cout << "buf1:" << buf1 << endl;

}

void main24()
{
	string s1 = "aaa";
	string s2 = "bbb";
	s1 = s1 + s2;
	cout << "s1:" << s1 << endl;

	string s3 = "2222";
	string s4 = "44444";
	s3.append(s4);
	cout << "s3:" << s3 << endl;

}
void main25()
{

	string s1 = "wbm hello wbm 111 wbm 222 wbm 3333 ";

	int index=s1.find("wbm", 0);
	cout << "index:" << index << endl;
	




	int offindex = s1.find("wbm", 0);
	while (offindex!=string::npos)
	{
		cout << "offindex:" << offindex << endl;
		offindex += 1;
		offindex = s1.find("wbm", offindex);
	}


	string s3 = "aaa bbb ccc";
	s3.replace(0, 3, "AAA");
	cout << "s3:" << s3 << endl;




	offindex = s1.find("wbm", 0);
	while (offindex != string::npos)
	{
		//cout << "offindex:" << offindex << endl;
		s1.replace(offindex, 3, "WBM");
		offindex += 1;
		offindex = s1.find("wbm", offindex);
	}
	cout << "s1替换后的结果：" << s1 << endl;


}


void main26()
{
	string s1 = "hello1 hello2 hello1";
	string::iterator it=find(s1.begin(), s1.end(), 'l');
	if (it != s1.end())
	{
		s1.erase(it);
	}

	cout << "delete l:" << s1 << endl;

	s1.erase(s1.begin(), s1.end());
	cout << "delete s1:" << s1 << endl;
	cout << "s1.length:" << s1.length() << endl;

	string s2 = "BBB";

	s2.insert(0, "AAAAA");
	s2.insert(s2.length(), "CCCCC");
	cout << "s2:"<<s2 << endl;




}

void main27()
{
	string s1 = "AAAAbbb";
	transform(s1.begin(), s1.end(), s1.begin(),toupper);
	cout << "s1:" << s1 << endl;

	string s2 = "AAAAbbbbb";
	transform(s2.begin(), s2.end(), s2.begin(), tolower);
	cout << "s2:" << s2 << endl;
}




void main()
{
	//main21();
	//main22();
	//main23();
	//main24();
	//main25();
	//main26();
	main27();


	system("pause");
}