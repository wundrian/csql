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
LIBS= -L$(CSQL_INSTALL_ROOT)/lib -lcsqlgw -lcsqlnw -lcsqlodbcadapter -lcsqlsqlnw   -lcsql -lcsqlsql -lcacheload -lcsqlsqllog

TARGETS = \
	test001 conntest1na\
	test002 conntest2na\
	test003 conntest3na\
	test004 conntest4na\
	test005 conntest5na\
	test007 conntest7na\
	test010 conntest10na\
	test011 conntest11na test012 test013

ifeq ($(PlatForm), supported)
all: $(TARGETS)
else
all:
        echo "CSQL is not supported on $(OSNAME) platform"
endif

test001: conntest1.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
conntest1na: conntest1.c common.h
	$(CPlus) -DNETWORKADAPTER $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test002:conntest2.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
conntest2na: conntest2.c common.h
	$(CPlus) -DNETWORKADAPTER $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003:conntest3.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
conntest3na: conntest3.c common.h
	$(CPlus) -DNETWORKADAPTER $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004:conntest4.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
conntest4na: conntest4.c common.h
	$(CPlus) -DNETWORKADAPTER $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005:conntest5.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
conntest5na: conntest5.c common.h
	$(CPlus) -DNETWORKADAPTER $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test007:conntest7.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
conntest7na: conntest7.c common.h
	$(CPlus) -DNETWORKADAPTER $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test010:conntest10.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
conntest10na: conntest10.c common.h
	$(CPlus) -DNETWORKADAPTER $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test011:conntest11.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
conntest11na: conntest11.c common.h
	$(CPlus) -DNETWORKADAPTER $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test012:conntest12.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test013:conntest13.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)

clean:
	rm -f *.o ${TARGETS}
