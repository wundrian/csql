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

INCL= -I$(CSQL_INSTALL_ROOT)/include

LIBS= -L$(CSQL_INSTALL_ROOT)/lib -lcsqlodbc 


TARGETS = GwStmt 

ifeq ($(PlatForm), supported)
all: $(TARGETS)
endif

.c.o:.c
	$(CPlus) $(CPlusFlags) $(INCL) -c -o $@ $<

GwStmt: GwStmt.o 
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)

clean:
	rm -f *.o $(TARGETS)

