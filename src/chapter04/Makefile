BIN = ../../bin
ODIR = ../../obj
SUBDIRS = rpncalc4-03 rpncalc4-04 rpncalc4-05
CC = cc
CFLAGS = -std=c99 -Wall -g -I.
LINT = splint
LINTFLAGS = -compdef +quiet +skip-sys-headers +charintliteral +charint -shadow -preproc
DEPS =
_OBJ = strrindex.o atof.o

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

.PHONY: all clean

all: atof strrindex
	@for i in $(SUBDIRS); do \
		echo "make all in $$i..."; \
		cd $$i; \
		make all; \
		cd ..; \
		rm -f $(ODIR)/*.o; \
	done

clean:
	rm -f $(ODIR)/*.o

atof: $(ODIR)/atof.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

strrindex: $(ODIR)/strrindex.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(LINT) $(LINTFLAGS) $<