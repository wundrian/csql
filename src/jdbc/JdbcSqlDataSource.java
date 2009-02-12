package csql.jdbc;
 
import java.util.*;
import java.sql.*;
import javax.sql.*;
import javax.naming.*;
import java.io.*;
import java.lang.*;
import java.lang.Class;
//import java.sql.SQLException;

public class JdbcSqlDataSource implements javax.sql.DataSource, javax.naming.Referenceable, java.io.Serializable
{
    private String databaseName;
    private String dataSourceName;
    private String serverName; 
    private String password="manager";
    private String userName="root";
    transient JdbcSqlDriver driver;
    transient private PrintWriter printer;
    private int loginTimeout;
    private String jdbcurl="jdbc:csql";
    private int portno;//need to set default port

    public JdbcSqlDataSource()
    {
        
    }

    
/* Connection*/
    public Connection getConnection() throws SQLException
    {
        return this.getConnection(getUserName(),getPassword());
    }
    public Connection getConnection(String username, String password) throws SQLException
    {
        Properties info = new Properties();
        if (username != null)
            info.put("user", username);
        if (password != null)
            info.put("password", password);
        Connection conn =  findDriver().connect(jdbcurl, info);
      /*  if (conn == null)
           throw ;*/
        return conn;
      
    }
    
    JdbcSqlDriver findDriver() throws SQLException
    {
        String url = jdbcurl;
        if (driver == null || !driver.acceptsURL(url))
        {
            synchronized(this)
            {
                new JdbcSqlDriver();
		driver=(JdbcSqlDriver) DriverManager.getDriver(url);
            }
	}
        return driver;
    }
    public java.io.PrintWriter getLogWriter()  throws SQLException
    {
        return printer;
    }

    public void setLogWriter(java.io.PrintWriter out)
    {
        printer = out;
    }
    
    public void setLoginTimeout(int seconds)throws SQLException 
    {
                loginTimeout = seconds;
        
    }
    
    public int getLoginTimeout() 
    {
        return loginTimeout;
    }

    public Reference getReference() throws NamingException 
    {
        Reference ref = new Reference(this.getClass().getName(),"csql.jdbc.JdbcSqlObjectFactory", null);
        ref.add( new StringRefAddr("serverName", getServerName()) );
        ref.add( new StringRefAddr("databaseName",getDatabaseName()));
        return ref;
    }
    

    public String getServerName(){
        return serverName;
    }

    public void setServerName(String serverName){
        this.serverName=serverName;
    }

    public String getDatabaseName(){
        return databaseName;
    }

    public void setDatabaseName(String databaseName){
        this.databaseName=databaseName;
    }

    public String getUserName()
    {
        return userName;
    }

    public void setUserName(String un)
    {
        this.userName=un;
    }

    public String getPassword()
    {
        return password;
    }

    public void setPassword(String pw)
    {
        this.password=pw;
    }

    public boolean isWrapperFor(Class ifact) throws SQLException
    {

       return ifact.isInstance(this);
    }

    public <T> T unwrap(java.lang.Class<T> iface) throws SQLException
    {
            return iface.cast(this);
    }

}