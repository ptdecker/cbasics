BIN = ../../bin
ODIR = obj
SUBDIRS = expr pointers strnfunc
CC = cc
CFLAGS = -std=c99 -Wall -g -I.
LINT = splint
LINTFLAGS = -compdef +quiet +skip-sys-headers +charintliteral +charint -shadow -preproc
DEPS =
_OBJ = datetools.o datetoolsp.o dcl.o detab2.o detab3.o entab2.o entab3.o getfloat.o getint.o \
       readline.o readline2.o sort1.o sort2.o sort3.o sort4.o strcat.o tail2.o undcl.o
_BIN = datetools datetoolsp dcl detab2 entab2 detab3 entab3 getfloat getint  readline readline2 \
       sort1 sort2 sort3 sort4 strcat tail2 undcl

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

datetoolsp: $(ODIR)/datetoolsp.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

dcl: $(ODIR)/dcl.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

detab2: $(ODIR)/detab2.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

detab3: $(ODIR)/detab3.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

entab2: $(ODIR)/entab2.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

entab3: $(ODIR)/entab3.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

getfloat: $(ODIR)/getfloat.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

getint: $(ODIR)/getint.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

readline: $(ODIR)/readline.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

readline2: $(ODIR)/readline2.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

sort1: $(ODIR)/sort1.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

sort2: $(ODIR)/sort2.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

sort3: $(ODIR)/sort3.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

sort4: $(ODIR)/sort4.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

strcat: $(ODIR)/strcat.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

tail2: $(ODIR)/tail2.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

undcl: $(ODIR)/undcl.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

$(ODIR)/%.o: %.c $(DEPS)
	mkdir -pv $(ODIR)
	$(CC) $(CFLAGS) -c -o $@ $<
#	$(LINT) $(LINTFLAGS) $<