#include<iostream>
using namespace std;


//const 修饰让p指向的内存空 变成只读属性
void printBuf(const char*p)
{

	/*p[0] = 'z';*/
	char *p1 = NULL;;
	//把只读属性去掉
	p1 = const_cast<char*>(p);

	p1[0] = 'Z';
	cout << p << endl;

}





void main()
{
	char*pp = (char*)"233333";
	char buf[] = "aaaaaaaaaa333333";
	char *p = const_cast<char *>("23333333333333"); //没有内存空间，还是无法去除只读属性
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
		cout << "汪汪" << endl;
	}
	void doHome()
	{
		cout << "看家" << endl;
	}
};


class Cat :public Animal
{
public:
	virtual void cry()
	{
		cout << "喵喵" << endl;
	}
	void doThing()
	{
		cout << "抓老鼠" << endl;
	}

};




void playObj(Animal *base)
{
	base->cry();
	//能识别子类对象

	//dynamic_cast 运行时类型识别

	Dog *pDog = dynamic_cast<Dog*>(base);
	if (pDog != NULL)
	{
		pDog->doHome(); //让狗 做自己 特有的工作
	}

	Cat *pCat = dynamic_cast<Cat*>(base);//父类对象===》 子类对象 向下转型
	if (pCat != NULL) //                     把老子转成小子
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
	
	cout << num << endl;//c语言中 隐式类型转换 的地方 均可使用 static_cast<>() 进行类型转换 可避免warning
	cout << num1 << endl; //C类型转换
	cout << num2 << endl;//静态类型转换  编译时c++编译器会做类型检查
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