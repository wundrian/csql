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
LIBS= -L$(CSQL_INSTALL_ROOT)/lib -lcsqlgw -lcsqlnw -lcsqlodbcadapter -lcsqlsqlnw   -lcacheload -lcsql -lcsqlsql -lcsqlsqllog

TARGETS = \
	paratest1 paratest2 paratest3 paratest4 paratest5 paratest6 

ifeq ($(PlatForm), supported)
all: $(TARGETS)
else
all:
        echo "CSQL is not supported on $(OSNAME) platform"
endif

paratest1:paratest1.c common.h
	$(CPlus) -DGATEWAY $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
paratest2:paratest2.c common.h
	$(CPlus) -DGATEWAY $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
paratest3:paratest3.c common.h
	$(CPlus) -DGATEWAY $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
paratest4:paratest4.c common.h
	$(CPlus) -DGATEWAY $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
paratest5:paratest5.c common.h
	$(CPlus) -DGATEWAY $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
paratest6:paratest6.c common.h
	$(CPlus) -DGATEWAY $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)

clean:
	rm -f *.o ${TARGETS}
