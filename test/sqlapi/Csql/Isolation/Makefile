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


INCL=  -I$(CSQL_INSTALL_ROOT)/include -I../../../../include
ifeq ($(BUILDTYPE), MMDB)
LIBS= -L$(CSQL_INSTALL_ROOT)/lib -lcsqlsql -lcsqlstorage -lcsqlbase -lcsqlsqllog -lcsqlnw -lcsqlsqlnw -lcsqlsqlnw  
else
LIBS= -L$(CSQL_INSTALL_ROOT)/lib -lcsqlsql -lcsqlstorage -lcsqlbase -lcsqlsqllog -lcsqlnw -lcacheload -lcsqlsqlnw -lcsqlgw -lcsqlsqlnw   -lcsqlodbcadapter
endif

TARGETS = \
	test001 test002 test003 test004 test005\
	test006 test007 test008 test009 test010\
	test011 test012 test013 test014 test015\
	test016 test017 test018 test019 test020\
	test021 test022 test023 test024 test025\
	test026 test027 test028 test029 test030\

ifeq ($(PlatForm), supported)
all: $(TARGETS)
else
all:
        echo "CSQL is not supported on $(OSNAME) platform"
endif

test001:isotest1.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test002:isotest2.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003:isotest3.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004:isotest4.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005:isotest5.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006:isotest6.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test007:isotest7.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test008:isotest8.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test009:isotest9.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test010:isotest10.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test011:isotest1.c common.h
	$(CPlus) -DRDUNCOM $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test012:isotest2.c common.h
	$(CPlus) -DRDUNCOM $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test013:isotest3.c common.h
	$(CPlus) -DRDUNCOM $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test014:isotest4.c common.h
	$(CPlus) -DRDUNCOM $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test015:isotest5.c common.h
	$(CPlus) -DRDUNCOM $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test016:isotest6.c common.h
	$(CPlus) -DRDUNCOM $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test017:isotest7.c common.h
	$(CPlus) -DRDUNCOM $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test018:isotest8.c common.h
	$(CPlus) -DRDUNCOM $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test019:isotest9.c common.h
	$(CPlus) -DRDUNCOM $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test020:isotest10.c common.h
	$(CPlus) -DRDUNCOM $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test021:isotest1.c common.h
	$(CPlus) -DRDRPT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test022:isotest2.c common.h
	$(CPlus) -DRDRPT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test023:isotest3.c common.h
	$(CPlus) -DRDRPT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test024:isotest4.c common.h
	$(CPlus) -DRDRPT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test025:isotest5.c common.h
	$(CPlus) -DRDRPT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test026:isotest6.c common.h
	$(CPlus) -DRDRPT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test027:isotest7.c common.h
	$(CPlus) -DRDRPT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test028:isotest8.c common.h
	$(CPlus) -DRDRPT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test029:isotest9.c common.h
	$(CPlus) -DRDRPT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test030:isotest10.c common.h
	$(CPlus) -DRDRPT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)

clean:
	rm -f $(TARGETS)
