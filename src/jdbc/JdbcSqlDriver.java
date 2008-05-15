package csql.jdbc;
import java.util.Properties;
import java.util.StringTokenizer;
import java.sql.Driver;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Connection;
import java.sql.DriverPropertyInfo;

public final class JdbcSqlDriver extends JSqlError implements Driver, JSqlErrorType
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
    public int mode;
    public boolean acceptsURL(String url)
    {
        //pattern jdbc:csql:
        String trimURL = url.toLowerCase().trim();
        StringTokenizer tokens = new StringTokenizer(trimURL, ":", false);
        int tokenNo =1;
        while(tokens.hasMoreTokens())
        {
            String t = tokens.nextToken().trim();
            switch(tokenNo)
            {
                case 1:
                        if( t.equalsIgnoreCase("jdbc") )
                        {
                            tokenNo++;
                            continue;
                        }
                        break;
                case 2:
                        if( t.equalsIgnoreCase("csql") )
                        {
                            tokenNo++;
                            mode = 1;
                            continue;
                        }else if (t.equalsIgnoreCase("gateway") )
                        {
                            tokenNo++;
                            mode = 2;
                            continue;
                        }
                        break;
                default:
                        tokenNo++;
                        break;
            }
        }
        if(tokenNo != 3) return false; 
        return true;
    }
    public Connection connect(String connectString, Properties info) throws SQLException
    {
        String uName, pword;

        if( info.isEmpty() )
            throw getException(CSQL_AUTHEN_ERR);

        if(!acceptsURL(connectString))
            throw getException(CSQL_AUTHEN_ERR);

        //System.loadLibrary("crypt");
        //System.loadLibrary("csql");
        //System.loadLibrary("csqlsql");
        System.loadLibrary("csqljdbc");

        uName = info.getProperty("user");
        pword = info.getProperty("password");
        JdbcSqlConnection con = new JdbcSqlConnection(mode, uName, pword);
        return((Connection) con);
    }
    public DriverPropertyInfo[] getPropertyInfo (String connectString,
            java.util.Properties info ) throws SQLException
    {
        return null;
    }
    public int getMajorVersion()
    {
        return 1;
    }
    public int getMinorVersion()
    {
        return 0;
    }
    public boolean jdbcCompliant()
    {
        return false;
    }
}
