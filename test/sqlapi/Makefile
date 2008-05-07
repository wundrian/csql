OSNAME = $(shell  uname -s)
MAKE=make

ifeq ($(OSNAME), SunOS)
PlatForm=supported
else
ifeq ($(OSNAME), Linux)
PlatForm=supported
else
PlatForm=notsupported
all:
        echo "CSQL is not supported on $(OSNAME) platform"
endif
endif


ifeq ($(PlatForm), supported)
all: buildall
endif

buildall:
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
