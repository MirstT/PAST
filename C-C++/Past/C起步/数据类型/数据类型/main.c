#include<stdio.h>
#define MAX 1000
#define STRING "hello world\n"

int main() {
	int i;
	i = 100;
	i = 10;
	printf("hello world\n");
	printf("%d\n", 10);
	printf("%d\n", MAX);
	printf("%d\n", i);
	const int a = 333;
	printf("%d\n", a);
	printf(STRING);
	const char*str = "hello c\n";
	printf(str);

	return 0;
}