BIN = ../../bin
ODIR = obj
SUBDIRS = 
CC = cc
CFLAGS = -std=c99 -Wall -g -I.
LINT = splint
LINTFLAGS = -compdef +quiet +skip-sys-headers +charintliteral +charint -shadow -preproc -mustfreeonly -temptrans -nullret -nullpass -nullstate +posixlib
DEPS =
_OBJ = bfree.o calloc.o calloc2.o mincat.o mincat2.o minstdio3.o
_BIN = bfree calloc calloc2 mincat mincat2 minstdio3

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

.PHONY: all clean

all: $(_BIN)
	@for i in $(SUBDIRS); do \
		cd $$i; \
		make all; \
		cd ..; \
	done

clean:
	@for i in $(SUBDIRS); do \
		cd $$i; \
		make clean; \
		cd ..; \
	done
	rm -rv $(ODIR) $(_BIN)

bfree: $(ODIR)/bfree.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

calloc: $(ODIR)/calloc.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

calloc2: $(ODIR)/calloc2.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

mincat: $(ODIR)/mincat.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

mincat2: $(ODIR)/mincat2.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

minstdio3: $(ODIR)/minstdio3.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

$(ODIR)/%.o: %.c $(DEPS)
	mkdir -pv $(ODIR)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(LINT) $(LINTFLAGS) $<