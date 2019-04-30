CFLAGS=
CC=gcc -c $(CFLAGS)
AS=gcc -c
LD=gcc
DA=objdump -D

OBJFILES=main.o add_value.o
CFILE=$(patsubst %.o, %.c, $(@))
ASMFILE=$(patsubst %.o, %.s, $(@))
OBJFILE=$(patsubst %.lst, %.o, $(@))
LISTINGS=$(patsubst %.o, %.lst, $(OBJFILES))

all: test.exe

clean:
	@-rm -f *.o *.exe *.lst

listing: $(LISTINGS)

add_value.o: add_value.c add_value.h
	@echo "CC  $(@)"
	@$(CC) $(CFILE) -o $(@)

main.o: main.c add_value.h
	@echo "CC  $(@)"
	@$(CC) $(CFILE) -o $(@)

test.exe: $(OBJFILES)
	@echo "LD  $(@)"
	@$(LD) $(OBJFILES) -o $(@)

$(LISTINGS): $(OBJFILES)
	@echo "DA $(@)"
	@$(DA) $(OBJFILE) >$(@)
