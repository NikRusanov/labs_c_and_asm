#include "strfunc.h"

#ifdef __cplusplus
extern "C"
{
#endif

	char *my_strend(char *str)
	{
		register char *result;
		__asm__ __volatile__
		(
			"cld\n"
			"xor %%al, %%al\n"
			"mov $-1, %%rcx\n"
			"repne; scasb\n"
			"lea -1(%%rdi), %[result]\n"
			: [result] "=A" (result)
			: "D" (str)
			: "%rcx"
		);
	
		return result;
	}

#ifdef __cplusplus
}
#endif