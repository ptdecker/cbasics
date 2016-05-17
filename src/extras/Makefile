BIN = ../../bin
ODIR = obj
SUBDIRS = rpncalc
CC = cc
CFLAGS = -std=c99 -Wall -g -I.
LINT = splint
LINTFLAGS = -compdef +quiet +skip-sys-headers +charintliteral +charint -shadow -preproc
DEPS =
_OBJ = makebigline.o saveasascii.o size.o testupcase.o
_BIN = makebigline saveasascii size testupcase

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

makebigline: $(ODIR)/makebigline.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

saveasascii: $(ODIR)/saveasascii.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

size: $(ODIR)/size.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

testupcase: $(ODIR)/testupcase.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

$(ODIR)/%.o: %.c $(DEPS)
	mkdir -pv $(ODIR)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(LINT) $(LINTFLAGS) $<