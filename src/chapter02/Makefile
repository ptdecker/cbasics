BIN = ../../bin
ODIR = obj
SUBDIRS = 
CC = cc
CFLAGS = -std=c99 -Wall -g -I.
LINT = splint
LINTFLAGS = -compdef +quiet +skip-sys-headers +charintliteral +charint -shadow -preproc -mustfreeonly -temptrans -nullret -nullpass
DEPS =
_OBJ = any.o equivloop.o fastbitcount.o htoi.o invert.o lower.o rightrot.o setbits.o squeeze.o typelimits.o
_BIN = any equivloop fastbitcount htoi invert lower rightrot setbits squeeze typelimits

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

any: $(ODIR)/any.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

equivloop: $(ODIR)/equivloop.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

fastbitcount: $(ODIR)/fastbitcount.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

htoi: $(ODIR)/htoi.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

invert: $(ODIR)/invert.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

lower: $(ODIR)/lower.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

rightrot: $(ODIR)/rightrot.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

setbits: $(ODIR)/setbits.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

squeeze: $(ODIR)/squeeze.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

typelimits: $(ODIR)/typelimits.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

$(ODIR)/%.o: %.c $(DEPS)
	mkdir -pv $(ODIR)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(LINT) $(LINTFLAGS) $<