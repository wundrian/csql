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
    static
    {
        try
        {
            DriverManager.registerDriver(new JdbcSqlDriver());
        }
        catch (Exception e)
        {
            System.out.println ("CSql JDBC Driver: " + e);
        }
    }

    private String databaseName="csql";
    private String dataSourceName;
    private String serverName="localhost";
    private String password="manager";
    private String userName="root";
    private String mode="";
    transient JdbcSqlDriver driver;
    transient private PrintWriter printer;
    private int loginTimeout;
    private String jdbcurl="jdbc:";
    private int portno = 5678;
    boolean explicityUrlUsed=false;
    private String explicityUrl="";
    public JdbcSqlDataSource()
    {
        
    }

    
/* Connection*/
    public Connection getConnection() throws SQLException
    {
        return this.getConnection(getUserName(),getPassword());
    }
    public synchronized Connection getConnection(String username, String password) throws SQLException
    {
        String url="";
        if(!explicityUrlUsed){
            url = jdbcurl+ mode +"://" + serverName + ":" + portno +"/" + databaseName;
        } else {
            url = explicityUrl;
        }
        Properties info = new Properties();
        if (username != null)
            info.put("user", username);
        if (password != null)
            info.put("password", password);
        Connection conn =  findDriver().connect(url, info);
      /*  if (conn == null)
           throw ;*/
        return conn;
      
    }
    public void setUrl(String url)
    {
         if(explicityUrlUsed) {
            explicityUrl = url;
         }
    }
    public String getUrl()
    {
        String url="";
        if(!explicityUrlUsed){
            url = jdbcurl+ mode +"://" + serverName + ":" + portno +"/" + databaseName;
        } else {
            url = explicityUrl;
        }
        return url;
    }

    public void setPort(int port)
    {
         this.portno = port;
    }
    public int getPort()
    {
         return this.portno ;
    }

    public void setMode(String mode)
    {
         this.mode = mode;
    }
    public String getMode()
    {
         return this.mode ;
    }
 
    JdbcSqlDriver findDriver() throws SQLException
    {
        String url = getUrl();
        if (driver == null || !driver.acceptsURL(url))
        {
            //new JdbcSqlDriver();
            driver=(JdbcSqlDriver) DriverManager.getDriver(url);
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
        ref.add( new StringRefAddr("mode",getMode()));
        ref.add( new StringRefAddr("port",""+getPort()));
        ref.add( new StringRefAddr("user",getUserName()));
        ref.add( new StringRefAddr("password",getPassword()));
        ref.add( new StringRefAddr("url",getUrl()));
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
