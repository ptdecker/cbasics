BIN = ../../bin
ODIR = obj
SUBDIRS = 
CC = cc
CFLAGS = -std=c99 -Wall -g -I.
LINT = splint
LINTFLAGS = +quiet +skip-sys-headers +charint -preproc 
DEPS =
_OBJ = any.o equivloop.o fastbitcount.o htoi.o invert.o tolower.o rightrot.o setbits.o squeeze.o typelimits.o
_BIN = any equivloop fastbitcount htoi invert tolower rightrot setbits squeeze typelimits

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

any: $(ODIR)/any.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

equivloop: $(ODIR)/equivloop.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

fastbitcount: $(ODIR)/fastbitcount.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

htoi: $(ODIR)/htoi.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

invert: $(ODIR)/invert.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

tolower: $(ODIR)/tolower.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

rightrot: $(ODIR)/rightrot.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

setbits: $(ODIR)/setbits.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

squeeze: $(ODIR)/squeeze.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

typelimits: $(ODIR)/typelimits.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

$(ODIR)/%.o: %.c $(DEPS)
	mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(LINT) $(LINTFLAGS) $<
