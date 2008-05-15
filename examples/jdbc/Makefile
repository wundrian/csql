OSNAME = $(shell  uname -s)
JAVAC = javac
TARGETS = jdbcexample gwexample
all: ${TARGETS}
jdbcexample: jdbcexample.java
	javac jdbcexample.java
gwexample: gwexample.java
	javac gwexample.java
clean:
	rm -rf *.class
