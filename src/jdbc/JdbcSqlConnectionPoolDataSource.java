package csql.jdbc;
import java.sql.Connection;
import java.sql.SQLException;

import javax.sql.ConnectionPoolDataSource;
import javax.sql.PooledConnection;
/**
 * 
 * @author bijaya
 */

public class JdbcSqlConnectionPoolDataSource extends JdbcSqlDataSource implements ConnectionPoolDataSource
{
    public synchronized PooledConnection getPooledConnection()throws SQLException {
                Connection connection = getConnection();
                JdbcSqlPooledConnection pooledConnection = new JdbcSqlPooledConnection(connection);
                return pooledConnection;
    }
    public synchronized PooledConnection getPooledConnection(String user, String passward)throws SQLException 
    {
                Connection connection = getConnection(user,passward);
                JdbcSqlPooledConnection pooledConnection = new JdbcSqlPooledConnection(connection);
                return pooledConnection;
    }
}
