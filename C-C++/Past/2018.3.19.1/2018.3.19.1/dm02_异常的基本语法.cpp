#include<iostream>
using namespace std;

//�쳣�ǿ纯����
//�����쳣�󣬿��Բ��������������׳��쳣
//�쳣�ǰ������ͽ���catch

//�쳣��׽�ϸ�������ƥ�� ���������ʽ����ת��




void main()
{
	try
	{
		throw 'Z';
	}
	catch (int e)
	{
		cout << "����int�����쳣" << endl;
	}
	catch (...)
	{
		cout << " δ֪ �����쳣" << endl;
	}

	system("pause");
}




void divide(int x, int y)
{
	if (y == 0)
	{
		throw x; //�׳� int ���� �쳣
	}

	cout << "divide ���:" << x/y << endl;

}


void myDivide(int x, int y)
{
	try
	{
		divide(x, y);
	}
	catch (...)
	{
		cout << "�ҽ�����divide���쳣������û�д����������ף�" << endl;
		throw;
	}
}

void main21()
{
	try
	{
		//divide(10, 2);
		myDivide(100, 0);// �쳣�ǿ纯���ģ�����������
	}

	catch (int e)
	{
		cout << e << "�����" << endl;
	}
	catch (...)
	{
		cout << "����δ֪�����쳣" << endl;
	}



	system("pause");
}