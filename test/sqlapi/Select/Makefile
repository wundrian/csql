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
ifeq ($(BUILDTYPE), MMDB)
LIBS= -L$(CSQL_INSTALL_ROOT)/lib -lcsqlsql -lcsqlstorage -lcsqlbase -lcsqlsqllog -lcsqlnw -lcsqlsqlnw 
else
LIBS= -L$(CSQL_INSTALL_ROOT)/lib -lcsqlsql -lcsqlstorage -lcsqlbase -lcsqlsqllog -lcsqlnw -lcacheload -lcsqlsqlnw -lcsqlgw  -lcsqlodbcadapter
endif

TARGETS = \
	test001 test001n\
	test002 test002n\
	test003 test003n\
	test004 test004n\
	test005 test005n\
	test006 test006n\
	test007 test007n\
	test008 test008n\
	test009 test009n\
	test010 test010n\
	test011 test011n\
	test012 test012n\
	test013 test013n\
	test014 test015\
	test016 test016n\
	

ifeq ($(PlatForm), supported)
all: $(TARGETS)
else
all:
        echo "CSQL is not supported on $(OSNAME) platform"
endif

test001: selecttest1.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test001n: selecttest1.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test002:selecttest2.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test002n: selecttest2.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003:selecttest3.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003n: selecttest3.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004:selecttest4.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004n: selecttest4.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005:selecttest5.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005n: selecttest5.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006:selecttest6.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006n: selecttest6.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test007:selecttest7.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test007n: selecttest7.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test008:selecttest8.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test008n: selecttest8.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test009:selecttest9.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test009n: selecttest9.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test010:selecttest10.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test010n: selecttest10.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test011:selecttest11.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test011n:selecttest11.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test012:selecttest12.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test012n:selecttest12.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test013:selecttest13.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test013n:selecttest13.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test014:aggseltest14.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test015:selecttest14.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test016:singleconn.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test016n:singleconn.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
clean:
	rm -f *.o ${TARGETS}
