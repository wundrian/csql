INCLUDES = -I$(top_srcdir)/include $(all_includes)
METASOURCES = AUTO
lib_LTLIBRARIES = libcacheload.la
libcacheload_la_SOURCES = CacheTableLoader.cxx TableConfig.cxx
libcacheload_la_LDFLAGS = -L$(top_srcdir)/src/base -lcsqlbase -avoid-version -module -lodbc
