#include<iostream>
using namespace std;
#include<fstream>
#include<iomanip>



class Teacher
{
public:
	Teacher()
	{
		age = 33;
		strcpy_s(name, 32, "");
	}
	Teacher(int _age, char *_name)
	{
		age = _age;
		strcpy_s(name, 32, _name);
	}
private:
	int age;
	char name[32];
};
void main()
{

	/*char FN[80];
	char buffer[256];

	cout << "FN:";
	cin >> FN;

	ofstream fout(FN, ios::app);
	fout << "1111111111111111\n";
	fout << "233333333333333333\n";

	cin.getline(buffer, 255);

	fout << buffer << "\n";
	fout.close();

	ifstream fin(FN);
	cout << "FN:" << endl;
	char ch;
	while (fin.get(ch))
		cout << ch;
	cout << "FN END\n";
	fin.close();*/


	//fstream myfile;
	//myfile.open("ss", ios::out | ios::app, 0);
	//if (!myfile)
	//{
	//	exit(1);
	//}

	//myfile << "dddd" << endl << "dddddddd" << endl;
	//myfile.close();

	//myfile.open("ss", ios::in, 0);
	//if (!myfile)
	//{
	//	exit(1);
	//}

	//char ch;
	//while (myfile.get(ch))
	//{
	//	cout.put(ch);
	//}
	//myfile.close();





	/*char FN[255] = "ss";
	ofstream fout(FN, ios::binary);
	if (!fout)
	{
		cout << "ddd";
	}
	
	Teacher t1(32, (char*)"341");
	Teacher t2(33, (char*)"dfsdfdsf");
	

	fout.write((char*)&t1, sizeof(Teacher));
	fout.write((char*)&t2, sizeof(Teacher));
	fout.close();


	cout << endl;

	ifstream fin(FN, ios::binary);
	if (!fin)
	{
		cout << "dsdfsf";
	}

	Teacher tmp;


	fin.read((char*)&tmp, sizeof(Teacher));*/

	long a = 234;
	double b = 2345.67890;
	char c[100];
	cout.fill('*');
	cout.flags(ios_base::left);
	cout.width(12);
	cout << a << endl;
	cout.fill('*');
	cout.flags(ios::right);
	cout.width(12);
	cout << a << endl;
	
	cout.flags()
	cout




	system("pause");
}