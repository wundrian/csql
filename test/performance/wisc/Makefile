CC=g++ -g
INCL= -I$(CSQL_INSTALL_ROOT)/include
#LIBS= -L$(CSQL_INSTALL_ROOT)/lib -L/home/praba/csql/mysql-connector-odbc-3.51.23-linux-x86-32bit/lib -lcrypt  -lrt  -lmyodbc3
LIBS= -L$(CSQL_INSTALL_ROOT)/lib -lcrypt  -lrt  -lcsqlodbc -lcacheload
ALL_CC_FLAG=$(INCL) $(LIBS) 
JAVAC = javac -g:none

all: odbcBench JDBCBench JDBCPopulate

odbcBench:  odbcBench.c 
	$(CC) $(ALL_CC_FLAG) -o odbcBench odbcBench.c
JDBCBench: JDBCBench.java
	$(JAVAC) JDBCBench.java

JDBCPopulate: JDBCPopulate.java
	$(JAVAC) JDBCPopulate.java
clean:
	rm -rf  *.o odbcBench 
	rm -rf  *.class
