BIN = ../../bin
ODIR = obj
SUBDIRS = 
CC = cc
CFLAGS = -std=c99 -Wall -g -I.
LINT = splint
LINTFLAGS = +quiet +skip-sys-headers +charint
DEPS =
_OBJ = charhistohori.o charhistovert.o cleantrailsnblanks.o countchar.o countwords.o ctof.o \
       detab.o entab.o eofvalue.o fold.o ftoc-func.o ftoc-reverse.o ftoc.o helloworld.o     \
       longestline.o longlines.o minilint.o nocomment.o printeof.o reverse.o showhiddens.o  \
       singleblank.o wordhistohori.o wordhistovert.o wordperline.o escapechars.o
_BIN = charhistohori charhistovert cleantrailsnblanks countchar countwords ctof \
       detab entab eofvalue fold ftoc-func ftoc-reverse ftoc helloworld     \
       longestline longlines minilint nocomment printeof reverse showhiddens  \
       singleblank wordhistohori wordhistovert wordperline escapechars

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

charhistohori: $(ODIR)/charhistohori.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

charhistovert: $(ODIR)/charhistovert.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

cleantrailsnblanks: $(ODIR)/cleantrailsnblanks.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

countchar: $(ODIR)/countchar.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

countwords: $(ODIR)/countwords.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

ctof: $(ODIR)/ctof.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

detab: $(ODIR)/detab.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

entab: $(ODIR)/entab.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

eofvalue: $(ODIR)/eofvalue.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

# escapechars.c follows a different pattern because it by nature throws
# all sorts of warnings that are okay to ignore. And, splint hates it too.
escapechars:
	$(CC) -std=c99 -w -g -I. escapechars.c -o $@
	cp $@ $(BIN)/$@
	rm -f -r escapechars.dSYM

fold: $(ODIR)/fold.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

ftoc-func: $(ODIR)/ftoc-func.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

ftoc-reverse: $(ODIR)/ftoc-reverse.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

ftoc: $(ODIR)/ftoc.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

helloworld: $(ODIR)/helloworld.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

longestline: $(ODIR)/longestline.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

longlines: $(ODIR)/longlines.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

minilint: $(ODIR)/minilint.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

nocomment: $(ODIR)/nocomment.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

printeof: $(ODIR)/printeof.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

reverse: $(ODIR)/reverse.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

showhiddens: $(ODIR)/showhiddens.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

singleblank: $(ODIR)/singleblank.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

wordhistohori: $(ODIR)/wordhistohori.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

wordhistovert: $(ODIR)/wordhistovert.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

wordperline: $(ODIR)/wordperline.o
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ $(BIN)/$@

$(ODIR)/%.o: %.c $(DEPS)
	mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(LINT) $(LINTFLAGS) $<
