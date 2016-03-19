BIN = ../../bin
ODIR = ../../obj
SUBDIRS = 
CC = cc
CFLAGS = -std=c99 -Wall -g -I.
LINT = splint
LINTFLAGS = -compdef +quiet +skip-sys-headers +charintliteral +charint -shadow -preproc
DEPS =
_OBJ = binsearch.o expand.o itoa.o itoaw.o itob.o

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

.PHONY: all clean

all: binsearch escape expand itoa itoaw itob
	@for i in $(SUBDIRS); do \
		echo "make all in $$i..."; \
		cd $$i; \
		make all; \
		cd ..; \
	done

clean:
	rm -f $(ODIR)/*.o

binsearch: $(ODIR)/binsearch.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

# escape.c follows a different pattern because splint chokes with an
# internal error on it and a messsage to report it as a bug to them.
# I have submitted such a bug but, so far, to no effect. So we'll 
# ignore linting on this one.
escape:
	$(CC) $(CFLAGS) escape.c -o $(BIN)/$@

expand: $(ODIR)/expand.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

itoa: $(ODIR)/itoa.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

itoaw: $(ODIR)/itoaw.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

itob: $(ODIR)/itob.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(LINT) $(LINTFLAGS) $<