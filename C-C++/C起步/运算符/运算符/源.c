#include<stdio.h>
int main01()
{
	int a = 10, b = 3;
	printf("a*b=%d\n", a*b);
	printf("a/b=%d\n", a/b);
	printf("a%b=%d\n", a%b);
	a += 3;
	a -= 3;
	a *= 3;
	a /= 3;
	a %= 3;
	a++;
	++a;
	a--;
	--a;

	return 0;

}
int main()
{
	int a = 3, b = 2;
	double c = (double)a / b;
	printf("%f\n", c);
	return 0;
}