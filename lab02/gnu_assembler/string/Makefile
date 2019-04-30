CFLAGS=-O2
CC=gcc -c $(CFLAGS)
AS=gcc -c
LD=gcc
DA=objdump -D 

OBJ_CFILES=main.o my_strend.o
OBJ_ASMFILES=my_strlen.o
OBJFILES=$(OBJ_CFILES) $(OBJ_ASMFILES)

CFILE=$(patsubst %.o, %.c, $(@))
ASMFILE=$(patsubst %.o, %.s, $(@))
OBJFILE=$(patsubst %.lst, %.o, $(@))
LISTINGS=$(patsubst %.o, %.lst, $(OBJFILES))

# Main targets
all: test.exe

clean:
	@-rm -f *.o *.exe *.lst

listing: $(LISTINGS)

# Dependencies
my_strlen.o: my_strlen.s

my_strend.o: my_strend.c strfunc.h

main.o: main.c strfunc.h

# Build rules
$(OBJ_CFILES):
	@echo "CC  $(@)"
	@$(CC) $(CFILE) -o $(@)

$(OBJ_ASMFILES):
	@echo "AS  $(@)"
	@$(AS) $(ASMFILE) -o $(@)

test.exe: $(OBJFILES)
	@echo "LD  $(@)"
	@$(LD) $(OBJFILES) -o test.exe

$(LISTINGS): $(OBJFILES)
	@echo "DA $(@)"
	@$(DA) $(OBJFILE) >$(@)
