#include "add_value.h"

long add_value(long a, long b)
{
	register long result;
	__asm__ __volatile__
	(
		"lea (%[a], %[b]), %[result]\n"
		: [result] "=r" (result)
		: [a] "r" (a), [b] "r"(b)
		:
	);
	
	return result;
}
