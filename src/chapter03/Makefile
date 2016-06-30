BIN = ../../bin
ODIR = obj
SUBDIRS = 
CC = cc
CFLAGS = -std=c99 -Wall -g -I.
LINT = splint
LINTFLAGS = -compdef +quiet +skip-sys-headers +charintliteral +charint -shadow -preproc -mustfreeonly -temptrans -nullret -nullpass
DEPS =
_OBJ = binsearch.o expand.o itoa.o itoaw.o itob.o
_BIN = binsearch expand itoa itoaw itob

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

binsearch: $(ODIR)/binsearch.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

# escape.c follows a different pattern because splint chokes with an
# internal error on it and a messsage to report it as a bug to them.
# I have submitted such a bug but, so far, to no effect. So we'll 
# ignore linting on this one.
escape:
	$(CC) $(CFLAGS) escape.c -o $@
	cp -v $@ $(BIN)/$@
	rm -r $(BIN)/escape.dSYM

expand: $(ODIR)/expand.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

itoa: $(ODIR)/itoa.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

itoaw: $(ODIR)/itoaw.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

itob: $(ODIR)/itob.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

$(ODIR)/%.o: %.c $(DEPS)
	mkdir -pv $(ODIR)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(LINT) $(LINTFLAGS) $<