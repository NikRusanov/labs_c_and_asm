.text

.type add_value, @function
.globl add_value

add_value:
	lea (%rsi,%rdi), %rax
	ret


