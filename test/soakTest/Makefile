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
LIBS= -L$(CSQL_INSTALL_ROOT)/lib -lcsqlodbc -lcsqlsql -lcsqlsqllog -lcsqlstorage -lcsqlbase -lcsqlnw -lcsqlodbcadapter

TARGETS = \
        csqlInsert \
	odbcInsert \
	jdbcDelete \
	jdbcUpdate \
	jdbcSelect\
	jdbcSelect1
        
ifeq ($(PlatForm), supported)
all: $(TARGETS)
else
all:
        echo "CSQL is not supported on $(OSNAME) platform"
endif

csqlInsert: csqlInsert.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
odbcInsert: odbcInsert.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
jdbcDelete: jdbcDelete.java
	$(JAVAC)  jdbcDelete.java
jdbcUpdate: jdbcUpdate.java
	$(JAVAC)  jdbcUpdate.java
jdbcSelect: jdbcSelect.java
	$(JAVAC)  jdbcSelect.java 
jdbcSelect1: jdbcSelect1.java
	$(JAVAC)  jdbcSelect1.java 

clean:
	rm -f $(TARGETS) *.class

