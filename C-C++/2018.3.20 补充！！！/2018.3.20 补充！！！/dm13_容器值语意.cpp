#include<iostream>
using namespace std;
#include<vector>


class Teacher
{
public:
	Teacher(char *name, int age)
	{
		m_pname = new char[strlen(name) + 1];
		strcpy_s(m_pname, 32, name);
		m_age = age;
	}
	~Teacher()
	{
		if (m_pname != NULL)
		{
			delete[] m_pname;
			m_pname = NULL;
			m_age = 0;
		}
	}

	Teacher(const Teacher &obj)
	{
		m_pname = new char[strlen(obj.m_pname) + 1];
		strcpy_s(m_pname, 32, obj.m_pname);
		m_age = obj.m_age;
	}


	Teacher& operator=(const Teacher &obj)
	{
		if (m_pname != NULL)
		{
			delete[] m_pname;
			m_pname = NULL;
			m_age = 0;
		}

		m_pname = new char[strlen(obj.m_pname) + 1];
		strcpy_s(m_pname, 32, obj.m_pname);
		m_age = obj.m_age;
	}

	void printT()
	{
		cout << m_pname << "\t" << m_age << endl;
	}

private:
	char	*m_pname;
	int		m_age;
};



void main1301()
{

	Teacher t1((char*)"t1", 31);
	t1.printT();

	vector<Teacher> v1;
	v1.push_back(t1);




}

void main()
{

	main1301();
	system("pause");
}