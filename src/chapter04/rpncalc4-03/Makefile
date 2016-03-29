BIN = ../../../bin
ODIR = ../../../obj
CC = cc
CFLAGS = -std=c99 -Wall -g -I.
LINT = splint
LINTFLAGS = -compdef +quiet +skip-sys-headers +charintliteral +charint -shadow -preproc
DEPS =
_OBJ = rpncalc1.o lexer.o dastack.o castack.o

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

.PHONY: all clean

all: rpncalc1

clean:
	rm -f $(ODIR)/*.o

rpncalc1: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@
	$(LINT) $(LINTFLAGS) $@.c


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(LINT) $(LINTFLAGS) $<
