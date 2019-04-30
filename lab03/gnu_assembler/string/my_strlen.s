.text

.type my_strlen, @function
.globl my_strlen

my_strlen:
	cld
	xor %al, %al
	mov $-1, %rcx
	repne; scasb
	not %rcx
	lea -1(%rcx), %rax
	ret

