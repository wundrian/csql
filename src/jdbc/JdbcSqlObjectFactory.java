package csql.jdbc;

import java.util.*;
import javax.naming.*;
import javax.naming.spi.*;
//import java.sql.*;



public class JdbcSqlObjectFactory implements ObjectFactory
{
    public Object getObjectInstance(Object refObj,
                                     Name name,
                                     Context nameCtx,
                                     Hashtable env)throws Exception {
    Reference ref = (Reference)refObj;
    if (ref.getClassName().equals("csql.jdbc.JdbcSqlDataSource")) {
      JdbcSqlDataSource jds = new JdbcSqlDataSource();
      jds.setServerName((String)ref.get("serverName").getContent());
      jds.setDatabaseName((String)ref.get("databaseName").getContent());
      return jds;
    }
    else {
      return null;
    }
}

};
