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
	test001 selecttest1na\
	test002 selecttest2na\
	test003 selecttest3na\
	test004 selecttest4na\
	test005 selecttest5na\
	test006 selecttest6na\
	test007 selecttest7na\
	test008 selecttest8na\
	test009 selecttest9na\
	test010 selecttest10na\
	test011 singleconnadapterna 

ifeq ($(PlatForm), supported)
all: $(TARGETS)
else
all:
        echo "CSQL is not supported on $(OSNAME) platform"
endif

test001: selecttest1.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
selecttest1na: selecttest1.c common.h
	$(CPlus) -DNETWORKADAPTER $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test002:selecttest2.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
selecttest2na: selecttest2.c common.h
	$(CPlus) -DNETWORKADAPTER $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003:selecttest3.c common.h 
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
selecttest3na: selecttest3.c common.h
	$(CPlus) -DNETWORKADAPTER $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004:selecttest4.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
selecttest4na: selecttest4.c common.h
	$(CPlus) -DNETWORKADAPTER $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005:selecttest5.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
selecttest5na: selecttest5.c common.h
	$(CPlus) -DNETWORKADAPTER $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006:selecttest6.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
selecttest6na: selecttest6.c common.h
	$(CPlus) -DNETWORKADAPTER $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test007:selecttest7.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
selecttest7na: selecttest7.c common.h
	$(CPlus) -DNETWORKADAPTER $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test008:selecttest8.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
selecttest8na: selecttest8.c common.h
	$(CPlus) -DNETWORKADAPTER $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test009:selecttest9.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
selecttest9na: selecttest9.c common.h
	$(CPlus) -DNETWORKADAPTER $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test010:selecttest10.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
selecttest10na: selecttest10.c common.h
	$(CPlus) -DNETWORKADAPTER $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test011:singleconnadapter.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
singleconnadapterna: singleconnadapter.c common.h
	$(CPlus) -DNETWORKADAPTER $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
	
clean:
	rm -f *.o ${TARGETS}
