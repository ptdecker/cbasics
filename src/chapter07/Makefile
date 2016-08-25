BIN = ../../bin
ODIR = obj
SUBDIRS = scancalc
CC = cc
CFLAGS = -std=c99 -Wall -g -I.
LINT = splint
LINTFLAGS = +quiet +skip-sys-headers +charint -preproc
DEPS =
_OBJ = chngcase.o fprint.o mindiff.o minfind.o minprintf.o minscanf.o print.o
_BIN = chngcase fprint mindiff minfind minprintf minscanf print

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

chngcase: $(ODIR)/chngcase.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/upper
	cp $@ $(BIN)/lower

fprint: $(ODIR)/fprint.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

mindiff: $(ODIR)/mindiff.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

minfind: $(ODIR)/minfind.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

minprintf: $(ODIR)/minprintf.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

minscanf: $(ODIR)/minscanf.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

print: $(ODIR)/print.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

$(ODIR)/%.o: %.c $(DEPS)
	mkdir -pv $(ODIR)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(LINT) $(LINTFLAGS) $<