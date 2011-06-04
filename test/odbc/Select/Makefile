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
TARGETS =  test001 test002 test003 test004 test005 \
	test006 test007 test008 test009 test010 \
	test001nw test002nw test003nw test004nw test005nw \
	test006nw test007nw test008nw test009nw test010nw 
else
TARGETS =  test001 test002 test003 test004 test005 \
	test006 test007 test008 test009 test010 \
	test001nw test002nw test003nw test004nw test005nw \
	test006nw test007nw test008nw test009nw test010nw 
endif

ifeq ($(PlatForm), supported)
all: $(TARGETS)
else
all:
        echo "CSQL is not supported on $(OSNAME) platform"
endif

test001: odbcselect1.c 
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test001nw: odbcselect1nw.c 
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test002:odbcselect2.c 
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test002nw: odbcselect2nw.c 
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003:odbcselect3.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003nw: odbcselect3nw.c 
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004:odbcselect4.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004nw: odbcselect4nw.c 
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005:odbcselect5.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005nw: odbcselect5nw.c 
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006:odbcselect6.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006nw: odbcselect6nw.c 
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test007:odbcselect7.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test007nw: odbcselect7nw.c 
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test008:odbcselect8.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test008nw: odbcselect8nw.c 
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test009:odbcselect9.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test009nw: odbcselect9nw.c 
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test010:odbcselect10.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test010nw: odbcselect10nw.c 
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)

clean:
	rm -f *.o $(TARGETS)

