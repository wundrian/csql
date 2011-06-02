INCLUDES = -I$(top_srcdir)/include $(all_includes)
METASOURCES = AUTO
lib_LTLIBRARIES = libcsqlbase.la
libcsqlbase_la_LDFLAGS = -avoid-version -module
libcsqlbase_la_SOURCES = Util.cxx FixedHeapAllocator.cxx VarHeapAllocator.cxx \
	Config.cxx HashMap.cxx  DataType.cxx TypeCompare.cxx \
	Date.cxx Time.cxx  Timestamp.cxx TypeConvert.cxx \
	Debug.cxx Logger.cxx Mutex.cxx os.cxx 
