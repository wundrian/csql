
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
        test001 test001a test002 test002a\
        test003 test003a test003b test003c \
        test004 test004a test004b test004c \
        test005 test005a test005b test005c \
        test006 test006a test006b test006c \
        test007 \
        test008 \
        test009 \
        test010 \
        test011 \
        test012 
       

ifeq ($(PlatForm), supported)
all: $(TARGETS)
endif

test001: notpredicate1.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test001a: notpredicate1.c
	$(CPlus) -DWITHINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test002: predicate1.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test002a:predicate1.c
	$(CPlus) -DWITHINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003: andpredicate1.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003a: andpredicate1.c
	$(CPlus) -DWITHF1INDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003b: andpredicate1.c
	$(CPlus) -DWITHF2INDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003c: andpredicate1.c
	$(CPlus) -DWITHF1INDEX -DWITHF2INDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004: notandpredicate1.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004a: notandpredicate1.c
	$(CPlus) -DWITHF1INDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004b: notandpredicate1.c
	$(CPlus) -DWITHF2INDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004c: notandpredicate1.c
	$(CPlus) -DWITHF1INDEX -DWITHF2INDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005: orpredicate1.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005a: orpredicate1.c
	$(CPlus) -DWITHF1INDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005b: orpredicate1.c
	$(CPlus) -DWITHF2INDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005c: orpredicate1.c
	$(CPlus) -DWITHF1INDEX -DWITHF2INDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006: notorpredicate1.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006a: notorpredicate1.c
	$(CPlus) -DWITHF1INDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006b: notorpredicate1.c
	$(CPlus) -DWITHF2INDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006c: notorpredicate1.c
	$(CPlus) -DWITHF1INDEX -DWITHF2INDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test007: andorpredicate1.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test008: orandpredicate1.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test009: andandpredicate1.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test010: ororpredicate1.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test011: andorandpredicate1.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test012: orandorpredicate1.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)

clean:
	rm -f $(TARGETS)

