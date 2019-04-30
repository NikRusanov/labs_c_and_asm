#include <stdio.h>

#include "strfunc.h"

int main()
{
	char *p;
	char str[64];
	
	printf("Please enter string:\n");
	fgets(str, sizeof(str)-1, stdin);
	str[sizeof(str)-1] = '\0';
	printf("You entered: %s\n", str);
	printf("String dump:\n");
	for (p=str; *p != '\0'; ++p)
		printf("%02x ", *p);
	printf("\n");
	printf("Length of string: %d\n", my_strlen(str));
	printf("Start of string: %p\n", str);
	printf("End of string: %p\n", my_strend(str));

	return 0;
}
