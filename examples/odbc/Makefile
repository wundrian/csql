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
#LIBS= -L$(CSQL_INSTALL_ROOT)/lib -lodbc

TARGETS =  ODBCman1 ODBCman2 ODBCman3 ODBCman4 ODBCman5 ODBCman6  odbcexample

ifeq ($(PlatForm), supported)
all: $(TARGETS)
endif

.c.o:.c
	$(CPlus) $(CPlusFlags) $(INCL) -c -o $@ $<

ODBCman1: ODBCman1.o 
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)

ODBCman2:ODBCman2.o 
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)
ODBCman3:ODBCman3.o
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)
ODBCman4:ODBCman4.o
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)
ODBCman5:ODBCman5.o
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)
ODBCman6:ODBCman6.o
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)
odbcexample:odbcexample.o
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)

clean:
	rm -f *.o $(TARGETS)

