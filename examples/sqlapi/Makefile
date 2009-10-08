OSNAME = $(shell  uname -s)
PlatForm=supported

ifeq ($(OSNAME), SunOS)
CPlus = g++
CPlusFlags = -O2 -w 
SYSLIBS=-ldl -lnsl -lsocket  -lposix4 
else 
ifeq ($(OSNAME), Linux)
CPlus = g++
CPlusFlags = -O2 -w
SYSLIBS= -rdynamic -lrt -lpthread -lcrypt
else
PlatForm=notsupported
all:
	echo "CSQL is not supported on $(OSNAME) platform"
endif
endif

INCL= -I$(CSQL_INSTALL_ROOT)/include
LIBS= -rdynamic -L$(CSQL_INSTALL_ROOT)/lib -lcsqlsql -lcsql -lcsqlsqllog -lcsqlnw -lcacheload -lcsqlgw -lcsqlodbcadapter -lcsqlsqlnw

TARGETS = sqlapiexample 

ifeq ($(PlatForm), supported)
all: $(TARGETS)
endif 

.c.o:.c
	$(CPlus) $(CPlusFlags) $(INCL) -c -o $@ $<

sqlapiexample: sqlapiexample.o
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)

clean:
	rm -f *.o $(TARGETS)
