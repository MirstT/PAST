//#define _CRT_SECURE_NO_WARNINGS
//#pragma warning(disable:4996)
#include<stdio.h>
#define STR "Hello"
#define ABC 100
int main01()
{
	char c = 't';
	volatile int i = 100;
	register int o = 100;
	printf("Hello World\n");
	printf("%s, %d, %c\n", STR ,ABC ,c);
	printf("%%\n");
	long l = 100;
	printf("%10ld\n", l);
	printf("%-10ld\n", l);
	printf("%010ld\n", l);
	putchar('\n');
	putchar('\n');
	putchar(67);
	putchar('A');
	putchar('\n');
	putchar('\n');
	putchar('\n');

	int a = 0, b = 0;

	scanf("%d", &a);
	scanf("%d", &b);

	printf("a+b=%d\n", a + b);
	return 0;
}

int main()
{
	char a, b;
	a = getchar();
	getchar();
	b = getchar();
	printf("a+b=%d\n", (a - '0') + (b - '0'));
	return 0;
}