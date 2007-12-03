
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
         test001 test001a \
         test003 test003a \
         test004 test004a \
         test005 test005a \
         test006 test006a \
         test007 test007a \
         test008 test008a \
         test009 test009a \
         test002 test002a 
       

ifeq ($(PlatForm), supported)
all: $(TARGETS)
endif

test001: locktest001.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test001a: locktest001.c
	$(CPlus) -DWITHINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test002: locktest002.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test002a: locktest002.c
	$(CPlus) -DWITHINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003: locktest003.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003a: locktest003.c
	$(CPlus) -DWITHINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004: locktest004.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004a: locktest004.c
	$(CPlus) -DWITHINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005: locktest005.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005a: locktest005.c
	$(CPlus) -DWITHINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006: locktest006.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006a: locktest006.c
	$(CPlus) -DWITHINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test007: locktest007.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test007a: locktest007.c
	$(CPlus) -DWITHINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test008: locktest008.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test008a: locktest008.c
	$(CPlus) -DWITHINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test009: locktest009.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test009a: locktest009.c
	$(CPlus) -DWITHINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
clean:
	rm -f $(TARGETS)

