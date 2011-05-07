
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
LIBS= -L$(CSQL_INSTALL_ROOT)/lib -lcsql

TARGETS = \
        test001 \
        test002 \
        test004 \
        test005 \
        test006 test006a \
        test007 test007a \
        test008 test008a \
        test009 test009a \
        test010 test010a \
        test011 test003 \
        test012 test012a test013 \
	test001a test002a test003a \
	test004a test004b test004c \
	test004d test004e test004f \
	test004g test004h \
	test005a test005b test005c \
	test005d test005e test005f \
	test005g test005h \
	test001b test002b test003b \
	test006b test007b test008b \
	test009b test010b test012b
       

ifeq ($(PlatForm), supported)
all: $(TARGETS)
else
all:
        echo "CSQL is not supported on $(OSNAME) platform"
endif


test001: uniqueindex1.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test001a: uniqueindex1.c common.h
	$(CPlus) $(CPlusFlags) -DTREEINDEX -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test001b: uniqueindex1.c common.h
	$(CPlus) $(CPlusFlags) -DTRIEINDEX -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test002: uniqueindex2.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test002a: uniqueindex2.c common.h
	$(CPlus) $(CPlusFlags) -DTREEINDEX -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test002b: uniqueindex2.c common.h
	$(CPlus) $(CPlusFlags) -DTRIEINDEX -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003: uniqueindex3.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003a: uniqueindex3.c common.h
	$(CPlus) $(CPlusFlags) -DTREEINDEX -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003b: uniqueindex3.c common.h
	$(CPlus) $(CPlusFlags) -DTRIEINDEX -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004: twoindex1.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004a: twoindex1.c
	$(CPlus) $(CPlusFlags) -DF1TREE -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004b: twoindex1.c
	$(CPlus) $(CPlusFlags) -DF2TREE -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004c: twoindex1.c
	$(CPlus) $(CPlusFlags) -DF1TREE -DF2TREE -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004d: twoindex1.c
	$(CPlus) $(CPlusFlags) -DF1TRIE -DF2TREE -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004e: twoindex1.c
	$(CPlus) $(CPlusFlags) -DF1TREE -DF2TRIE -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004f: twoindex1.c
	$(CPlus) $(CPlusFlags) -DF1TRIE -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004g: twoindex1.c
	$(CPlus) $(CPlusFlags) -DF2TRIE  -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004h: twoindex1.c
	$(CPlus) $(CPlusFlags) -DF1TRIE -DF2TRIE -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005: twoindex2.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005a: twoindex2.c
	$(CPlus) $(CPlusFlags) -DF1TREE -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005b: twoindex2.c
	$(CPlus) $(CPlusFlags) -DF2TREE -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005c: twoindex2.c
	$(CPlus) $(CPlusFlags) -DF1TREE -DF2TREE -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005d: twoindex2.c
	$(CPlus) $(CPlusFlags) -DF1TRIE -DF2TREE -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005e: twoindex2.c
	$(CPlus) $(CPlusFlags) -DF1TREE -DF2TRIE -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005f: twoindex2.c
	$(CPlus) $(CPlusFlags) -DF1TRIE -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005g: twoindex2.c
	$(CPlus) $(CPlusFlags) -DF2TRIE  -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005h: twoindex2.c
	$(CPlus) $(CPlusFlags) -DF1TRIE -DF2TRIE -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006: dupindex1.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006a: dupindex1.c
	$(CPlus) $(CPlusFlags) -DTREEINDEX -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006b: dupindex1.c
	$(CPlus) $(CPlusFlags) -DTRIEINDEX -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test007: dupindex2.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test007a: dupindex2.c
	$(CPlus) $(CPlusFlags) -DTREEINDEX -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test007b: dupindex2.c
	$(CPlus) $(CPlusFlags) -DTRIEINDEX -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test008: compositekeyindex1.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test008a: compositekeyindex1.c
	$(CPlus) $(CPlusFlags) -DTREEINDEX -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test008b: compositekeyindex1.c
	$(CPlus) $(CPlusFlags) -DTRIEINDEX -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test009: createindexnotexist.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test009a: createindexnotexist.c
	$(CPlus) $(CPlusFlags) -DTREEINDEX -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test009b: createindexnotexist.c
	$(CPlus) $(CPlusFlags) -DTRIEINDEX -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test010: createindexnofld.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test010a: createindexnofld.c
	$(CPlus) $(CPlusFlags) -DTREEINDEX -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test010b: createindexnofld.c
	$(CPlus) $(CPlusFlags) -DTRIEINDEX -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test011: primarynonunique.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test012: index1.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test012a: index1.c common.h
	$(CPlus) $(CPlusFlags) -DTREEINDEX -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test012b: index1.c common.h
	$(CPlus) $(CPlusFlags) -DTRIEINDEX -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test013:multiplecompositeindex1.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
clean:
	rm -f $(TARGETS)

