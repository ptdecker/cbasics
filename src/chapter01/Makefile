BIN = ../../bin
ODIR = obj
SUBDIRS = 
CC = cc
CFLAGS = -std=c99 -Wall -g -I.
LINT = splint
LINTFLAGS = -compdef +quiet +skip-sys-headers +charintliteral +charint -shadow -preproc
DEPS =
_OBJ = charhistohori.o charhistovert.o cleantrailsnblanks.o countchar.o countwords.o ctof.o \
       detab.o entab.o eofvalue.o fold.o ftoc-func.o ftoc-reverse.o ftoc.o helloworld.o     \
       longestline.o longlines.o minilint.o nocomment.o printeof.o reverse.o showhiddens.o  \
       singleblank.o wordhistohori.o wordhistovert.o wordperline.o
_BIN = charhistohori charhistovert cleantrailsnblanks countchar countwords ctof \
       detab entab eofvalue fold ftoc-func ftoc-reverse ftoc helloworld     \
       longestline longlines minilint nocomment printeof reverse showhiddens  \
       singleblank wordhistohori wordhistovert wordperline

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
	rm -rv $(ODIR) $(_BIN) escapechars

charhistohori: $(ODIR)/charhistohori.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

charhistovert: $(ODIR)/charhistovert.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

cleantrailsnblanks: $(ODIR)/cleantrailsnblanks.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

countchar: $(ODIR)/countchar.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

countwords: $(ODIR)/countwords.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

ctof: $(ODIR)/ctof.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

detab: $(ODIR)/detab.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

entab: $(ODIR)/entab.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

eofvalue: $(ODIR)/eofvalue.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

# escapechars.c follows a different pattern because it by nature throws
# all sorts of warnings that are okay to ignore. And, splint hates it too.
escapechars:
	$(CC) -std=c99 -w -g -I. escapechars.c -o $@
	cp -v $@ $(BIN)/$@
	rm -r escapechars.dSYM

fold: $(ODIR)/fold.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

ftoc-func: $(ODIR)/ftoc-func.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

ftoc-reverse: $(ODIR)/ftoc-reverse.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

ftoc: $(ODIR)/ftoc.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

helloworld: $(ODIR)/helloworld.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

longestline: $(ODIR)/longestline.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

longlines: $(ODIR)/longlines.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

minilint: $(ODIR)/minilint.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

nocomment: $(ODIR)/nocomment.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

printeof: $(ODIR)/printeof.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

reverse: $(ODIR)/reverse.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

showhiddens: $(ODIR)/showhiddens.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

singleblank: $(ODIR)/singleblank.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

wordhistohori: $(ODIR)/wordhistohori.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

wordhistovert: $(ODIR)/wordhistovert.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

wordperline: $(ODIR)/wordperline.o
	$(CC) $(CFLAGS) $^ -o $@
	cp -v $@ $(BIN)/$@

$(ODIR)/%.o: %.c $(DEPS)
	mkdir -pv $(ODIR)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(LINT) $(LINTFLAGS) $<