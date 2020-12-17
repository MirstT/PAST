#include<iostream>
using namespace std;


class BadSrcType {};
class BadDesType{};
class BadProcessType
{
public:
	BadProcessType()
	{
		cout << "BadProcessType构造函数do\n";
	}
	BadProcessType(const BadProcessType &obj)
	{
		cout << "BadProcessType copy构造函数do\n";
	}
	~BadProcessType()
	{
		cout << "BadProcessType析构函数do\n";
	}
};


// throw 类对象 类型异常

void my_strcpy(char *to, char *from)
{


	if (from == NULL)
	{
		throw BadSrcType();
	}

	if (to == NULL)
	{
		throw BadDesType();
	}
	if (*from == 'a')
	{
		cout << "开始BadProcessType类型异常" << endl;
		throw BadProcessType();  //最佳！！！！！！！！！！
	}
	if (*from == 'b')
	{
		cout << "开始BadProcessType类型异常" << endl;
		throw &(BadProcessType());  //会被析构，变成垃圾野指针
	}
	if (*from == 'c')
	{
		cout << "开始BadProcessType类型异常" << endl;
		throw new BadProcessType; //不会被析构 但需要delete手动释放！！！！
	}

	while (*to++ = *from++);
}

void main()
{
	char buf1[] = "a233333";
	char buf2[1024] = { 0 };

	try
	{
		my_strcpy(buf2, buf1);
	}

	catch (int e) //e 可以写，也可以不写
	{
		cout << e << "int 类型异常" << endl;
	}

	catch (const char *e)
	{
		cout << e << " char*类型异常" << endl;
	}
	//====================================================
	catch (BadSrcType e)
	{
		cout<< " BadSrcType类型异常" << endl;
	}

	catch (BadDesType e)
	{
		cout<< " BadDesType类型异常" << endl;
	}

	// 接收异常的时候 使用一个异常变量，则copy构造异常变量
	/*catch (BadProcessType e)
	{
		cout << "BadProcessType类型异常" << endl;
	}*/

	// 使用引用的话 会使用throw时候的那个对象，
	catch (BadProcessType &e)//最佳！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
	{
		cout << "BadProcessType类型异常" << endl;
	}

	//指针可以和引用/元素 写在一起 但引用&元素不能写在一起
	catch (BadProcessType *e) //不推荐使用！！！！
	{
		cout << "BadProcessType类型异常" << endl;
	}
	//==========================================================
	catch (...)
	{
		cout << "未知类型异常" << endl;
	}

	//==================================================

	/*if (ret != 0)
	{
	switch (ret)
	{
	case 1:
	printf("源buf出错\n");
	break;
	case 2:
	printf("目的buf出错\n");
	break;
	case 3:
	printf("copy过程出错！\n");
	break;
	default:
	printf("未知错误!\n");
	break;
	}
	}*/

	cout << endl << "buf2:" << buf2 << endl;

	system("pause");
	return;
}




//// throw char* 类型异常
//
//void my_strcpy(char *to, char *from)
//{
//
//
//	if (from == NULL)
//	{
//		throw "源buf出错";
//	}
//
//	if (to == NULL)
//	{
//		throw "目的buf出错";
//	}
//	if (*from == 'a')
//	{
//		throw "copy过程出错";
//	}
//
//	while (*to++ = *from++);
//}
//
//void main()
//{
//	char buf1[] = "a233333";
//	char buf2[1024] = { 0 };
//
//	try
//	{
//		my_strcpy(buf2, buf1);
//	}
//
//	catch (int e) //e 可以写，也可以不写
//	{
//		cout << e<<"int 类型异常" << endl;
//	}
//
//	catch (const char *e)
//	{
//		cout << e << " char*类型异常" << endl;
//	}
//
//	catch (...)
//	{
//		cout << "未知类型异常" << endl;
//	}
//
//	/*if (ret != 0)
//	{
//		switch (ret)
//		{
//		case 1:
//			printf("源buf出错\n");
//			break;
//		case 2:
//			printf("目的buf出错\n");
//			break;
//		case 3:
//			printf("copy过程出错！\n");
//			break;
//		default:
//			printf("未知错误!\n");
//			break;
//		}
//	}*/
//
//	cout << endl << "buf2:" << buf2 << endl;
//
//	system("pause");
//	return;
//}
//传统的错误处理机制
//int my_strcpy1(char *to, char *from)
//{
//
//
//	if (from == NULL)
//	{
//		return 1;
//	}
//
//	if (to == NULL)
//	{
//		return 2;
//	}
//	if (*from == 'a')
//	{
//		return 3;
//	}
//
//	while (*to++ = *from++);
//
//	return 0;
//}
//
//void main41()
//{
//	int ret = 0;
//	char buf1[] = "233333";
//	char buf2[1024] = {0};
//
//	ret = my_strcpy(buf2, buf1);
//	if (ret != 0)
//	{
//		switch (ret)
//		{
//		case 1:
//			printf("源buf出错\n");
//			break;
//		case 2:
//			printf("目的buf出错\n");
//			break;
//		case 3:
//			printf("copy过程出错！\n");
//			break;
//		default:
//			printf("未知错误!\n");
//			break;
//		}
//	}
//	cout << endl<<"buf2:"<<buf2<<endl;
//
//
//
//	system("pause");
//	return;
//}