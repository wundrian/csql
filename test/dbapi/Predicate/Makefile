
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
  SYSLIBS= -rdynamic -lrt -lpthread -lcrypt -ldl
  PlatForm=supported
endif
ifeq ($(OSNAME), FreeBSD)
  CPlus = g++
  CPlusFlags = -g -w
  SYSLIBS= -rdynamic -lrt -lpthread -lcrypt -ldl
  PlatForm=supported
endif


INCL= -I$(CSQL_INSTALL_ROOT)/include -I../../../include
LIBS= -L$(CSQL_INSTALL_ROOT)/lib -lcsqlstorage -lcsqlbase

TARGETS = \
        test001 test001a test002 test002a\
        test003 test003a test003b test003c \
        test004 test004a test004b test004c \
        test005 test005a test005b test005c \
        test006 test006a test006b test006c \
        test007  test008  test009 test010 \
        test011 test012 \
	test001b test002b test003d test003e \
	test003f test003g test003h test005d \
	test005f test005g test005h test005e \
	test004f test004g test004h test004e \
	test004d test006g test006h test006e \
	test006f test006d 

ifeq ($(PlatForm), supported)
all: $(TARGETS)
else
all:
        echo "CSQL is not supported on $(OSNAME) platform"
endif

test001: notpredicate1.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test001a: notpredicate1.c
	$(CPlus) -DWITHINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test001b: notpredicate1.c
	$(CPlus) -DWITHTREEINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test002: predicate1.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test002a:predicate1.c
	$(CPlus) -DWITHINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test002b:predicate1.c
	$(CPlus) -DWITHTREEINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003: andpredicate1.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003a: andpredicate1.c
	$(CPlus) -DWITHF1INDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003b: andpredicate1.c
	$(CPlus) -DWITHF2INDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003c: andpredicate1.c
	$(CPlus) -DWITHF1INDEX -DWITHF2INDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003d: andpredicate1.c
	$(CPlus) -DWITHF1TREEINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003e: andpredicate1.c
	$(CPlus) -DWITHF2TREEINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003f: andpredicate1.c
	$(CPlus) -DWITHF1TREEINDEX -DWITHF2TREEINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003g: andpredicate1.c
	$(CPlus) -DWITHF1INDEX -DWITHF2TREEINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003h: andpredicate1.c
	$(CPlus) -DWITHF1TREEINDEX -DWITHF2INDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)

test004: notandpredicate1.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004a: notandpredicate1.c
	$(CPlus) -DWITHF1INDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004b: notandpredicate1.c
	$(CPlus) -DWITHF2INDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004c: notandpredicate1.c
	$(CPlus) -DWITHF1INDEX -DWITHF2INDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004d: notandpredicate1.c
	$(CPlus) -DWITHF1TREEINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004e: notandpredicate1.c
	$(CPlus) -DWITHF2TREEINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004f: notandpredicate1.c
	$(CPlus) -DWITHF1TREEINDEX -DWITHF2TREEINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004g: notandpredicate1.c
	$(CPlus) -DWITHF1INDEX -DWITHF2TREEINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004h: notandpredicate1.c
	$(CPlus) -DWITHF1TREEINDEX -DWITHF2INDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)

test005: orpredicate1.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005a: orpredicate1.c
	$(CPlus) -DWITHF1INDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005b: orpredicate1.c
	$(CPlus) -DWITHF2INDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005c: orpredicate1.c
	$(CPlus) -DWITHF1INDEX -DWITHF2INDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005d: orpredicate1.c
	$(CPlus) -DWITHF1TREEINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005e: orpredicate1.c
	$(CPlus) -DWITHF2TREEINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005f: orpredicate1.c
	$(CPlus) -DWITHF1TREEINDEX -DWITHF2TREEINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005g: orpredicate1.c
	$(CPlus) -DWITHF1INDEX -DWITHF2TREEINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005h: orpredicate1.c
	$(CPlus) -DWITHF1TREEINDEX -DWITHF2INDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)

test006: notorpredicate1.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006a: notorpredicate1.c
	$(CPlus) -DWITHF1INDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006b: notorpredicate1.c
	$(CPlus) -DWITHF2INDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006c: notorpredicate1.c
	$(CPlus) -DWITHF1INDEX -DWITHF2INDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006d: notorpredicate1.c
	$(CPlus) -DWITHF1TREEINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006e: notorpredicate1.c
	$(CPlus) -DWITHF2TREEINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006f: notorpredicate1.c
	$(CPlus) -DWITHF1TREEINDEX -DWITHF2TREEINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006g: notorpredicate1.c
	$(CPlus) -DWITHF1INDEX -DWITHF2TREEINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006h: notorpredicate1.c
	$(CPlus) -DWITHF1TREEINDEX -DWITHF2INDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)

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

