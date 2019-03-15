BIN = ../../bin
ODIR = obj
SUBDIRS = rpncalc
CC = cc
CFLAGS = -std=c99 -Wall -g -I.
LINT = splint
LINTFLAGS = +quiet +skip-sys-headers +charint -preproc
DEPS =
_OBJ = echoargs.o getkeywords.o makebigline.o points.o porterstem.o saveasascii.o size.o testupcase.o wordxrefstem.o
_BIN = echoargs getkeywords makebigline points porterstem saveasascii size testupcase wordxrefstem

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

echoargs: $(ODIR)/echoargs.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

getkeywords: $(ODIR)/getkeywords.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

makebigline: $(ODIR)/makebigline.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

points: $(ODIR)/points.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	cp $@ $(BIN)/$@

porterstem: $(ODIR)/porterstem.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

saveasascii: $(ODIR)/saveasascii.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

size: $(ODIR)/size.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

testupcase: $(ODIR)/testupcase.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

wordxrefstem: $(ODIR)/wordxrefstem.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

$(ODIR)/%.o: %.c $(DEPS)
	mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(LINT) $(LINTFLAGS) $<
