BIN = ../../bin
ODIR = ../../obj
SUBDIRS = rpncalc
CC = cc
CFLAGS = -std=c99 -Wall -g -I.
LINT = splint
LINTFLAGS = -compdef +quiet +skip-sys-headers +charintliteral +charint -shadow -preproc
DEPS =
_OBJ = strrindex.o

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

.PHONY: all clean

all: strrindex
	@for i in $(SUBDIRS); do \
		echo "make all in $$i..."; \
		cd $$i; \
		make all; \
	done

clean:
	rm -f $(ODIR)/*.o

strrindex: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@
	$(LINT) $(LINTFLAGS) $@.c

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(LINT) $(LINTFLAGS) $<