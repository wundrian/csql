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
      jds.setMode((String)ref.get("mode").getContent());
      jds.setPort(Integer.parseInt((String)ref.get("port").getContent())); 
      jds.setUserName((String)ref.get("user").getContent());
      jds.setPassword((String)ref.get("password").getContent());
      String eUrl = (String)ref.get("url").getContent();
      if(eUrl == null) jds.explicityUrlUsed=false;
      else { jds.explicityUrlUsed = true; jds.setUrl(eUrl);}
      return jds;
    }
    else {
      return null;
    }
}

};
