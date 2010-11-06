
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
CPlusFlags = -O2  -w 
SYSLIBS= -rdynamic -lrt -lpthread -lcrypt
PlatForm=supported
endif

ifeq ($(OSNAME), FreeBSD)
CPlus = g++
CPlusFlags = -O2  -w
SYSLIBS= -rdynamic -lrt -lpthread -lcrypt
PlatForm=supported
endif


JAVAC = javac -g:none
INCL= -I$(CSQL_INSTALL_ROOT)/include -I../../include
LIBS= -L/home/prabatuty/myroot/lib -L$(CSQL_INSTALL_ROOT)/lib -L/usr/local/lib -lcsqlsql -lcsqlsqllog -lcsql -lcsqlnw -lodbc -lcsqlgw -lcacheload   -lcsqlsqlnw -lcsqlodbcadapter 

TARGETS = \
        SQLAdapterTest 
       

ifeq ($(PlatForm), supported)
all: $(TARGETS)
else
all:
        echo "CSQL is not supported on $(OSNAME) platform"
endif


SQLAdapterTest: SQLAdapterTest.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)

clean:
	rm -f $(TARGETS) *.class

