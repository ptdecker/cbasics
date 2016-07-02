BIN = ../../bin
ODIR = obj
SUBDIRS =
CC = cc
CFLAGS = -std=c99 -Wall -g -I.
LINT = splint
LINTFLAGS = -compdef +quiet +skip-sys-headers +charintliteral +charint -shadow -preproc -mustfreeonly -temptrans -nullret -nullpass -nullstate
DEPS =
_OBJ = define.o getvars.o getword.o tablookup.o wordfreq.o wordxref.o
_BIN = define getvars getword tablookup wordfreq wordxref

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

define: $(ODIR)/define.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

getvars: $(ODIR)/getvars.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

getword: $(ODIR)/getword.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

tablookup: $(ODIR)/tablookup.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

wordfreq: $(ODIR)/wordfreq.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

wordxref: $(ODIR)/wordxref.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

$(ODIR)/%.o: %.c $(DEPS)
	mkdir -pv $(ODIR)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(LINT) $(LINTFLAGS) $<