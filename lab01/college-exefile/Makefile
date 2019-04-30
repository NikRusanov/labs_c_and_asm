BUILDDIR        = $(CURDIR)/build
ARTIFACT_ID     = exedump

SUBDIRS         = src
FILES           = main.c

export OBJFILE  = module.o
export CFLAGS  += --std=c99 -O2 -I"$(CURDIR)/include"
export CC       = gcc -c
export LD       = gcc
export LINK     = ld
export MAKE_OPTS= -s

OBJ_FILES       = $(patsubst %.c,$(BUILDDIR)/%.o,$(FILES))
CFILE           = $(patsubst $(BUILDDIR)/%.o,%.c,$(@))

.PHONY: all clean $(SUBDIRS)

all: $(ARTIFACT_ID)

$(ARTIFACT_ID): $(SUBDIRS) $(OBJ_FILES)
	@echo "ld  $(ARTIFACT_ID)"
	@$(LD) -o $(ARTIFACT_ID) $(OBJ_FILES) $(patsubst %,$(BUILDDIR)/%/$(OBJFILE),$(SUBDIRS))
	@echo "Build OK"

$(OBJ_FILES):
	@echo "cc  $(CFILE)"
	@$(CC) -o $(@) $(CFLAGS) $(CFILE)

$(SUBDIRS):
	@echo "Compiling source files"
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(BUILDDIR)/src
	@$(MAKE) $(MAKE_OPTS) -C src all BUILDDIR=$(BUILDDIR)/src

clean:
	@echo "Cleaning binaries"
	@-rm -rf $(BUILDDIR)
	@-rm -rf $(ARTIFACT_ID)
	@echo "Clean OK"
