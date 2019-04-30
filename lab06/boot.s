.code16
.section .text
.globl _start

# CODE
_start:
	# Initialize segments
	cld
	xor         %ax, %ax
	mov         %ax, %ds
	mov         %ax, %es

	# Get VESA information
	mov         $0x8000, %di
	mov         $0x4f00, %ax
	int         $0x10

	# Check VESA support
	mov         %di, %si
	lodsw
	cmp         $0x4556, %ax # ax = 'VE'
	jne         10f
	lodsw
	cmp         $0x4153, %ax # ax = 'SA'
	jne         10f
	lodsw
	cmp         $0x200, %ax
	jae         20f
	
10:
	# Output error message
	mov         $no_vbe, %si
	call        out_text
	jmp         1000f

20:
	# Now information about VBE is stored into 512-byte buffer at 0x0:0x8000
	lds         %es:0x0e(%di), %si
	mov         $0x8200, %di
	
	# Scan basic and extended modes
	call        scan_modes
	jnz         20f
	call        scan_modes
	jnz         20f

	# Output error message
	xor         %ax, %ax
	mov         %ax, %ds
	mov         $no_mode, %si
	call        out_text
	jmp         1000f

20:
	# Mode was found, cx=mode number
	# Useful addresses:
	#   $0x8208 - segment address of window A
	#   $0x820a - address of window B
	#   $0x820c - window function
	#   $0x8210 - number of bytes per line

	# Set current video mode
	xor         %ax, %ax
	mov         %ax, %ds
	mov         %cx, %bx
	mov         $0x4f02, %ax
	int         $0x10
	xor         %dx, %dx
	mov         %ds:(0x8206), %ax
	divw        %ds:(0x8204)
	mov         %ax, %ds:(bank_gran)

        # Draw some stuff
	xor         %bx, %bx
	mov         $0x7fe0, %ax
#	mov         $51, %bx
30:
	mov         %bx, %dx
	call        put_pixel
	inc         %bx
	cmp         $480, %bx
	jb          30b

	# Do infinite loop
1000:	jmp         1000b

# Scan modes
# Input:
#   ds:si - Address of list of modes
#   es:di - Address of buffer to store information
# Output:
#   ZF = 0 if mode not found
#   ZF = 1 if mode was found, cx = number of mode
# Modifies:
#   ax, si, cx
scan_modes:
1:
	mov         $0x4f01, %ax
	mov         %ds:(%si), %cx
	add         $2, %si
	cmp         $0xffff, %cx
	jnz         2f
	ret         # zf = 1
	
	# Get inforrmation about mode
2:
	int         $0x10
	mov         %ds:0x12(%di), %ax
	cmp         $640, %ax
	jne         1b
	mov         %ds:0x14(%di), %ax
	cmp         $480, %ax
	jne         1b
	mov         %ds:0x19(%di), %al
	cmp         $15, %al
	jne         1b
	mov         %ds:0x1b(%di), %al
	cmp         $6, %al
	jne         1b
	dec         %al # zf = 0
	ret

# Input:
#   bx = x
#   dx = y
#   ax = color
# Output:
#   none
# Modifies:
#   none
put_pixel:
	push       %es
	push       %bx
	push       %dx
	push       %ax
	
	mov        %ds:(0x8208), %ax
	mov        %ax, %es
	shl        $1, %bx # bx = x*2
	mov        %ds:(0x8210), %ax # ax = bytes_per_row
	mul        %dx   # dx:ax = y*bytes_per_row
	add        %ax, %bx
	adc        $0, %dx # dx:bx = y*bytes_per_row + x*2 = offset
	cmp        %ds:(curr_bank), %dx
	je         1f

	# Move window
	push       %bx
	xor        %bx, %bx # setup window A
	mov        %dx, %ds:(curr_bank) # store new bank
	mov        %dx, %ax
	mulw       (bank_gran)
	mov        %ax, %dx
	lcall      %ds:(0x820c)
	pop        %bx # bx = offset

1:
	pop        %ax # restore color
	mov        %ax, %es:(%bx) # store pixel
	
	pop        %dx
	pop        %bx
	pop        %es
	ret

# Output text
# Input:
#   ds:si = C-string of buffer to output
# Output:
#   none
# Modifies:
#   ax, ds, es, di
out_text:
	mov         $0xb800, %ax
	mov         %ax, %es
	xor         %di, %di
	
	xor         %ax, %ax
	mov         $2000, %cx
	rep         stosw
	
	xor         %di, %di
	mov         $0x1e, %ah
1:
	lodsb
	test        %al, %al
	jz          2f
	stosw
	jmp         1b
2:
	ret

# DATA
_data:
curr_bank:      .word       0xffff
bank_gran:      .word       0x0000
no_vbe:		.asciz      "VBE2 not supported!"
no_mode:	.asciz      "Video mode not found!"
