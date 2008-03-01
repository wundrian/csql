INCLUDES = -I$(top_srcdir)/include $(all_includes) 
METASOURCES = AUTO
lib_LTLIBRARIES = libcsqlnw.la
libcsqlnw_la_LDFLAGS = -avoid-version -module
libcsqlnw_la_SOURCES = NetworkTable.cxx UDPClient.cxx TCPClient.cxx \
	NetworkPacket.cxx SqlNetworkHandler.cxx UDPServer.cxx \
	TCPServer.cxx

libcsqlnw_a_LIBADD = $(top_builddir)/src/sql/libcsql.la
