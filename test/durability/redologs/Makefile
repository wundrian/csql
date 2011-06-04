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

 

JAVAC = javac -g:none
INCL= -I$(CSQL_INSTALL_ROOT)/include -I../../include
LIBS= -L$(CSQL_INSTALL_ROOT)/lib -lcsqlodbc -lcsqlsql -lcsqlsqllog -lcsqlstorage -lcsqlbase -lcsqlnw -lcsqlodbcadapter -lcsqlfault

TARGETS = stmtTest3  stmtTest5 stmtTest6 stmtTest7 stmtTest8 stmtTest9
        
ifeq ($(PlatForm), supported)
all: $(TARGETS)
else
all:
        echo "CSQL is not supported on $(OSNAME) platform"
endif

stmtTest3: stmtTest3.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
stmtTest5: stmtTest5.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
stmtTest6: stmtTest6.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
stmtTest7: stmtTest7.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
stmtTest8: stmtTest8.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
stmtTest9: stmtTest9.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)

clean:
	rm -f $(TARGETS) *.class

