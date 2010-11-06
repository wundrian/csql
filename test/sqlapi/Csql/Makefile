OSNAME = $(shell  uname -s)
MAKE=gmake

all:
	@for i in *; \
	do \
	if [ -d $$i ];\
	then cd $$i; $(MAKE); cd ..;\
	fi;\
	done

clean:
	@for i in *; \
	do \
	if [ -d $$i ];\
	then cd $$i; $(MAKE) clean; cd ..;\
	fi;\
	done
