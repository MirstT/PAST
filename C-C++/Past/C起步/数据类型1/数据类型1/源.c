#include<stdio.h>
int main()
{
	int i = 10;
	printf("%d\n", sizeof(i));
	short a;
	printf("%d\n", sizeof(a));
	long b;
	printf("%d\n", sizeof(b));
	long long c;
	printf("%d\n", sizeof(c));


	unsigned int d;
	unsigned short e=0xffff;
	e += 1;
	printf("\n\n\n%d\n\n\n\n", e);
	unsigned long f;
	unsigned long long g;

	unsigned short ff =5;
	ff -= 8;
	printf("\n\n\n%d\n\n\n\n", ff);

	int i1 = 0x12345678;
	ff = i1;
	printf("\n\n\n%x\n\n\n\n", ff);


	short abc1 = -2;
	i1 = abc1;
	printf("\n\n\n%x\n\n\n\n", i1);
	printf("\n\n\n%d\n\n\n\n", i1);


	unsigned short abc2 = 0;
	abc2 -= 1;
	printf("\n\n\n%x\n\n\n\n", abc2);
	printf("\n\n\n%d\n\n\n\n", abc2);

	int ccc = 0x12345678;
	printf("%p\n", &ccc);
			


	signed int r; /*int r;*/
	

	return 0;
}