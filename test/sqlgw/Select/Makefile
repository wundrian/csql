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
	selecttest1 selecttest2 selecttest3 selecttest4 selecttest5 selecttest6 \
    selecttest7 selecttest8 singleconngateway  

ifeq ($(PlatForm), supported)
all: $(TARGETS)
else
all:
        echo "CSQL is not supported on $(OSNAME) platform"
endif

selecttest1: selecttest1.c common.h
	$(CPlus) -DGATEWAY $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
selecttest2: selecttest2.c common.h
	$(CPlus) -DGATEWAY $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
selecttest3: selecttest3.c common.h
	$(CPlus) -DGATEWAY $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
selecttest4: selecttest4.c common.h
	$(CPlus) -DGATEWAY $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
selecttest5: selecttest5.c common.h
	$(CPlus) -DGATEWAY $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
selecttest6: selecttest6.c common.h
	$(CPlus) -DGATEWAY $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
selecttest7: selecttest7.c common.h
	$(CPlus) -DGATEWAY $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
selecttest8: selecttest8.c common.h
	$(CPlus) -DGATEWAY $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
singleconngateway:singleconngateway.c common.h
	$(CPlus) -DGATEWAY $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)	
clean:
	rm -f *.o ${TARGETS}
