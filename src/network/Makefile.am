INCLUDES = -I$(top_srcdir)/include $(all_includes) 
METASOURCES = AUTO
lib_LTLIBRARIES = libcsqlnw.la 
libcsqlnw_la_LDFLAGS = -version-info 2:4:0 -module
libcsqlnw_la_SOURCES = NetworkTable.cxx UDPClient.cxx TCPClient.cxx \
	NetworkPacket.cxx SqlNetworkHandler.cxx UDPServer.cxx \
	TCPServer.cxx
