# For a good overview of Makefiles in general see:
#      http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
# For an overview of the approach taken to recursive make processes see:
#      http://www.eecs.wsu.edu/~cs224/notes/makefile.html

ODIR = ../obj
SUBDIRS = chapter01 chapter02 chapter03 chapter04 extras

.PHONY: all clean

all:
	@for i in $(SUBDIRS); do \
		echo "make all in $$i..."; \
		cd $$i; \
		make all; \
		cd ..; \
	done

clean:
	rm -f $(ODIR)/*.o