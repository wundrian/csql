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


INCL=  -I$(CSQL_INSTALL_ROOT)/install/include -I../../../../include
ifeq ($(BUILDTYPE), MMDB)
LIBS= -L$(CSQL_INSTALL_ROOT)/lib -lcsqlsql -lcsqlstorage -lcsqlbase -lcsqlsqllog -lcsqlnw -lcsqlsqlnw -lcsqlsqlnw  
else
LIBS= -L$(CSQL_INSTALL_ROOT)/lib -lcsqlsql -lcsqlstorage -lcsqlbase -lcsqlsqllog -lcsqlnw -lcacheload -lcsqlsqlnw -lcsqlgw -lcsqlsqlnw   -lcsqlodbcadapter
endif

TARGETS = \
	test001 test001n \
	test002 test002n \
	test003 test003n \
	test004 test004n \
	test005 test005n \
	test006 test006n \
	test007 test007n \
	test008 test008n \
	test009 test009n


ifeq ($(PlatForm), supported)
all: $(TARGETS)
else
all:
        echo "CSQL is not supported on $(OSNAME) platform"
endif

test001:conntest1.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test001n:conntest1.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test002:userauthentication.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test002n:userauthentication.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003:connecttwicewithoutclose.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003n:connecttwicewithoutclose.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004:closetwicewithoutconnect.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004n:closetwicewithoutconnect.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005:prepareafterclose.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005n:prepareafterclose.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006:executeafterclose.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006n:executeafterclose.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test007:fetchafterclose.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test007n:fetchafterclose.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test008:transactionafterclose.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test008n:transactionafterclose.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test009:connect5000times.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test009n:connect5000times.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
clean:
	rm -f ${TARGETS}
