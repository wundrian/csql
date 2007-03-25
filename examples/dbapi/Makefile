OSNAME = $(shell  uname -s)
PlatForm=supported

ifeq ($(OSNAME), SunOS)
CPlus = CC
CPlusFlags = -O2 -w -mt -xarch=v8 
SYSLIBS=-ldl -lnsl -lsocket  -lposix4 
else 
ifeq ($(OSNAME), Linux)
CPlus = g++
CPlusFlags = -O2 -w
SYSLIBS= -rdynamic -lrt -lpthread -lcrypt
else
PlatForm=notsupported
all:
	echo "CSQL is not supported on $(OSNAME) platform"
endif
endif

INCL= -I$(INSTALLROOT)/include
LIBS= -L$(INSTALLROOT)/lib -lcsql

TARGETS = \
	dbapiexample

ifeq ($(PlatForm), supported)
all: $(TARGETS)
endif 

.c.o:.c
	$(CPlus) $(CPlusFlags) $(INCL) -c -o $@ $<

dbapiexample: dbapiexample.o
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)

clean:
	rm *.o dbapiexample
