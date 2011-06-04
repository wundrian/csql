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
LIBS= -L$(CSQL_INSTALL_ROOT)/lib -lcsqlsql -lcsqlstorage -lcsqlbase -lcsqlsqllog -lcsqlnw -lcsqlsqlnw 
else 
LIBS= -L$(CSQL_INSTALL_ROOT)/lib -lcsqlsql -lcsqlstorage -lcsqlbase -lcsqlsqllog -lcsqlnw -lcacheload -lcsqlsqlnw  -lcsqlgw -lcsqlodbcadapter
endif

TARGETS = \
	test001 test001n \
	test002 test002n \
	test003 test003n \
	test004 test004n \
	test005 test005n \
	test006 test006n \
	hashindexonalldatatype hashindexonalldatatypen \
	treeindexonalldatatype treeindexonalldatatypen \
	compositehashonalldatatype compositehashonalldatatypen \
	test010 test010n

ifeq ($(PlatForm), supported)
all: $(TARGETS)
else
all:
        echo "CSQL is not supported on $(OSNAME) platform"
endif

test001: createtablewithalldatatype.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test001n: createtablewithalldatatype.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test002: defaultwithalldatatype.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test002n: defaultwithalldatatype.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003: notnullonalldatatype.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003n: notnullonalldatatype.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004: pkeyfkeyonalldatatype.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004n: pkeyfkeyonalldatatype.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005: autoincreonalldatatype.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005n: autoincreonalldatatype.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006: copystatement.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006n: copystatement.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
hashindexonalldatatype: hashindexonalldatatype.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
hashindexonalldatatypen: hashindexonalldatatype.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
treeindexonalldatatype: treeindexonalldatatype.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
treeindexonalldatatypen: treeindexonalldatatype.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
compositehashonalldatatype: compositehashonalldatatype.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
compositehashonalldatatypen: compositehashonalldatatype.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test010: charvarcharrange.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test010n: charvarcharrange.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)

clean:
	rm -f *.o ${TARGETS}
