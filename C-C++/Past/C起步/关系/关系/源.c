#include<stdio.h>
int main01()
{
	/*int i = 3 < 6, m = 3 > 6,a=10,b=30,h;
	printf("i=%d\n,m=%d\n", i,m);
	h = !(3 > 5 || (a = b));
	printf("%d\n", h);
	return 0;*/
	int a = 0, b = 0;
	char c;

	printf("Please input a:");
	scanf("%d", &a);

	getchar();

	printf("Please input opertor:");
	scanf("%c", &c);

	printf("Please input b:");
	scanf("%d", &b);

	if (c == '+')
	{
		printf("a+b=%d\n", a + b);
	}
	else if (c == '-')
	{
		printf("a-b=%d\n", a - b);
	}
	else if(c=='*')
	{
		printf("a*b=%d\n", a * b);

	}
	else if (c = '/')
	{
		if (b == 0)
		{
			printf("ERROR\n");
		}
		else
		{
			printf("a/b=%f\n", (float)a / b);
		}

	}
	else if (c == '%')
	{
		printf("a%%b=%d\n", a % b);
	}
	else
	{
		printf("ERROR!\n");
	}
	return 0;
}
int main()
{
	int a, b;
	char c;
	printf("Please input a:");
	scanf("%d", &a);
	getchar();
	printf("Please input opertor:");
	scanf("%c", &c);
	printf("Please input b:");
	scanf("%d", &b);
	switch (c)
	{
	case '+':
		printf("a+b=%d\n", a + b);
		break;
	case '-':
		printf("a-b=%d\n", a - b);
		break;
	case '*':
		printf("a*b=%d\n", a * b);
		break;
	case '/':
		switch (b)
		{
		case 0:
			printf("ERROR\n");
			break;
		default:
			printf("a/b=%f\n", (float)a / b);	
		}
		break;	
	default:
		printf("ERROR\n");
	}
	return 0;
}