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
LIBS= -L$(CSQL_INSTALL_ROOT)/lib -lcsqlsql -lcsqlsqllog -lcsqlodbcadapter -lcsql -lcsqlnw -lodbc -lcsqlgw -lcacheload
 
TARGETS = \
	insertconncsqldown 	selectconncsqldown 	updateconncsqldown	deleteconncsqldown	\
	insertprepcsqldown 	selectprepcsqldown 	updateprepcsqldown	deleteprepcsqldown	\
	insertexeccsqldown 	selectexeccsqldown 	updateexeccsqldown	deleteexeccsqldown
# insertprepmysqldown	selectprepmysqldown	updateprepmysqldown deleteprepmysqldown 
# insertexecmysqldown	selectexecmysqldown	updateexecmysqldown deleteexecmysqldown 
#    insertconnmysqldown	selectconnmysqldown	updateconnmysqldown deleteconnmysqldown 
	

ifeq ($(PlatForm), supported)
all: $(TARGETS)
endif 

.c.o:.c
	$(CPlus) $(CPlusFlags) $(INCL) -c -o $@ $<

insertconncsqldown: insertconncsqldown.o 
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)
selectconncsqldown: selectconncsqldown.o 
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)
updateconncsqldown: updateconncsqldown.o 
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)
deleteconncsqldown: deleteconncsqldown.o 
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)
#insertconnmysqldown: insertconnmysqldown.o 
#	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)
#selectconnmysqldown: selectconnmysqldown.o 
#	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)
#updateconnmysqldown: updateconnmysqldown.o 
##	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)
#deleteconnmysqldown: deleteconnmysqldown.o 
#	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)
insertprepcsqldown: insertprepcsqldown.o 
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)
selectprepcsqldown: selectprepcsqldown.o 
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)
updateprepcsqldown: updateprepcsqldown.o 
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)
deleteprepcsqldown: deleteprepcsqldown.o 
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)
#insertprepmysqldown: insertprepmysqldown.o 
#	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)
#selectprepmysqldown: selectprepmysqldown.o 
#	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)
#updateprepmysqldown: updateprepmysqldown.o 
#	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)
#deleteprepmysqldown: deleteprepmysqldown.o 
#	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)
insertexeccsqldown: insertexeccsqldown.o 
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)
selectexeccsqldown: selectexeccsqldown.o 
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)
updateexeccsqldown: updateexeccsqldown.o 
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)
deleteexeccsqldown: deleteexeccsqldown.o 
	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)
#insertexecmysqldown: insertexecmysqldown.o 
#	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)
#selectexecmysqldown: selectexecmysqldown.o 
#	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)
#updateexecmysqldown: updateexecmysqldown.o 
#	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)
#deleteexecmysqldown: deleteexecmysqldown.o 
#	$(CPlus) $(CPlusFlags) -o $@ $< $(LIBS) $(SYSLIBS)

clean:
	rm -f *.o ${TARGETS}
