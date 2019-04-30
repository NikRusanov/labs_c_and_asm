FILES           = endian.c msdos.c
OBJFILES        = $(patsubst %.c,$(BUILDDIR)/%.o,$(FILES))
MODULE          = $(BUILDDIR)/$(OBJFILE)
CFILE           = $(patsubst $(BUILDDIR)/%.o,%.c,$(@))

.PHONY: all

all: $(MODULE)

$(MODULE): $(OBJFILES)
	@echo "ld  $(notdir $@)"
	@$(LINK) -o $(MODULE) -r $(OBJFILES)

$(OBJFILES):
	@echo "cc  $(CFILE)"
	@$(CC) -o $(@) $(CFLAGS) $(CFILE)
