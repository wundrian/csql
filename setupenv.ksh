
export CSQL_SRCROOT=`pwd`
export CSQL_CONFIG_FILE=$CSQL_SRCROOT/csql.conf

export CSQL_INSTALL_ROOT=$CSQL_SRCROOT/install
export PATH=$CSQL_INSTALL_ROOT/bin:$PATH
export LD_LIBRARY_PATH=$CSQL_INSTALL_ROOT/lib:/usr/local/lib:$LD_LIBRARY_PATH
export CLASSPATH=$CSQL_INSTALL_ROOT/lib/CSqlJdbcDriver.jar:.
mkdir -p /tmp/log/csql
mkdir -p /tmp/csql
touch /tmp/csql/csql.db
