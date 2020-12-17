#include<iostream>
using namespace std;


class BadSrcType {};
class BadDesType{};
class BadProcessType
{
public:
	BadProcessType()
	{
		cout << "BadProcessType���캯��do\n";
	}
	BadProcessType(const BadProcessType &obj)
	{
		cout << "BadProcessType copy���캯��do\n";
	}
	~BadProcessType()
	{
		cout << "BadProcessType��������do\n";
	}
};


// throw ����� �����쳣

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
		cout << "��ʼBadProcessType�����쳣" << endl;
		throw BadProcessType();  //��ѣ�������������������
	}
	if (*from == 'b')
	{
		cout << "��ʼBadProcessType�����쳣" << endl;
		throw &(BadProcessType());  //�ᱻ�������������Ұָ��
	}
	if (*from == 'c')
	{
		cout << "��ʼBadProcessType�����쳣" << endl;
		throw new BadProcessType; //���ᱻ���� ����Ҫdelete�ֶ��ͷţ�������
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

	catch (int e) //e ����д��Ҳ���Բ�д
	{
		cout << e << "int �����쳣" << endl;
	}

	catch (const char *e)
	{
		cout << e << " char*�����쳣" << endl;
	}
	//====================================================
	catch (BadSrcType e)
	{
		cout<< " BadSrcType�����쳣" << endl;
	}

	catch (BadDesType e)
	{
		cout<< " BadDesType�����쳣" << endl;
	}

	// �����쳣��ʱ�� ʹ��һ���쳣��������copy�����쳣����
	/*catch (BadProcessType e)
	{
		cout << "BadProcessType�����쳣" << endl;
	}*/

	// ʹ�����õĻ� ��ʹ��throwʱ����Ǹ�����
	catch (BadProcessType &e)//��ѣ�����������������������������������������������������������������������������������������
	{
		cout << "BadProcessType�����쳣" << endl;
	}

	//ָ����Ժ�����/Ԫ�� д��һ�� ������&Ԫ�ز���д��һ��
	catch (BadProcessType *e) //���Ƽ�ʹ�ã�������
	{
		cout << "BadProcessType�����쳣" << endl;
	}
	//==========================================================
	catch (...)
	{
		cout << "δ֪�����쳣" << endl;
	}

	//==================================================

	/*if (ret != 0)
	{
	switch (ret)
	{
	case 1:
	printf("Դbuf����\n");
	break;
	case 2:
	printf("Ŀ��buf����\n");
	break;
	case 3:
	printf("copy���̳���\n");
	break;
	default:
	printf("δ֪����!\n");
	break;
	}
	}*/

	cout << endl << "buf2:" << buf2 << endl;

	system("pause");
	return;
}




//// throw char* �����쳣
//
//void my_strcpy(char *to, char *from)
//{
//
//
//	if (from == NULL)
//	{
//		throw "Դbuf����";
//	}
//
//	if (to == NULL)
//	{
//		throw "Ŀ��buf����";
//	}
//	if (*from == 'a')
//	{
//		throw "copy���̳���";
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
//	catch (int e) //e ����д��Ҳ���Բ�д
//	{
//		cout << e<<"int �����쳣" << endl;
//	}
//
//	catch (const char *e)
//	{
//		cout << e << " char*�����쳣" << endl;
//	}
//
//	catch (...)
//	{
//		cout << "δ֪�����쳣" << endl;
//	}
//
//	/*if (ret != 0)
//	{
//		switch (ret)
//		{
//		case 1:
//			printf("Դbuf����\n");
//			break;
//		case 2:
//			printf("Ŀ��buf����\n");
//			break;
//		case 3:
//			printf("copy���̳���\n");
//			break;
//		default:
//			printf("δ֪����!\n");
//			break;
//		}
//	}*/
//
//	cout << endl << "buf2:" << buf2 << endl;
//
//	system("pause");
//	return;
//}
//��ͳ�Ĵ��������
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
//			printf("Դbuf����\n");
//			break;
//		case 2:
//			printf("Ŀ��buf����\n");
//			break;
//		case 3:
//			printf("copy���̳���\n");
//			break;
//		default:
//			printf("δ֪����!\n");
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