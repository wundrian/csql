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


INCL=  -I$(CSQL_INSTALL_ROOT)/install/include -I../../../include
LIBS= -L$(CSQL_INSTALL_ROOT)/lib -lcacheload -lcsqlgw -lcsqlnw -lcsqlodbcadapter -lcsqlsqlnw   -lcsqlstorage -lcsqlbase -lcsqlsql -lcsqlsqllog

 
TARGETS = \
	insertconncsqldown 	selectconncsqldown 	updateconncsqldown	updateconncsqldownora	deleteconncsqldown	\
	insertprepcsqldown	insertprepcsqldownora	insertconncsqldownora   selectprepcsqldown 	updateprepcsqldown	deleteprepcsqldown	\
	updateprepcsqldownora	insertexeccsqldown 	insertexeccsqldownora	selectexeccsqldown 	updateexeccsqldown	deleteexeccsqldown	\
	updateexeccsqldownora
# insertprepmysqldown	selectprepmysqldown	updateprepmysqldown deleteprepmysqldown 
# insertexecmysqldown	selectexecmysqldown	updateexecmysqldown deleteexecmysqldown 
#    insertconnmysqldown	selectconnmysqldown	updateconnmysqldown deleteconnmysqldown 
	

ifeq ($(PlatForm), supported)
all: $(TARGETS)
else
all:
        echo "CSQL is not supported on $(OSNAME) platform"
endif

insertconncsqldown: insertconncsqldown.c 
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
insertconncsqldownora:  insertconncsqldownora.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
selectconncsqldown: selectconncsqldown.c 
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
updateconncsqldown: updateconncsqldown.c 
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
updateconncsqldownora: updateconncsqldownora.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
deleteconncsqldown: deleteconncsqldown.c 
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
#insertconnmysqldown: insertconnmysqldown.c 
#	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
#selectconnmysqldown: selectconnmysqldown.c 
#	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
#updateconnmysqldown: updateconnmysqldown.c 
##	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
#deleteconnmysqldown: deleteconnmysqldown.c 
#	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
insertprepcsqldown: insertprepcsqldown.c 
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
insertprepcsqldownora: insertprepcsqldownora.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
selectprepcsqldown: selectprepcsqldown.c 
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
updateprepcsqldown: updateprepcsqldown.c 
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
updateprepcsqldownora: updateprepcsqldownora.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
deleteprepcsqldown: deleteprepcsqldown.c 
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
#insertprepmysqldown: insertprepmysqldown.c 
#	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
#selectprepmysqldown: selectprepmysqldown.c 
#	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
#updateprepmysqldown: updateprepmysqldown.c 
#	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
#deleteprepmysqldown: deleteprepmysqldown.c 
#	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
insertexeccsqldown: insertexeccsqldown.c 
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
insertexeccsqldownora: insertexeccsqldownora.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
selectexeccsqldown: selectexeccsqldown.c 
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
updateexeccsqldown: updateexeccsqldown.c 
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
updateexeccsqldownora: updateexeccsqldownora.c
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
deleteexeccsqldown: deleteexeccsqldown.c 
	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
#insertexecmysqldown: insertexecmysqldown.c 
#	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
#selectexecmysqldown: selectexecmysqldown.c 
#	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
#updateexecmysqldown: updateexecmysqldown.c 
#	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)
#deleteexecmysqldown: deleteexecmysqldown.c 
#	$(CPlus) $(CPlusFlags) -o $@ $< $(INCL) $(LIBS) $(SYSLIBS)

clean:
	rm -f *.o ${TARGETS}
