# For a good overview of Makefiles in general see:
#      http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
# For an overview of the approach taken to recursive make processes see:
#      http://www.eecs.wsu.edu/~cs224/notes/makefile.html

SUBDIRS = chapter01 chapter02 chapter03 chapter04 chapter05 chapter06 extras

.PHONY: all clean

all:
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
