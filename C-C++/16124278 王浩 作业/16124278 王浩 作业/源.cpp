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
	cout << "               班级内全部学生成绩记录（10名）" << endl;
	picture1();
	for (i=0; i <= 9; i++)
	{
		cout << "请依次输入第 " << i + 1 <<
			" 位学生的学号，姓名，性别，平时成绩，期中成绩和期末成绩。" << endl;
		cin >> s[i].num >> s[i].name >>s[i].sex>>
			s[i].score[1] >> s[i].score[2] >> s[i].score[3];
		if ((s[i].sex != "男" && s[i].sex != "女") ||
			(s[i].score[1] < 0 || s[i].score[1]>100) ||
			(s[i].score[2] < 0 || s[i].score[2]>100) ||
			(s[i].score[3] < 0 || s[i].score[3]>100))
		{
			picture1();
			cout << "输入数据有误，请重新输入！！！"<<endl;
			if(s[i].sex != "男" && s[i].sex != "女")
				cout << "性别输入有误，请输入：‘男’或‘女’！"<< endl;
			if (s[i].score[1] < 0 || s[i].score[1]>100)
				cout << "平时成绩输入有误，请输入：0-100之间的数字！" << endl;
			if (s[i].score[2] < 0 || s[i].score[2]>100)
				cout << "期中成绩输入有误，请输入：0-100之间的数字！"<<endl;
			if (s[i].score[3] < 0 || s[i].score[3]>100)
				cout << "期末成绩输入有误，请输入：0-100之间的数字！"<<endl;
			picture1();
			cout << "请依次重新输入第 " << i + 1 << 
				" 位学生的学号，姓名，性别，平时成绩，期中成绩和期末成绩。" << endl;
			cin >> s[i].num >> s[i].name >> s[i].sex >>
				s[i].score[1] >> s[i].score[2] >> s[i].score[3];
		}
	}
	
	cout <<endl<<endl<< "                          ++++输入数据++++" << endl;
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
	cout << endl << endl<< "                          ++++成绩总榜++++" << endl;
	title2();
	for (j = 0; j <= 9; j++)
		for (i = 0; i <= 9; i++)
	{
		if (a[j] == s[i].total)
		{
			cout << "第" << j + 1<<"名  ";
			print(s[i]);
		}
	}
	picture1();
	picture1();
	cout << "输入你想要查找的学生的学号或者姓名（任意一个）" << endl;
	cin >> find;
	bool flage = false;
	for (i=0; i <= 9; i++)
		if (s[i].name == find || s[i].num == find)
		{
			cout << s[i].num << "  " << s[i].name << "  的学生信息已找到" << endl;
			title1();
			print(s[i]);
			flage = true;
			break;
		}
	if (flage == false)
		cout << "查无此人" << endl;
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
		"  学号       名字    性别     平时成绩    期中成绩    期末成绩   总成绩" << endl;
}
void title2()
{
	cout << endl<<
		"名次     学号       名字    性别     平时成绩    期中成绩    期末成绩   总成绩" << endl;
}