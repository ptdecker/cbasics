BIN = ../../bin
ODIR = ../../obj
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

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

.PHONY: all clean

all: charhistohori charhistovert cleantrailsnblanks countchar countwords ctof detab entab    \
	 eofvalue escapechars fold ftoc-func ftoc-reverse ftoc helloworld longestline longlines  \
	 minilint nocomment printeof reverse showhiddens singleblank wordhistohori wordhistovert \
	 wordperline
	@for i in $(SUBDIRS); do \
		echo "make all in $$i..."; \
		cd $$i; \
		make all; \
		cd ..; \
	done

clean:
	rm -f $(ODIR)/*.o

charhistohori: $(ODIR)/charhistohori.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

charhistovert: $(ODIR)/charhistovert.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

cleantrailsnblanks: $(ODIR)/cleantrailsnblanks.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

countchar: $(ODIR)/countchar.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

countwords: $(ODIR)/countwords.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

ctof: $(ODIR)/ctof.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

detab: $(ODIR)/detab.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

entab: $(ODIR)/entab.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

eofvalue: $(ODIR)/eofvalue.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

# escapechars.c follows a different pattern because it by nature throws
# all sorts of warnings that are okay to ignore. And, splint hates it too.
escapechars:
	$(CC) -std=c99 -w -g -I. escapechars.c -o $(BIN)/$@

fold: $(ODIR)/fold.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

ftoc-func: $(ODIR)/ftoc-func.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

ftoc-reverse: $(ODIR)/ftoc-reverse.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

ftoc: $(ODIR)/ftoc.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

helloworld: $(ODIR)/helloworld.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

longestline: $(ODIR)/longestline.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

longlines: $(ODIR)/longlines.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

minilint: $(ODIR)/minilint.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

nocomment: $(ODIR)/nocomment.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

printeof: $(ODIR)/printeof.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

reverse: $(ODIR)/reverse.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

showhiddens: $(ODIR)/showhiddens.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

singleblank: $(ODIR)/singleblank.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

wordhistohori: $(ODIR)/wordhistohori.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

wordhistovert: $(ODIR)/wordhistovert.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

wordperline: $(ODIR)/wordperline.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(LINT) $(LINTFLAGS) $<