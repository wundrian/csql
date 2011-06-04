
OSNAME = $(shell  uname -s)
PlatForm=supported

ifeq ($(OSNAME), SunOS)
CPlus = CC
CPlusFlags = -O2 -w -mt -xarch=v8
SYSLIBS=-ldl -lnsl -lsocket  -lposix4
JAVAC = javac
else
ifeq ($(OSNAME), Linux)
CPlus = g++
CPlusFlags = -O2  -w 
JAVAC = javac -g:none
SYSLIBS= -rdynamic -lrt -lpthread -lcrypt
else
PlatForm=notsupported
all:
        echo "CSQL is not supported on $(OSNAME) platform"
endif
endif

INCL= -I$(CSQL_INSTALL_ROOT)/include -I../../include
LIBS= -L/home/prabatuty/myroot/lib -L$(CSQL_INSTALL_ROOT)/lib -lcsqlodbc -lcsqlsql -lcsqlsqllog -lcsqlstorage -lcsqlbase -lcsqlnw -lodbc -lcsqlgw -lcacheload
#LIBS= -L/home/prabatuty/myroot/lib -L$(CSQL_INSTALL_ROOT)/lib -lodbc

TARGETS = \
        ODBCTest \
        ODBCLoad ODBCLoadWiscSchema ODBCTestWiscSchema
       

ifeq ($(PlatForm), supported)
all: $(TARGETS)
endif


ODBCTest: ODBCTest.c
	$(CPlus) $(CPlusFlags)-o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
ODBCLoad: ODBCLoad.c
	$(CPlus) $(CPlusFlags)-o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
ODBCTestWiscSchema:ODBCTestWiscSchema.c
	$(CPlus) $(CPlusFlags)-o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
ODBCLoadWiscSchema:ODBCLoadWiscSchema.c
	$(CPlus) $(CPlusFlags)-o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
clean:
	rm -f $(TARGETS) *.class

