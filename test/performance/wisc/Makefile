CC=g++
INCL= -I$(CSQL_INSTALL_ROOT)/include
LIBS= -L$(CSQL_INSTALL_ROOT)/lib -lcsqlodbc -lcrypt
ALL_CC_FLAG=$(INCL) $(LIBS)
JAVAC = javac

all: odbcBench JDBCBench 

relBench.o: wbench.c
	$(CC) -o relBench.o $(ALL_CC_FLAG) -c wbench.c 

wiscTimer.o:wiscTimer.c
	$(CC) -o wiscTimer.o $(ALL_CC_FLAG) -c wiscTimer.c

support.o: support.c
	$(CC) -o support.o $(ALL_CC_FLAG)  -c support.c

odbcDB.o: odbcDB.c odbcDB.h
	$(CC) -o odbcDB.o $(ALL_CC_FLAG) -c odbcDB.c -I$(BLZ_BASE)/sql/include

odbcBench.o: wbench.c
	$(CC) -o odbcBench.o $(ALL_CC_FLAG) -c wbench.c 

odbcBench: odbcDB.o odbcBench.o wiscTimer.o support.o
	$(CC) $(ALL_CC_FLAG) -o odbcBench odbcDB.o odbcBench.o wiscTimer.o support.o 
JDBCBench: JDBCBench.java
	$(JAVAC) JDBCBench.java

clean:
	rm -rf  *.o odbcBench 
	rm -rf  *.class
