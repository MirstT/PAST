#include<stdio.h>
int main()
{
	int i;
	i = 5 / 2;
	printf("%d\n", i);
	double f,a,b,c,e=5.0,g=5;
	f = 5/ 2;
	a = 5.0 / 2;
	b = 5 / 2.0;
	c = 5.0 / 2.0;
	e = e / 2;
	g = g / 2;

	printf("%f\n", f);
	printf("%f\n", a);
	printf("%f\n", b);
	printf("%f\n", c);
	printf("%f\n", e);
	printf("%f\n", g);


	printf("%d\n", sizeof(float));
	printf("%d\n", sizeof(double));

	return 0;

}