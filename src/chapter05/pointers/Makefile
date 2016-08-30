BIN = ../../../bin
ODIR = obj
SUBDIRS =
CC = cc
CFLAGS = -std=c99 -Wall -g -I.
LINT = splint
LINTFLAGS = +quiet +skip-sys-headers +charint -preproc
DEPS =
_OBJ = anyp.o atofp.o cleantrailsnblanksp.o expandp.o htoip.o itoawp.o itobp.o longestlinep.o \
       reversep.o reverserecursivep.o squeezep.o escapep.o
_BIN = anyp atofp cleantrailsnblanksp expandp htoip itoawp itobp longestlinep \
       reversep reverserecursivep squeezep escapep

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

anyp: $(ODIR)/anyp.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

atofp: $(ODIR)/atofp.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

cleantrailsnblanksp: $(ODIR)/cleantrailsnblanksp.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

escapep: $(ODIR)/escapep.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

expandp: $(ODIR)/expandp.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

htoip: $(ODIR)/htoip.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

itoawp: $(ODIR)/itoawp.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

itobp: $(ODIR)/itobp.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

longestlinep: $(ODIR)/longestlinep.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

reversep: $(ODIR)/reversep.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

reverserecursivep: $(ODIR)/reverserecursivep.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

squeezep: $(ODIR)/squeezep.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

$(ODIR)/%.o: %.c $(DEPS)
	mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(LINT) $(LINTFLAGS) $<
