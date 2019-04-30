#include <stdio.h>

#include "add_value.h"

int main()
{
	long a, b;
	printf("Input a, b\n");
	scanf("%ld %ld", &a, &b);
	
	long result = add_value(a, b);
	printf("Result: %ld\n", result);

	return 0;
}