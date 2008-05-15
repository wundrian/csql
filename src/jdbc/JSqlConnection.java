package csql.jdbc;
public class JSqlConnection
{
    public long sqlConPtr;

    public long getPtr()
    {
        return sqlConPtr;
    }
    public void setPtr( long ptr )
    {
        sqlConPtr = ptr;
    }

    // Wrappers 
    public native void alloc(int mode);
    public native void free();

    public native int connect(String user, String pass);
    public native int disconnect();
    public native boolean isOpen();

    public native int beginTrans(int isoLevel);
    public native int commit();
    public native int rollback();
};
