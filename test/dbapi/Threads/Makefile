
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
LIBS= -L$(CSQL_INSTALL_ROOT)/lib  -lcsqlstorage -lcsqlbase 

TARGETS = noindex hash tree autoinc autoinchash autoinctree noindexvarchar hashvarchar treevarchar
       

ifeq ($(PlatForm), supported)
all: $(TARGETS)
else
all:
        echo "CSQL is not supported on $(OSNAME) platform"
endif

noindex: DMLThreadTest.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
hash: DMLThreadTest.c
	$(CPlus) -DHASH $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
tree: DMLThreadTest.c
	$(CPlus) -DTREE $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
noindexvarchar: DMLThreadTest.c
	$(CPlus) -DVARCHAR $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
hashvarchar: DMLThreadTest.c
	$(CPlus) -DHASH -DVARCHAR $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
treevarchar: DMLThreadTest.c
	$(CPlus) -DTREE -DVARCHAR $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
autoinc: autoincTest.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
autoinchash: autoincTest.c
	$(CPlus) -DHASH $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
autoinctree: autoincTest.c
	$(CPlus) -DTREE $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)

clean:
	rm -f $(TARGETS)

