BIN = ../../bin
ODIR = obj
SUBDIRS = rpncalc4-03 rpncalc4-04 rpncalc4-05 rpncalc4-06 rpncalc4-10 rpncalc4-11
CC = cc
CFLAGS = -std=c99 -Wall -g -I.
LINT = splint
LINTFLAGS = +quiet +skip-sys-headers +charint -preproc
DEPS =
_OBJ = atof.o itoarecursive.o reverserecursive.o singlegetch.o strrindex.o swapmacro.o \
       ungets.o ungetseof.o
_BIN = atof itoarecursive reverserecursive singlegetch strrindex swapmacro \
       ungets ungetseof

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

atof: $(ODIR)/atof.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

itoarecursive: $(ODIR)/itoarecursive.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

reverserecursive: $(ODIR)/reverserecursive.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

singlegetch: $(ODIR)/singlegetch.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

strrindex: $(ODIR)/strrindex.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

swapmacro: $(ODIR)/swapmacro.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

ungets: $(ODIR)/ungets.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

ungetseof: $(ODIR)/ungetseof.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

$(ODIR)/%.o: %.c $(DEPS)
	mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(LINT) $(LINTFLAGS) $<
