BIN = ../../bin
ODIR = ../../obj
SUBDIRS = 
CC = cc
CFLAGS = -std=c99 -Wall -g -I.
LINT = splint
LINTFLAGS = -compdef +quiet +skip-sys-headers +charintliteral +charint -shadow -preproc
DEPS =
_OBJ = any.o equivloop.o fastbitcount.o htoi.o invert.o lower.o rightrot.o setbits.o squeeze.o typelimits.o

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

.PHONY: all clean

all: any equivloop fastbitcount htoi invert lower rightrot setbits squeeze typelimits
	@for i in $(SUBDIRS); do \
		echo "make all in $$i..."; \
		cd $$i; \
		make all; \
		cd ..; \
	done

clean:
	rm -f $(ODIR)/*.o

any: $(ODIR)/any.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

equivloop: $(ODIR)/equivloop.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

fastbitcount: $(ODIR)/fastbitcount.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

htoi: $(ODIR)/htoi.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

invert: $(ODIR)/invert.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

lower: $(ODIR)/lower.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

rightrot: $(ODIR)/rightrot.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

setbits: $(ODIR)/setbits.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

squeeze: $(ODIR)/squeeze.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

typelimits: $(ODIR)/typelimits.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(LINT) $(LINTFLAGS) $<