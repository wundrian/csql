
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
        test001  test002  test003  test004  test005  test006   test007  \
        test008  test009  test010  test011  test012  test013   test014  \
        test015  test016  test017  test018  test019  test020   test021  \
        test022  test002a test004a test006a test008a test010a \
        test012a test014a test016a test018a test020a test022a test002b \
	test006b test016b
 
ifeq ($(PlatForm), supported)
all: $(TARGETS)
else
all:
        echo "CSQL is not supported on $(OSNAME) platform"
endif

       
test001: inttest.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test002: inttest.c
	$(CPlus) -DWITHINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test002a: inttest.c
	$(CPlus) -DWITHTREEINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test002b: inttest.c
	$(CPlus) -DWITHTRIEINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003: longtest.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004: longtest.c
	$(CPlus) -DWITHINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004a: longtest.c
	$(CPlus) -DWITHTREEINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005: longlongtest.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006: longlongtest.c
	$(CPlus)  $(CPlusFlags) -DWITHINDEX -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006a: longlongtest.c
	$(CPlus)  $(CPlusFlags) -DWITHTREEINDEX -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006b: longlongtest.c
	$(CPlus)  $(CPlusFlags) -DWITHTRIEINDEX -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test007: shorttest.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test008: shorttest.c
	$(CPlus)  -DWITHINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test008a: shorttest.c
	$(CPlus)  -DWITHTREEINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test009: byteinttest.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test010: byteinttest.c
	$(CPlus)  -DWITHINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test010a: byteinttest.c
	$(CPlus)  -DWITHTREEINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test011: floattest.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test012: floattest.c
	$(CPlus)  -DWITHINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test012a: floattest.c
	$(CPlus)  -DWITHTREEINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test013: doubletest.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test014: doubletest.c
	$(CPlus)  -DWITHINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test014a: doubletest.c
	$(CPlus)  -DWITHTREEINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test015: chartest.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test016: chartest.c
	$(CPlus)  -DWITHINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test016a: chartest.c
	$(CPlus)  -DWITHTREEINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test016b: chartest.c
	$(CPlus)  -DWITHTRIEINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test017: datetest.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test018: datetest.c
	$(CPlus)  -DWITHINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test018a: datetest.c
	$(CPlus)  -DWITHTREEINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test019: timetest.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test020: timetest.c
	$(CPlus)  -DWITHINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test020a: timetest.c
	$(CPlus)  -DWITHTREEINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test021: timestamptest.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test022: timestamptest.c
	$(CPlus)  -DWITHINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test022a: timestamptest.c
	$(CPlus)  -DWITHTREEINDEX $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)

clean:
	rm -f $(TARGETS)

