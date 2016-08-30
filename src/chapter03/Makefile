BIN = ../../bin
ODIR = obj
SUBDIRS =
CC = cc
CFLAGS = -std=c99 -Wall -g -I.
LINT = splint
LINTFLAGS = +quiet +skip-sys-headers +charint -preproc
DEPS =
_OBJ = binsearch.o escape.o expand.o itoa.o itoaw.o itob.o
_BIN = binsearch escape expand itoa itoaw itob

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

binsearch: $(ODIR)/binsearch.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

escape: $(ODIR)/escape.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

expand: $(ODIR)/expand.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

itoa: $(ODIR)/itoa.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

itoaw: $(ODIR)/itoaw.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

itob: $(ODIR)/itob.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

$(ODIR)/%.o: %.c $(DEPS)
	mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(LINT) $(LINTFLAGS) $<
