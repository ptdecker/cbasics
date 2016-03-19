BIN = ../../bin
ODIR = ../../obj
SUBDIRS = 
CC = cc
CFLAGS = -std=c99 -Wall -g -I.
LINT = splint
LINTFLAGS = -compdef +quiet +skip-sys-headers +charintliteral +charint -shadow -preproc
DEPS =
_OBJ = makebigline.o saveasascii.o size.o testupcase.o

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

.PHONY: all clean

all: makebigline saveasascii size testupcase
	@for i in $(SUBDIRS); do \
		echo "make all in $$i..."; \
		cd $$i; \
		make all; \
		cd ..; \
	done

clean:
	rm -f $(ODIR)/*.o

makebigline: $(ODIR)/makebigline.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

saveasascii: $(ODIR)/saveasascii.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

size: $(ODIR)/size.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

testupcase: $(ODIR)/testupcase.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(LINT) $(LINTFLAGS) $<