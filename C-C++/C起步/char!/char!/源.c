#include<stdio.h>
int mainww()
{
	char c;
	c = 'a';
	printf("%c\n", c);
	printf("%d\n", c);

	c = 4;
	printf("%c\n", c);
	printf("%d\n", c);

	c = '4';
	printf("%c\n", c);
	printf("%d\n", c);

	c = 'A';
	c += 1;
	printf("%c\n", c);
	printf("%d\n", c);

	printf("%d\n", sizeof(c));
	return 0;
}
int main()
{
	char c;
	c = '\a';
	printf("%c\n", c);
	printf("%d\n", c);

	printf("%c\n", c);
	c = '\b';
	printf("%c\n", c);
	printf("%d\n", c);

	c = '\b';
	printf("%c\n", c);
	printf("%d\n", c);
	c = '\b';
	printf("%d", c); printf("%d", c); printf("%d", c); printf("%d", c);	printf("%d", c);;

	c = '\r';
	printf("%c", c);
	printf("%d", c);
	c = '\b';
	printf("%d", c);

	c = 'a';
	printf("%c", c);
	c = '\t';
	printf("%c", c);
	c = 'b';
	printf("%c", c);

	c = '\\';
	printf("%c", c);
	c = '\'';
	printf("%c", c);
	c = '\"';
	printf("%c", c);
	c = '\?';
	printf("%c", c);

	char x = 0;
	unsigned char y = 0;
	y=y- 1;
	x = y;
	printf("%d\n", y);
	printf("%d\n",x);

	y = 127;
	y = y + 5;
	x = y;
	printf("%d\n", y);
	printf("%d\n", x);


	return 0;
}