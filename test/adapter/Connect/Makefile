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

INCL=  -I$(CSQL_INSTALL_ROOT)/install/include -I../../../include
LIBS= -L$(CSQL_INSTALL_ROOT)/lib -lcsqlsql -lcsql -lcsqlsqllog -lcsqlnw

TARGETS = \
	test001\
	test002\
	test003\
	test004\
	test005\
	test007\
	test010\
	test011


ifeq ($(PlatForm), supported)
all: $(TARGETS)
endif 

.c.o:.c
	$(CPlus) $(CPlusFlags) $(INCL) -c -o $@ $<

test001: conntest1.o 
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) -lcsqlsql -lcsqlsqllog -lcsqlodbcadapter -lcsql -lcsqlnw -lodbc -lcsqlgw $(SYSLIBS)
test002:conntest2.o
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS)  -lcsqlsql -lcsqlsqllog -lcsqlodbcadapter -lcsql -lcsqlnw -lodbc -lcsqlgw $(SYSLIBS)
test003:conntest3.o
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) -lcsqlsql -lcsqlsqllog -lcsqlodbcadapter -lcsql -lcsqlnw -lodbc -lcsqlgw  $(SYSLIBS)
test004:conntest4.o
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS)  -lcsqlsql -lcsqlsqllog -lcsqlodbcadapter -lcsql -lcsqlnw -lodbc -lcsqlgw $(SYSLIBS)
test005:conntest5.o
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) -lcsqlsql -lcsqlsqllog -lcsqlodbcadapter -lcsql -lcsqlnw -lodbc -lcsqlgw  $(SYSLIBS)
test007:conntest7.o
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) -lcsqlsql -lcsqlsqllog -lcsqlodbcadapter -lcsql -lcsqlnw -lodbc -lcsqlgw  $(SYSLIBS)
test010:conntest10.o
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) -lcsqlsql -lcsqlsqllog -lcsqlodbcadapter -lcsql -lcsqlnw -lodbc -lcsqlgw  $(SYSLIBS)
test011:conntest11.o
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) -lcsqlsql -lcsqlsqllog -lcsqlodbcadapter -lcsql -lcsqlnw -lodbc -lcsqlgw  $(SYSLIBS)

clean:
	rm -f *.o ${TARGETS}
