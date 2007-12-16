
OSNAME = $(shell  uname -s)
PlatForm=supported

ifeq ($(OSNAME), SunOS)
CPlus = CC
CPlusFlags = -O2 -w -mt -xarch=v8
SYSLIBS=-ldl -lnsl -lsocket  -lposix4
JAVAC = javac
else
ifeq ($(OSNAME), Linux)
CPlus = g++
CPlusFlags = -O2 -w 
JAVAC = javac
SYSLIBS= -rdynamic -lrt -lpthread -lcrypt
else
PlatForm=notsupported
all:
        echo "CSQL is not supported on $(OSNAME) platform"
endif
endif

INCL= -I$(CSQL_INSTALL_ROOT)/include
LIBS= -L$(CSQL_INSTALL_ROOT)/lib -rdynamic -lcsql

TARGETS = \
        DMLTest \
        DMLTestChar \
        DMLThreadTest \
        JDBCTest \
	Range
       

ifeq ($(PlatForm), supported)
all: $(TARGETS)
endif

DMLTest: DMLTest.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
DMLTestChar: DMLTestChar.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
DMLThreadTest: DMLThreadTest.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
Range: Range.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
JDBCTest: JDBCTest.java
	$(JAVAC) JDBCTest.java

clean:
	rm -f $(TARGETS) *.class

