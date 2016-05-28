BIN = ../../bin
ODIR = obj
SUBDIRS = pointers strnfunc
CC = cc
CFLAGS = -std=c99 -Wall -g -I.
LINT = splint
LINTFLAGS = -compdef +quiet +skip-sys-headers +charintliteral +charint -shadow -preproc
DEPS =
_OBJ = datetools.o getfloat.o getint.o strcat.o readline.o readline2.o
_BIN = datetools getfloat getint strcat readline readline2

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

datetools: $(ODIR)/datetools.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

getfloat: $(ODIR)/getfloat.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

getint: $(ODIR)/getint.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

strcat: $(ODIR)/strcat.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

readline: $(ODIR)/readline.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

readline2: $(ODIR)/readline2.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

$(ODIR)/%.o: %.c $(DEPS)
	mkdir -pv $(ODIR)
	$(CC) $(CFLAGS) -c -o $@ $<
#	$(LINT) $(LINTFLAGS) $<