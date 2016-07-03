BIN = ../../bin
ODIR = obj
SUBDIRS =
CC = cc
CFLAGS = -std=c99 -Wall -g -I.
LINT = splint
LINTFLAGS = -compdef +quiet +skip-sys-headers +charintliteral +charint -shadow -preproc -mustfreeonly -temptrans -nullret -nullpass -nullstate
DEPS =
_OBJ = chngcase.o minprintf.o print.o
_BIN = chngcase minprintf print

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

chngcase: $(ODIR)/chngcase.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/upper
	cp -v $@ $(BIN)/lower

minprintf: $(ODIR)/minprintf.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

print: $(ODIR)/print.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

$(ODIR)/%.o: %.c $(DEPS)
	mkdir -pv $(ODIR)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(LINT) $(LINTFLAGS) $<