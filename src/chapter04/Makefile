BIN = ../../bin
ODIR = obj
SUBDIRS = rpncalc4-03 rpncalc4-04 rpncalc4-05 rpncalc4-06 rpncalc4-10 rpncalc4-11
CC = cc
CFLAGS = -std=c99 -Wall -g -I.
LINT = splint
LINTFLAGS = -compdef +quiet +skip-sys-headers +charintliteral +charint -shadow -preproc
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
	rm -rv $(ODIR) $(_BIN)

atof: $(ODIR)/atof.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

itoarecursive: $(ODIR)/itoarecursive.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

reverserecursive: $(ODIR)/reverserecursive.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

singlegetch: $(ODIR)/singlegetch.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

strrindex: $(ODIR)/strrindex.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

swapmacro: $(ODIR)/swapmacro.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

ungets: $(ODIR)/ungets.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

ungetseof: $(ODIR)/ungetseof.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

$(ODIR)/%.o: %.c $(DEPS)
	mkdir -pv $(ODIR)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(LINT) $(LINTFLAGS) $<