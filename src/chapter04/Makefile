BIN = ../../bin
ODIR = ../../obj
SUBDIRS = rpncalc4-03 rpncalc4-04 rpncalc4-05 rpncalc4-06 rpncalc4-10 rpncalc4-11
CC = cc
CFLAGS = -std=c99 -Wall -g -I.
LINT = splint
LINTFLAGS = -compdef +quiet +skip-sys-headers +charintliteral +charint -shadow -preproc
DEPS =
_OBJ = atof.o itoarecursive.o reverserecursive.o singlegetch.o strrindex.o swapmacro.o \
       ungets.o ungetseof.o

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

.PHONY: all clean

all: atof itoarecursive reverserecursive singlegetch strrindex swapmacro ungets ungetseof
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

itoarecursive: $(ODIR)/itoarecursive.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

reverserecursive: $(ODIR)/reverserecursive.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

singlegetch: $(ODIR)/singlegetch.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

strrindex: $(ODIR)/strrindex.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

swapmacro: $(ODIR)/swapmacro.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

ungets: $(ODIR)/ungets.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

ungetseof: $(ODIR)/ungetseof.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(LINT) $(LINTFLAGS) $<