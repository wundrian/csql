
OSNAME = $(shell  uname -s)
PlatForm=supported

ifeq ($(OSNAME), SunOS)
CPlus = CC
CPlusFlags = -O2 -w -mt -xarch=v8
SYSLIBS=-ldl -lnsl -lsocket  -lposix4
else
ifeq ($(OSNAME), Linux)
CPlus = g++
CPlusFlags = -g -w
SYSLIBS= -rdynamic -lrt -lpthread -lcrypt
else
PlatForm=notsupported
all:
        echo "CSQL is not supported on $(OSNAME) platform"
endif
endif

INCL= -I$(CSQL_INSTALL_ROOT)/include
LIBS= -L$(CSQL_INSTALL_ROOT)/lib -lcsql

TARGETS = \
        test001  \
        test002  \
        test003  \
        test004  \
        test005  \
        test006  \
        test007  
 
       

ifeq ($(PlatForm), supported)
all: $(TARGETS)
endif

test001: inttest.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test002: longtest.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003: longlongtest.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004: shorttest.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005: byteinttest.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006: floattest.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test007: doubletest.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)

clean:
	rm -f $(TARGETS)

