BIN = ../../bin
ODIR = obj
SUBDIRS =
CC = cc
CFLAGS = -std=c99 -Wall -g -I.
LINT = splint
LINTFLAGS = +quiet +skip-sys-headers +charint -preproc
DEPS =
_OBJ = define.o getvars.o getword.o tablookup.o wordfreq.o wordxref.o
_BIN = define getvars getword tablookup wordfreq wordxref

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

define: $(ODIR)/define.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

getvars: $(ODIR)/getvars.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

getword: $(ODIR)/getword.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

tablookup: $(ODIR)/tablookup.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

wordfreq: $(ODIR)/wordfreq.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

wordxref: $(ODIR)/wordxref.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

$(ODIR)/%.o: %.c $(DEPS)
	mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(LINT) $(LINTFLAGS) $<