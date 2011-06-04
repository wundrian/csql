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


INCL=  -I$(CSQL_INSTALL_ROOT)/install/include -I../../../include
LIBS= -L$(CSQL_INSTALL_ROOT)/lib -lcsqlgw -lcsqlnw -lcsqlodbcadapter -lcsqlsqlnw   -lcacheload -lcsqlstorage -lcsqlbase -lcsqlsql -lcsqlsqllog

TARGETS = \
	test001 paratest1na\
	test002 paratest2na\
	test003 paratest3na\
	test004 paratest4na\
	test005 paratest5na\
	test006 paratest6na

ifeq ($(PlatForm), supported)
all: $(TARGETS)
else
all:
        echo "CSQL is not supported on $(OSNAME) platform"
endif

test001:paratest1.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
paratest1na:paratest1.c common.h
	$(CPlus) -DNETWORKADAPTER $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test002:paratest2.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
paratest2na:paratest2.c common.h
	$(CPlus) -DNETWORKADAPTER $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003:paratest3.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
paratest3na:paratest3.c common.h
	$(CPlus) -DNETWORKADAPTER $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004:paratest4.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
paratest4na:paratest4.c common.h
	$(CPlus) -DNETWORKADAPTER $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005:paratest5.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
paratest5na:paratest5.c common.h
	$(CPlus) -DNETWORKADAPTER $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006:paratest6.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
paratest6na:paratest6.c common.h
	$(CPlus) -DNETWORKADAPTER $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)

clean:
	rm -f *.o ${TARGETS}
