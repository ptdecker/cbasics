BIN = ../../../bin
ODIR = obj
SUBDIRS = 
CC = cc
CFLAGS = -std=c99 -Wall -g -I.
LINT = splint
LINTFLAGS = +quiet +skip-sys-headers +charint
DEPS =
_OBJ = strncat.o strncopy.o strncmp.o
_BIN = strncat strncopy strncmp

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

strncat: $(ODIR)/strncat.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

strncopy: $(ODIR)/strncopy.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

strncmp: $(ODIR)/strncmp.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

$(ODIR)/%.o: %.c $(DEPS)
	mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(LINT) $(LINTFLAGS) $<