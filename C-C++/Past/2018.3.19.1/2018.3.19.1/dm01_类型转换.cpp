#include<iostream>
using namespace std;


//const ������pָ����ڴ�� ���ֻ������
void printBuf(const char*p)
{

	/*p[0] = 'z';*/
	char *p1 = NULL;;
	//��ֻ������ȥ��
	p1 = const_cast<char*>(p);

	p1[0] = 'Z';
	cout << p << endl;

}





void main()
{
	char*pp = (char*)"233333";
	char buf[] = "aaaaaaaaaa333333";
	char *p = const_cast<char *>("23333333333333"); //û���ڴ�ռ䣬�����޷�ȥ��ֻ������
	printBuf(buf);
	//printBuf(p);
	//p[0] = 'Z';
	//cout << p << endl;

	system("pause");

}








class Tree{};

class Animal
{
public:
	virtual void cry() = 0;

};

class Dog :public Animal
{
public:
	virtual void cry()
	{
		cout << "����" << endl;
	}
	void doHome()
	{
		cout << "����" << endl;
	}
};


class Cat :public Animal
{
public:
	virtual void cry()
	{
		cout << "����" << endl;
	}
	void doThing()
	{
		cout << "ץ����" << endl;
	}

};




void playObj(Animal *base)
{
	base->cry();
	//��ʶ���������

	//dynamic_cast ����ʱ����ʶ��

	Dog *pDog = dynamic_cast<Dog*>(base);
	if (pDog != NULL)
	{
		pDog->doHome(); //�ù� ���Լ� ���еĹ���
	}

	Cat *pCat = dynamic_cast<Cat*>(base);//�������===�� ������� ����ת��
	if (pCat != NULL) //                     ������ת��С��
	{
		pCat->doThing();
	}
	
}

void main12()
{
	Dog d1;
	Cat c1;

	Animal *pBase = NULL;
	/*Animal Base;*/

	pBase = &d1;

	pBase = static_cast<Animal*>(&d1);
	pBase = reinterpret_cast<Animal*>(&d1);


	{
		Tree t1;
		/*pBase = static_cast<Animal*>(&t1);*/
		pBase = reinterpret_cast<Animal*>(&t1);
		/*pBase = reinterpret_cast<Animal>(t1);*/



	}

	playObj(&d1);
	playObj(&c1);

	system("pause");
}

void main11()
{
	double dpi = 3.1415926;

	int num = dpi;
	int num1 = (int)dpi;
	int num2 = static_cast<int>(dpi);
	
	cout << num << endl;//c������ ��ʽ����ת�� �ĵط� ����ʹ�� static_cast<>() ��������ת�� �ɱ���warning
	cout << num1 << endl; //C����ת��
	cout << num2 << endl;//��̬����ת��  ����ʱc++�������������ͼ��
	cout << "=============================================" << endl;



	//cha*===> int *
	char *p1 =const_cast<char*>( "hello.....itcast");
	int *p2 = NULL;
	//p2 = static_cast<int *>(p1);

	p2 = reinterpret_cast<int *>(p1);

	cout <<"p1:"<< p1 << endl;//%s
	cout << "p2:" << p2 << endl;//%d




	system("pause");
}