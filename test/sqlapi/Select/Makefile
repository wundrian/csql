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
	test006\
	test007\
	test008\
	test009\
	test010



ifeq ($(PlatForm), supported)
all: $(TARGETS)
endif 

.c.o:.c
	$(CPlus) $(CPlusFlags) $(INCL) -c -o $@ $<

test001: selecttest1.o 
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) -lcsqlsql -lcsqlsqllog -lcsqlodbcadapter -lcsql -lcsqlnw -lodbc -lcsqlgw $(SYSLIBS)
test002:selecttest2.o
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS)  -lcsqlsql -lcsqlsqllog -lcsqlodbcadapter -lcsql -lcsqlnw -lodbc -lcsqlgw $(SYSLIBS)
test003:selecttest3.o
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) -lcsqlsql -lcsqlsqllog -lcsqlodbcadapter -lcsql -lcsqlnw -lodbc -lcsqlgw  $(SYSLIBS)
test004:selecttest4.o
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS)  -lcsqlsql -lcsqlsqllog -lcsqlodbcadapter -lcsql -lcsqlnw -lodbc -lcsqlgw $(SYSLIBS)
test005:selecttest5.o
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) -lcsqlsql -lcsqlsqllog -lcsqlodbcadapter -lcsql -lcsqlnw -lodbc -lcsqlgw  $(SYSLIBS)
test006:selecttest6.o
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) -lcsqlsql -lcsqlsqllog -lcsqlodbcadapter -lcsql -lcsqlnw -lodbc -lcsqlgw  $(SYSLIBS)
test007:selecttest7.o
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) -lcsqlsql -lcsqlsqllog -lcsqlodbcadapter -lcsql -lcsqlnw -lodbc -lcsqlgw  $(SYSLIBS)
test008:selecttest8.o
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) -lcsqlsql -lcsqlsqllog -lcsqlodbcadapter -lcsql -lcsqlnw -lodbc -lcsqlgw  $(SYSLIBS)
test009:selecttest9.o
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) -lcsqlsql -lcsqlsqllog -lcsqlodbcadapter -lcsql -lcsqlnw -lodbc -lcsqlgw  $(SYSLIBS)
test010:selecttest10.o
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) -lcsqlsql -lcsqlsqllog -lcsqlodbcadapter -lcsql -lcsqlnw -lodbc -lcsqlgw  $(SYSLIBS)
	
clean:
	rm -f *.o ${TARGETS}
