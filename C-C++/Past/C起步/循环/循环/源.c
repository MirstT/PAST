#include<stdio.h>
//int main01()
//{
//	int i = 1;
//	while (i)
//	{
//		printf("Please input number: ");
//		scanf("%d", &i);
//		if (i == 9)
//			continue;
//		if (i == 6)
//			break;
//		printf("Helo World!\n");
//	}
//	printf("End!\n");
//	return 0;
//}
//int main02()
//{
//	for (int i = 1; i < 10; i++)
//	{
//		for (int j = 1; j < 10; j++)
//		{
//			printf("%d\t", i*j);
//		}
//		printf("\n");
//	}
//	return 0;
//}
int main()
{
	for (int i = 1; i < 11; i++)
	{
		for (int j = 0; j < 10-i; j++)
			printf(" ");
		for (int j = 0; j < 2 * i - 1; j++)
			printf("*");
		printf("\n");
	}
	return 0;
}
