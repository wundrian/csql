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
         create createNoIndex drop \
         insert1 insert100 insert1000 delete1 delete100 delete1000 deleteAll \
         test010 test011\
         test025 test021 test022 test023 test024
       

ifeq ($(PlatForm), supported)
all: $(TARGETS)
else
all:
        echo "CSQL is not supported on $(OSNAME) platform"
endif

create: create.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
createNoIndex: createNoIndex.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
drop: drop.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
insert1: insert1.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
insert1000: insert1000.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
insert100: insert100.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
delete1: delete1.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
delete1000: delete1000.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
delete100: delete100.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
deleteAll: deleteAll.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test010: dbsizelimit.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test011: dbsizelimit1.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test021: tuplesize1.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test022: tuplesize2.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test023: tuplesize3.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test024: tuplesize4.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test025: tuplesize5.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
clean:
	rm -f $(TARGETS)

