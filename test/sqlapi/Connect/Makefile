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

INCL=  -I$(CSQL_INSTALL_ROOT)/install/include -I../../../include
LIBS= -L$(CSQL_INSTALL_ROOT)/lib -lcsqlsql -lcsql -lcsqlsqllog -lcsqlnw -lcsqlsqlnw

TARGETS = \
	test001 test001n\
	test002 test002n\
	test003 test003n\
	test004 test004n\
	test005 test005n\
	test006 test006n\
	test007 test007n\
	test008 test008n\
	test009 test009n\
	test010 test010n\
	test011 test011n


ifeq ($(PlatForm), supported)
all: $(TARGETS)
endif 

test001:conntest1.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test001n:conntest1.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test002:conntest2.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test002n:conntest2.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003:conntest3.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test003n:conntest3.c common.h 
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004:conntest4.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test004n:conntest4.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005:conntest5.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test005n:conntest5.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006:conntest6.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test006n:conntest6.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test007:conntest7.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test007n:conntest7.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test008:conntest8.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test008n:conntest8.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test009:conntest9.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test009n:conntest9.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test010:conntest10.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test010n:conntest10.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test011:conntest11.c common.h
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
test011n:conntest11.c common.h
	$(CPlus) -DNETWORK $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)

clean:
	rm -f ${TARGETS}
