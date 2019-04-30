ASM         = as
LD          = ld
LDFLAGS     = --oformat binary -Ttext 7c00
QEMU        = qemu-system-i386
QEMUFLAGS   = -drive format=raw,index=0,if=floppy,file=boot.img
QEMUGDB     = -gdb tcp:localhost:9090 -S

.PHONY: all qemu clean gdb

all: boot.img

clean:
	@-$(RM) *.o boot.code boot.img

qemu: all
	$(QEMU) $(QEMUFLAGS)

gdb: all
	$(QEMU) $(QEMUFLAGS) $(QEMUGDB)

boot.img: boot.code
	@dd if=boot.code of=boot.img
	@echo -ne "\x55\xaa" | dd seek=510 bs=1 of=boot.img

boot.code:  boot.o
	@$(LD) $(LDFLAGS) -o boot.code boot.o

boot.o: boot.s
	@$(ASM) -o boot.o boot.s

