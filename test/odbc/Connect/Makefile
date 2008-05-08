OSNAME = $(shell  uname -s)
PlatForm=supported

ifeq ($(OSNAME), SunOS)
CPlus = CC
CPlusFlags = -O2 -w -mt -xarch=v8
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

LIBS= -L$(CSQL_INSTALL_ROOT)/lib -lcsqlodbc

TARGETS =  test001 test002 test003 test004 test005 test006 test007 

ifeq ($(PlatForm), supported)
all: $(TARGETS)
endif

.c.o:.c
	$(CPlus) $(CPlusFlags) $(INCL) -c -o $@ $<

test001: odbcconnect1.o 
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)

test002:odbcconnect2.o 
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)
test003:odbcconnect3.o
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)
test004:odbcconnect4.o
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)
test005:odbcconnect5.o
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)
test006:odbcconnect6.o
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)
test007:odbcconnect7.o
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)

clean:
	rm -f *.o $(TARGETS)

