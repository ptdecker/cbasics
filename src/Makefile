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