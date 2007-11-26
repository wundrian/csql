
OSNAME = $(shell  uname -s)
PlatForm=supported

ifeq ($(OSNAME), SunOS)
CPlus = CC
CPlusFlags = -O2 -w -mt -xarch=v8
SYSLIBS=-ldl -lnsl -lsocket  -lposix4
else
ifeq ($(OSNAME), Linux)
CPlus = g++
CPlusFlags = -g -w
SYSLIBS= -rdynamic -lrt -lpthread -lcrypt
else
PlatForm=notsupported
all:
        echo "CSQL is not supported on $(OSNAME) platform"
endif
endif

INCL= -I$(CSQL_INSTALL_ROOT)/include
LIBS= -L$(CSQL_INSTALL_ROOT)/lib -lcsql

TARGETS = \
        test001 test002 test003 test004 test005 test006 test007 test008 \
	test009 test010 test011 test012 test013 test014 test015 test016 \
	test017 \
	test051 test052 test053 test054 test055 test056 test057 test058 \
	test059 test060 \
	test061 test062 test063 test064 test065 test066 test067 test068 \
	test069 test070 \
	test071 test072 test073 test074 test075 test076 test077 test078 \
	test079 test080 \
	test081 test082 test083 test084 test085 test086 test087 test088 \
	test089 test090 \
	test101
       

ifeq ($(PlatForm), supported)
all: $(TARGETS)
endif

test001: conntest1.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test002: conntest2.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003: conntest3.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004: conntest4.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005: conntest5.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006: conntest6.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test007: conntest7.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test008: conntest8.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test009: conntest9.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test010: conntest10.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test011: conntest11.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test012: conntest12.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test013: conntest13.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test014: conntest14.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test015: conntest15.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test016: conntest16.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test017: conntest17.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test051: isotest1.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test052: isotest2.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test053: isotest3.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test054: isotest4.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test055: isotest5.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test056: isotest6.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test057: isotest7.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test058: isotest8.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test059: isotest9.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test060: isotest10.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test061: isotest1.c common.h
	$(CPlus) -DDEFAULT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test062: isotest2.c common.h
	$(CPlus) -DDEFAULT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test063: isotest3.c common.h
	$(CPlus) -DDEFAULT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test064: isotest4.c common.h
	$(CPlus) -DDEFAULT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test065: isotest5.c common.h
	$(CPlus) -DDEFAULT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test066: isotest6.c common.h
	$(CPlus) -DDEFAULT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test067: isotest7.c common.h
	$(CPlus) -DDEFAULT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test068: isotest8.c common.h
	$(CPlus) -DDEFAULT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test069: isotest9.c common.h
	$(CPlus) -DDEFAULT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test070: isotest10.c common.h
	$(CPlus) -DDEFAULT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test071: isotest11.c common.h
	$(CPlus) -DDEFAULT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test072: isotest12.c common.h
	$(CPlus) -DDEFAULT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test073: isotest13.c common.h
	$(CPlus) -DDEFAULT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test074: isotest14.c common.h
	$(CPlus) -DDEFAULT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test075: isotest15.c common.h
	$(CPlus) -DDEFAULT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test076: isotest16.c common.h
	$(CPlus) -DDEFAULT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test077: isotest17.c common.h
	$(CPlus) -DDEFAULT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test078: isotest18.c common.h
	$(CPlus) -DDEFAULT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test079: isotest19.c common.h
	$(CPlus) -DDEFAULT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test080: isotest20.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test081: isotest21.c common.h
	$(CPlus) -DDEFAULT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test082: isotest22.c common.h
	$(CPlus) -DDEFAULT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test083: isotest23.c common.h
	$(CPlus) -DDEFAULT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test084: isotest24.c common.h
	$(CPlus) -DDEFAULT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test085: isotest25.c common.h
	$(CPlus) -DDEFAULT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test086: isotest26.c common.h
	$(CPlus) -DDEFAULT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test087: isotest27.c common.h
	$(CPlus) -DDEFAULT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test088: isotest28.c common.h
	$(CPlus) -DDEFAULT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test089: isotest29.c common.h
	$(CPlus) -DDEFAULT $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test090: isotest30.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test101: threadtest1.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)

clean:
	rm -f $(TARGETS)

