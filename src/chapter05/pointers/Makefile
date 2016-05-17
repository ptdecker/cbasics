BIN = ../../../bin
ODIR = obj
SUBDIRS = 
CC = cc
CFLAGS = -std=c99 -Wall -g -I.
LINT = splint
LINTFLAGS = -compdef +quiet +skip-sys-headers +charintliteral +charint -shadow -preproc
DEPS =
_OBJ = anyp.o atofp.o cleantrailsnblanksp.o expandp.o htoip.o itoawp.o itobp.o longestlinep.o \
       reversep.o reverserecursivep.o squeezep.o
_BIN = anyp atofp cleantrailsnblanksp expandp htoip itoawp itobp longestlinep \
       reversep reverserecursivep squeezep

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

.PHONY: all clean

all: $(_BIN) escapep
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
	rm -rv $(ODIR) $(_BIN) escapep

anyp: $(ODIR)/anyp.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

atofp: $(ODIR)/atofp.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

cleantrailsnblanksp: $(ODIR)/cleantrailsnblanksp.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

# escape.c follows a different pattern because splint chokes with an
# internal error on it and a messsage to report it as a bug to them.
# I have submitted such a bug but, so far, to no effect. So we'll 
# ignore linting on this one.
escapep:
	$(CC) $(CFLAGS) escapep.c -o $@
	rm -rv escapep.dSYM
	cp -v $@ $(BIN)/$@

expandp: $(ODIR)/expandp.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

htoip: $(ODIR)/htoip.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

itoawp: $(ODIR)/itoawp.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

itobp: $(ODIR)/itobp.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

longestlinep: $(ODIR)/longestlinep.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

reversep: $(ODIR)/reversep.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

reverserecursivep: $(ODIR)/reverserecursivep.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

squeezep: $(ODIR)/squeezep.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

$(ODIR)/%.o: %.c $(DEPS)
	mkdir -pv $(ODIR)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(LINT) $(LINTFLAGS) $<