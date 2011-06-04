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


INCL= -I$(CSQL_INSTALL_ROOT)/include -I../../../include
ifeq ($(BUILDTYPE), MMDB)
LIBS= -L$(CSQL_INSTALL_ROOT)/lib -lcsqlodbc -lcsqlnw -lcsqlsqlnw -lcsqlstorage -lcsqlbase -lcsqlsql -lcsqlsqllog
else
LIBS= -L$(CSQL_INSTALL_ROOT)/lib -lcsqlodbc -lcacheload -lcsqlgw -lcsqlnw -lcsqlodbcadapter -lcsqlsqlnw -lcacheload -lcsqlstorage -lcsqlbase -lcsqlsql -lcsqlsqllog
endif


ifeq ($(BUILDTYPE), MMDB)
TARGETS =  test001 test002 \
	test001nw test002nw
else
TARGETS =  test001 test002 \
	test001nw test002nw
endif 

ifeq ($(PlatForm), supported)
all: $(TARGETS)
else
all:
        echo "CSQL is not supported on $(OSNAME) platform"
endif

test001: transact1.c 
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test001nw: transact1nw.c 
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)

test002:transact2.c 
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test002nw: transact2nw.c 
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)

clean:
	rm -f *.o $(TARGETS)

