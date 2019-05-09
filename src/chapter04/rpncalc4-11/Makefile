BIN = ../../../bin
ODIR = obj
CC = cc
CFLAGS = -std=c99 -Wall -g -I.
LINT = splint
LINTFLAGS = +quiet +skip-sys-headers +charint -preproc
DEPS =
_OBJ = rpncalc6.o lexer.o dastack.o
_BIN = rpncalc6

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

rpncalc6: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(LINT) $(LINTFLAGS) $@.c
	cp $@ $(BIN)/$@

$(ODIR)/%.o: %.c $(DEPS)
	mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(LINT) $(LINTFLAGS) $<
