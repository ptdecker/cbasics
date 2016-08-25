BIN = ../../bin
ODIR = obj
SUBDIRS = 
CC = cc
CFLAGS = -std=c99 -Wall -g -I.
LINT = splint
LINTFLAGS = +quiet +skip-sys-headers +charint +posixlib -preproc
DEPS =
_OBJ = bfree.o calloc.o calloc2.o mincat.o mincat2.o minstdio.o minstdiotest.o stdiobits.o \
       minstdio0.o minstdio1.o fseektest.o fileinfo.o
_BIN = bfree calloc calloc2 mincat mincat2 minstdiotest stdiobits fseektest fileinfo

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
	rm -r $(ODIR) $(_BIN)
	rm minstdio.o minstdio0.o minstdio1.o

bfree: $(ODIR)/bfree.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

calloc: $(ODIR)/calloc.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

calloc2: $(ODIR)/calloc2.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

mincat: $(ODIR)/mincat.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

mincat2: $(ODIR)/mincat2.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

minstdiotest: $(ODIR)/minstdiotest.o minstdio.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

stdiobits: $(ODIR)/stdiobits.o minstdio0.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

fseektest: $(ODIR)/fseektest.o minstdio1.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

fileinfo: $(ODIR)/fileinfo.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

$(ODIR)/%.o: %.c $(DEPS)
	mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(LINT) $(LINTFLAGS) $<
