#include<iostream>
#include<string>
#include<iomanip>
using namespace std;
struct Student
{
	string num;
	string name;
	string sex;
	float score[4];
	float total;
};
int main()
{
	void print(Student&), 
		picture1(), 
		search(string, Student&), 
		title1(), 
		title2();
	Student s[10];
	string find;
	int i ,j;
	float t,a[10];
	picture1();
	cout << "               �༶��ȫ��ѧ���ɼ���¼��10����" << endl;
	picture1();
	for (i=0; i <= 9; i++)
	{
		cout << "����������� " << i + 1 <<
			" λѧ����ѧ�ţ��������Ա�ƽʱ�ɼ������гɼ�����ĩ�ɼ���" << endl;
		cin >> s[i].num >> s[i].name >>s[i].sex>>
			s[i].score[1] >> s[i].score[2] >> s[i].score[3];
		if ((s[i].sex != "��" && s[i].sex != "Ů") ||
			(s[i].score[1] < 0 || s[i].score[1]>100) ||
			(s[i].score[2] < 0 || s[i].score[2]>100) ||
			(s[i].score[3] < 0 || s[i].score[3]>100))
		{
			picture1();
			cout << "���������������������룡����"<<endl;
			if(s[i].sex != "��" && s[i].sex != "Ů")
				cout << "�Ա��������������룺���С���Ů����"<< endl;
			if (s[i].score[1] < 0 || s[i].score[1]>100)
				cout << "ƽʱ�ɼ��������������룺0-100֮������֣�" << endl;
			if (s[i].score[2] < 0 || s[i].score[2]>100)
				cout << "���гɼ��������������룺0-100֮������֣�"<<endl;
			if (s[i].score[3] < 0 || s[i].score[3]>100)
				cout << "��ĩ�ɼ��������������룺0-100֮������֣�"<<endl;
			picture1();
			cout << "��������������� " << i + 1 << 
				" λѧ����ѧ�ţ��������Ա�ƽʱ�ɼ������гɼ�����ĩ�ɼ���" << endl;
			cin >> s[i].num >> s[i].name >> s[i].sex >>
				s[i].score[1] >> s[i].score[2] >> s[i].score[3];
		}
	}
	
	cout <<endl<<endl<< "                          ++++��������++++" << endl;
	title1();
	for (i = 0; i <= 9; i++)
	{
		s[i].total = s[i].score[1]*0.2 + s[i].score[2]*0.3 + s[i].score[3]*0.5;
		print(s[i]);
		a[i] = s[i].total;
	}
	for(j=0;j<=8;j++)
		for(i=0;i<=9-j;i++)
			if (a[i]< a[i + 1])
			{
				t = a[i];
				a[i] = a[i + 1];
				a[i + 1] = t;
			}
	cout << endl << endl<< "                          ++++�ɼ��ܰ�++++" << endl;
	title2();
	for (j = 0; j <= 9; j++)
		for (i = 0; i <= 9; i++)
	{
		if (a[j] == s[i].total)
		{
			cout << "��" << j + 1<<"��  ";
			print(s[i]);
		}
	}
	picture1();
	picture1();
	cout << "��������Ҫ���ҵ�ѧ����ѧ�Ż�������������һ����" << endl;
	cin >> find;
	bool flage = false;
	for (i=0; i <= 9; i++)
		if (s[i].name == find || s[i].num == find)
		{
			cout << s[i].num << "  " << s[i].name << "  ��ѧ����Ϣ���ҵ�" << endl;
			title1();
			print(s[i]);
			flage = true;
			break;
		}
	if (flage == false)
		cout << "���޴���" << endl;
	picture1();
	picture1();
	return 0;
}
void print(Student &s)
{
	cout << setw(8) << s.num << "   " << setw(6) << s.name << "   "
		<< setw(4) << s.sex << "   " << setw(8) << s.score[1] << "     "
		<< setw(7) << s.score[2] << "     " << setw(7) << s.score[3] <<"   " 
		<< setw(7) << s.total<< endl;
}
void picture1()
{
	cout << 
		"*****************************************************************************" << endl;
}
void title1()
{
	cout << endl << 
		"  ѧ��       ����    �Ա�     ƽʱ�ɼ�    ���гɼ�    ��ĩ�ɼ�   �ܳɼ�" << endl;
}
void title2()
{
	cout << endl<<
		"����     ѧ��       ����    �Ա�     ƽʱ�ɼ�    ���гɼ�    ��ĩ�ɼ�   �ܳɼ�" << endl;
}