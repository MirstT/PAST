//#include<iostream>
//using namespace std;
//
//
//template<typename T> //template<typename T,typename T2>
//int mySort(T *array, int size)
//{
//	int i, j;
//	T tmp;
//	if (array == NULL)
//	{
//		return -1;
//	}
//
//	for (i = 0; i < size; i++)
//	{
//		for (j = i + 1; j < size; j++)
//		{
//			if (array[i] < array[j])
//			{
//				tmp = array[i];
//				array[i] = array[j];
//				array[j] = tmp;
//			}
//		}
//	}
//
//	return 0;
//}
//
//template<typename T>
//int myPrint(T *array, int size)
//{
//	int i = 0;
//	for (i = 0; i < size; i++)
//	{
//		cout << array[i] << " ";
//	}
//
//
//	return 0;
//}
//
//
//void main()
//{
//	{int myarray[] = { 11,22,44,232,3,1,5,9 };
//
//
//	int size = sizeof(myarray) / sizeof(*myarray);
//	mySort(myarray, size);
//
//	printf("ÅÅÐòÖ®ºó\n");
//
//	myPrint(myarray, size); }
//
//
//	{
//		char buf[] = "aafff3232dddf34ddss";
//		int len = strlen(buf);
//
//		mySort(buf, len);
//		cout << endl;
//		myPrint<char>(buf, len);
//	}
//
//
//	system("pause");
//}