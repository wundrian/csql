
OSNAME = $(shell  uname -s)
PlatForm=notsupported
ifeq ($(OSNAME), SunOS)
  CPlus = CC
  CPlusFlags = -O2 -w $(COMPILER_FLAG)
  SYSLIBS=-ldl -lnsl -lsocket  -lposix4
  PlatForm=supported
endif
ifeq ($(OSNAME), Linux)
  CPlus = g++
  CPlusFlags = -g -w
  SYSLIBS= -rdynamic -lrt -lpthread -lcrypt
  PlatForm=supported
endif
ifeq ($(OSNAME), FreeBSD)
  CPlus = g++
  CPlusFlags = -g -w
  SYSLIBS= -rdynamic -lrt -lpthread -lcrypt
  PlatForm=supported
endif


INCL= -I$(CSQL_INSTALL_ROOT)/include -I../../include
LIBS= -L/home/prabatuty/myroot/lib -L$(CSQL_INSTALL_ROOT)/lib -lcsqlodbc -lcsqlsql -lcsqlsqllog -lcsqlstorage -lcsqlbase -lcsqlnw -lodbc -lcsqlgw -lcacheload

TARGETS = \
        test001 test002 test003 

ifeq ($(PlatForm), supported)
all: $(TARGETS)
else
all:
        echo "CSQL is not supported on $(OSNAME) platform"
endif


test001:ODBCThread.c 
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test002:ODBCThread.c 
	$(CPlus) -DHASH $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003:ODBCThread.c 
	$(CPlus) -DTREE $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)

clean:
	rm -f $(TARGETS) *.class

