BIN = ../../bin
ODIR = obj
SUBDIRS = rpncalc
CC = cc
CFLAGS = -std=c99 -Wall -g -I.
LINT = splint
LINTFLAGS = -compdef +quiet +skip-sys-headers +charintliteral +charint -shadow -preproc -temptrans 
DEPS =
_OBJ = echoargs.o getkeywords.o makebigline.o points.o saveasascii.o size.o testupcase.o
_BIN = echoargs getkeywords makebigline points saveasascii size testupcase

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

echoargs: $(ODIR)/echoargs.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

getkeywords: $(ODIR)/getkeywords.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

makebigline: $(ODIR)/makebigline.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

points: $(ODIR)/points.o
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