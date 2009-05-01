#include<AbsSqlStatement.h>
#include<SqlNwStatement.h>
#include<SqlFactory.h>
//sqlStmtPtr


/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class JSqlStatement */

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     JSqlStatement
 * Method:    alloc
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_csql_jdbc_JSqlStatement_alloc
  (JNIEnv *env, jobject obj, jint mode)
{
    jclass cls;
    jfieldID fid;

    AbsSqlStatement *stmt;
    switch(mode)
    {
        case 1:
        {
            stmt = SqlFactory::createStatement(CSql);
            break;
        }
        case 2:
        {
            stmt = SqlFactory::createStatement(CSqlGateway);
            break;
        }
        case 3:
        {
            stmt = SqlFactory::createStatement(CSqlAdapter);
            break;
        }
        default:
        {
            stmt = new SqlNwStatement();
            stmt->setInnerStatement(NULL);
        }
    }
    cls = env->GetObjectClass( obj );
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return;
    }
    env->SetLongField( obj, fid, (jlong) stmt );
    return;
}

/*
 * Class:     JSqlStatement
 * Method:    free
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_csql_jdbc_JSqlStatement_free
  (JNIEnv *env, jobject obj)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass(obj);
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return;
    }
    AbsSqlStatement *stmt = (AbsSqlStatement*) env->GetLongField( obj, fid );
    delete stmt;
    return;
}

/*
 * Class:     JSqlStatement
 * Method:    freeStmt
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_csql_jdbc_JSqlStatement_freeStmt
  (JNIEnv *env, jobject obj)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass(obj);
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return;
    }
    AbsSqlStatement *stmt = (AbsSqlStatement*) env->GetLongField( obj, fid);
    stmt->free();
    return;

}

/*
 * Class:     JSqlStatement
 * Method:    setConnectionPtr
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_csql_jdbc_JSqlStatement_setConnectionPtr
  (JNIEnv *env, jobject obj, jlong conn)
{

    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass(obj);
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return;
    }
    AbsSqlStatement *stmt = (AbsSqlStatement*) env->GetLongField( obj, fid);
    stmt->setConnection((AbsSqlConnection*) conn);
    return;
}

/*
 * Class:     JSqlStatement
 * Method:    prepare
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_csql_jdbc_JSqlStatement_prepare
  (JNIEnv *env, jobject obj, jstring stmt)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass(obj);
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return(-1);
    }
    AbsSqlStatement *s = (AbsSqlStatement*) env->GetLongField( obj, fid );
    jboolean isCopy = JNI_TRUE;
    char *stmtString = (char*) env->GetStringUTFChars(stmt, &isCopy );
    int rv = s->prepare(stmtString);
    return rv;
}

/*
 * Class:     JSqlStatement
 * Method:    isSelect
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_csql_jdbc_JSqlStatement_isSelect
  (JNIEnv *env, jobject obj)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass(obj);
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return(-1);
    }
    AbsSqlStatement *s = (AbsSqlStatement*) env->GetLongField( obj, fid );
    return s->isSelect();
}

/*
 * Class:     JSqlStatement
 * Method:    execute
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_csql_jdbc_JSqlStatement_execute
  (JNIEnv *env, jobject obj)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass(obj);
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return(-1);
    }
    AbsSqlStatement *stmt = (AbsSqlStatement*) env->GetLongField( obj, fid );
    int rowsAffected =0;
    DbRetVal rv = stmt->execute(rowsAffected);
    if (rv != OK) return -1;
    return rowsAffected;
}

/*
 * Class:     JSqlStatement
 * Method:    next
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_csql_jdbc_JSqlStatement_next
  (JNIEnv *env, jobject obj)
{
    jclass cls;
    jfieldID fid;
    cls = env->GetObjectClass(obj);
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return(-1);
    }
    AbsSqlStatement *stmt = (AbsSqlStatement*) env->GetLongField( obj, fid );
    void *tuple = stmt->next();
    if (NULL == tuple) return 0; else return 1;
}

/*
 * Class:     JSqlStatement
 * Method:    close
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_csql_jdbc_JSqlStatement_close
  (JNIEnv *env, jobject obj)
{
   //TODO::stmt currently does not support close
    jclass cls;
    jfieldID fid;
    cls = env->GetObjectClass(obj);
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return(-1);
    }
    AbsSqlStatement *stmt = (AbsSqlStatement*) env->GetLongField( obj, fid );
    int rv =0;
    rv  = stmt->close();
    return rv;
}

/*
 * Class:     JSqlStatement
 * Method:    setBoolean
 * Signature: (I)Z
 */
JNIEXPORT void JNICALL Java_csql_jdbc_JSqlStatement_setBoolean
  (JNIEnv *env, jobject obj, jint position, jint value)
{};

/*
 * Class:     JSqlStatement
 * Method:    setShort
 * Signature: (IS)V
 */
JNIEXPORT void JNICALL Java_csql_jdbc_JSqlStatement_setShort
  (JNIEnv *env, jobject obj, jint position, jshort value)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass( obj );
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return;
    }
    AbsSqlStatement *stmt = (AbsSqlStatement*) env->GetLongField( obj, fid );
    stmt->setShortParam(position, (short) value);
    return;
}

/*
 * Class:     JSqlStatement
 * Method:    setInt
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_csql_jdbc_JSqlStatement_setInt
  (JNIEnv *env, jobject obj, jint position, jint value)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass( obj );
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return;
    }
    AbsSqlStatement *stmt = (AbsSqlStatement*) env->GetLongField( obj, fid );
    stmt->setIntParam(position, (int) value);
    return;
}

/*
 * Class:     JSqlStatement
 * Method:    setLong
 * Signature: (IJ)V
 */
JNIEXPORT void JNICALL Java_csql_jdbc_JSqlStatement_setLong
  (JNIEnv *env, jobject obj, jint position, jlong value)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass( obj );
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return;
    }
    AbsSqlStatement *stmt = (AbsSqlStatement*) env->GetLongField( obj, fid );
    stmt->setLongLongParam(position, (long long) value);
    return;
}

/*
 * Class:     JSqlStatement
 * Method:    setByte
 * Signature: (IB)V
 */
JNIEXPORT void JNICALL Java_csql_jdbc_JSqlStatement_setByte
  (JNIEnv *env, jobject obj, jint position, jbyte value)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass( obj );
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return;
    }
    AbsSqlStatement *stmt = (AbsSqlStatement*) env->GetLongField( obj, fid );
    stmt->setByteIntParam(position, (ByteInt) value);
    return;
}
/*
 * Class:     JSqlStatement
 * Method:    setFloat
 * Signature: (IF)V
 */
JNIEXPORT void JNICALL Java_csql_jdbc_JSqlStatement_setFloat
  (JNIEnv *env, jobject obj, jint position, jfloat value)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass( obj );
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return;
    }
    AbsSqlStatement *stmt = (AbsSqlStatement*) env->GetLongField( obj, fid );
    stmt->setFloatParam(position, (float) value);
    return;
}

/*
 * Class:     JSqlStatement
 * Method:    setDouble
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_csql_jdbc_JSqlStatement_setDouble
  (JNIEnv *env, jobject obj, jint position, jdouble value)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass( obj );
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return;
    }
    AbsSqlStatement *stmt = (AbsSqlStatement*) env->GetLongField( obj, fid );
    stmt->setDoubleParam(position, (double) value);
    return;
}

/*
 * Class:     JSqlStatement
 * Method:    setString
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_csql_jdbc_JSqlStatement_setString
  (JNIEnv *env, jobject obj, jint position, jstring value)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass( obj );
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return;
    }

    jboolean isCopy = JNI_TRUE;
    char *valueStr = (char*) env->GetStringUTFChars( value, &isCopy );

    AbsSqlStatement *stmt = (AbsSqlStatement*) env->GetLongField( obj, fid );
    stmt->setStringParam(position, valueStr);
    return;
}

/*
 * Class:     JSqlStatement
 * Method:    setDate
 * Signature: (ILjava/sql/Date;)V
 */
JNIEXPORT void JNICALL Java_csql_jdbc_JSqlStatement_setDate
  (JNIEnv *env, jobject obj, jint position, jobject dateObj)

{
    jclass cls, datecls;
    jfieldID fid;
    jmethodID dateMethod;

    cls = env->GetObjectClass( obj );
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return;
    }
    AbsSqlStatement *stmt = (AbsSqlStatement*) env->GetLongField( obj, fid );

    // Get date, month, year from java object
    int d, m, y;
    datecls = env->GetObjectClass( dateObj );
    dateMethod = env->GetMethodID( datecls, "getYear", "()I");
    y = env->CallIntMethod( dateObj, dateMethod);
    dateMethod = env->GetMethodID( datecls, "getMonth", "()I");
    m = env->CallIntMethod( dateObj, dateMethod);
    dateMethod = env->GetMethodID( datecls, "getDate", "()I");
    d = env->CallIntMethod( dateObj, dateMethod);

    Date date(y + 1900, m + 1, d);
    stmt->setDateParam(position, date);

    return;
}


/*
 * Class:     JSqlStatement
 * Method:    setTime
 * Signature: (ILjava/sql/Time;)V
 */
JNIEXPORT void JNICALL Java_csql_jdbc_JSqlStatement_setTime
  (JNIEnv *env, jobject obj, jint position, jobject timeObj)

{
    jclass cls, timecls;
    jfieldID fid;
    jmethodID timeMethod;

    cls = env->GetObjectClass( obj );
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return;
    }
    AbsSqlStatement *stmt = (AbsSqlStatement*) env->GetLongField( obj, fid );

    // Get hour, minures, secs from java object
    int h, m, s;
    timecls = env->GetObjectClass( timeObj );
    timeMethod = env->GetMethodID( timecls, "getHours", "()I");
    h = env->CallIntMethod( timeObj, timeMethod);
    timeMethod = env->GetMethodID( timecls, "getMinutes", "()I");
    m = env->CallIntMethod( timeObj, timeMethod);
    timeMethod = env->GetMethodID( timecls, "getSeconds", "()I");
    s = env->CallIntMethod( timeObj, timeMethod);

    Time time(h, m, s, 0);
    stmt->setTimeParam(position, time);

    return;
}

/*
 * Class:     JSqlStatement
 * Method:    setTimestamp
 * Signature: (ILjava/sql/Timestamp;)V
 */
JNIEXPORT void JNICALL Java_csql_jdbc_JSqlStatement_setTimestamp
  (JNIEnv *env, jobject obj, jint position, jobject timeObj)

{
    jclass cls, timecls;
    jfieldID fid;
    jmethodID timeMethod;

    cls = env->GetObjectClass( obj );
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return;
    }
    AbsSqlStatement *stmt = (AbsSqlStatement*) env->GetLongField( obj, fid );

    // Get year, month, day, hour, minutes, secs from java object
    int y, mo, d, h, mn, s;
    timecls = env->GetObjectClass( timeObj );

    timeMethod = env->GetMethodID( timecls, "getYear", "()I");
    y = env->CallIntMethod( timeObj, timeMethod );
    timeMethod = env->GetMethodID( timecls, "getMonth", "()I");
    mo = env->CallIntMethod( timeObj, timeMethod );
    timeMethod = env->GetMethodID( timecls, "getDate", "()I");
    d = env->CallIntMethod( timeObj, timeMethod );
    timeMethod = env->GetMethodID( timecls, "getHours", "()I");
    h = env->CallIntMethod( timeObj, timeMethod);
    timeMethod = env->GetMethodID( timecls, "getMinutes", "()I");
    mn = env->CallIntMethod( timeObj, timeMethod);
    timeMethod = env->GetMethodID( timecls, "getSeconds", "()I");
    s = env->CallIntMethod( timeObj, timeMethod);

    TimeStamp timeStamp(y + 1900, mo + 1, d, h, mn, s, 0);
    stmt->setTimeStampParam(position, timeStamp);

    return;
}

/*
 * Class:     JSqlStatement
 * Method:    getShort
 * Signature: (I)S
 */
JNIEXPORT jshort JNICALL Java_csql_jdbc_JSqlStatement_getShort
  (JNIEnv *env, jobject obj, jint pos)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass( obj );
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0) 
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return(-1);
    }
    AbsSqlStatement *sqlStmt = (AbsSqlStatement*) env->GetLongField( obj, fid );

    // Validate pos
    // Handle conversion

    // Read data at column
    void *fvp = sqlStmt->getFieldValuePtr( pos );
    return( * ((short*)fvp) );
}

/*
 * Class:     JSqlStatement
 * Method:    setNull
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_csql_jdbc_JSqlStatement_setNull
  (JNIEnv *env, jobject obj, jint pos)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass(obj);
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return;
    }
    AbsSqlStatement *s = (AbsSqlStatement*) env->GetLongField( obj, fid );
    s->setNull(pos);
    return;
}



/*
 * Class:     csql_jdbc_JSqlStatement
 * Method:    isNull
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_csql_jdbc_JSqlStatement_isNull
  (JNIEnv *env, jobject obj, jint pos)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass(obj);
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return(-1);
    }
    AbsSqlStatement *s = (AbsSqlStatement*) env->GetLongField( obj, fid );
    return s->isFldNull(pos);
}


/*
 * Class:     csql_jdbc_JSqlStatement
 * Method:    findColumn
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_csql_jdbc_JSqlStatement_findColumn
  (JNIEnv *env, jobject obj, jstring value)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass(obj);
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return(-1);
    }

    jboolean isCopy = JNI_TRUE;
    char *valueStr = (char*) env->GetStringUTFChars( value, &isCopy );
 
    AbsSqlStatement *s = (AbsSqlStatement*) env->GetLongField( obj, fid );
    return s->getFldPos(valueStr); 
}

/*
 * Class:     csql_jdbc_JSqlStatement
 * Method:    getParamFldName
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_csql_jdbc_JSqlStatement_getParamFldName
  (JNIEnv *env, jobject obj, jint pos)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass(obj);
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return((jstring) 0);
    }
    AbsSqlStatement *s = (AbsSqlStatement*) env->GetLongField( obj, fid );
    FieldInfo *field = new FieldInfo();
    DbRetVal rv = s->getParamFldInfo(pos,field);
    if(rv!=OK)return NULL;
    _jstring *name = env->NewStringUTF( (char*) field->fldName );
    delete field;
    return name;
}

/*
 * Class:     csql_jdbc_JSqlStatement
 * Method:    getTotalparam
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_csql_jdbc_JSqlStatement_getTotalparam
  (JNIEnv *env, jobject obj)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass(obj);
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return(-1);
    }
    AbsSqlStatement *s = (AbsSqlStatement*) env->GetLongField( obj, fid );
      
    return (s->noOfParamFields());    
}

/*
 * Class:     csql_jdbc_JSqlStatement
 * Method:    getType
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_csql_jdbc_JSqlStatement_getType
  (JNIEnv *env, jobject obj, jint pos)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass(obj);
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return(-1);
    }
    AbsSqlStatement *s = (AbsSqlStatement*) env->GetLongField( obj, fid );

    FieldInfo *field = new FieldInfo();
    DbRetVal rv = s->getParamFldInfo(pos,field);
    if(rv!=OK)return 100;
    int type = field->type;
    delete field;
    return type;
}

/*
 * Class:     csql_jdbc_JSqlStatement
 * Method:    isNullable
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_csql_jdbc_JSqlStatement_isNullable
  (JNIEnv *env, jobject obj, jint pos)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass(obj);
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return(-1);
    }
    AbsSqlStatement *s = (AbsSqlStatement*) env->GetLongField( obj, fid );

    FieldInfo *field = new FieldInfo();
    DbRetVal rv = s->getParamFldInfo(pos,field);
    if(rv!=OK)return (-1);
    if(field->isNull){
        delete field;
        return true;
    }else{
        delete field;
        return false;
    }        
}


/*
 * Class:     csql_jdbc_JSqlStatement
 * Method:    getTotalProjFld
 * Signature: ()I
 */

JNIEXPORT jint JNICALL Java_csql_jdbc_JSqlStatement_getTotalProjFld
  (JNIEnv *env, jobject obj)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass(obj);
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return(-1);
    }
    AbsSqlStatement *s = (AbsSqlStatement*) env->GetLongField( obj, fid );
    
    return (s->noOfProjFields());

}

/*
 * Class:     csql_jdbc_JSqlStatement
 * Method:    getProjFldType
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_csql_jdbc_JSqlStatement_getProjFldType
  (JNIEnv *env, jobject obj, jint pos)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass(obj);
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return(-1);
    }
    AbsSqlStatement *s = (AbsSqlStatement*) env->GetLongField( obj, fid );
    
    FieldInfo *field = new FieldInfo();
    s->getProjFldInfo(pos,field);
    int type = field->type;
    delete field;

    return type;
}


/*
 * Class:     csql_jdbc_JSqlStatement
 * Method:    isFldNullable
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_csql_jdbc_JSqlStatement_isFldNullable
  (JNIEnv *env, jobject obj, jint pos)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass(obj);
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return(-1);
    }
    AbsSqlStatement *s = (AbsSqlStatement*) env->GetLongField( obj, fid );
    FieldInfo *field = new FieldInfo();
    s->getProjFldInfo(pos,field);
    bool nul = field->isNull;
    delete field;

    return nul;
}


/*
 * Class:     csql_jdbc_JSqlStatement
 * Method:    getProjFldName
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_csql_jdbc_JSqlStatement_getProjFldName
  (JNIEnv *env, jobject obj, jint pos)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass(obj);
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return( (jstring) 0 );
    }
    AbsSqlStatement *s = (AbsSqlStatement*) env->GetLongField( obj, fid );
    FieldInfo *field = new FieldInfo();
    s->getProjFldInfo(pos,field);
    _jstring *name = env->NewStringUTF( (char*) field->fldName );
    delete field;
    return name;
}


/*
 * Class:     csql_jdbc_JSqlStatement
 * Method:    getTableName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_csql_jdbc_JSqlStatement_getTableName
  (JNIEnv *env, jobject obj)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass(obj);
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return( (jstring) 0 );
    }
    AbsSqlStatement *s = (AbsSqlStatement*) env->GetLongField( obj, fid );


   return NULL;
}



/*
 * Class:     JSqlStatement
 * Method:    getInt
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_csql_jdbc_JSqlStatement_getInt
  (JNIEnv *env, jobject obj, jint pos)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass( obj );
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0) 
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return(-1);
    }
    AbsSqlStatement *sqlStmt = (AbsSqlStatement*) env->GetLongField( obj, fid );

    // Validate pos
    // Handle conversion

    // Read data at column
    void *fvp = sqlStmt->getFieldValuePtr( pos );
    return( * ((int*)fvp) );
}

/*
 * Class:     JSqlStatement
 * Method:    getLong
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_csql_jdbc_JSqlStatement_getLong
  (JNIEnv *env, jobject obj, jint pos)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass( obj );
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0) 
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return(-1);
    }
    AbsSqlStatement *sqlStmt = (AbsSqlStatement*) env->GetLongField( obj, fid );

    // Validate pos
    // Handle conversion

    // Read data at column
    void *fvp = sqlStmt->getFieldValuePtr( pos );
    return( * ((long*)fvp) );
}

/*
 * Class:     JSqlStatement
 * Method:    getByte
 * Signature: (I)B
 */
JNIEXPORT jbyte JNICALL Java_csql_jdbc_JSqlStatement_getByte
  (JNIEnv *env, jobject obj, jint pos)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass( obj );
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0) 
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return(-1);
    }
    AbsSqlStatement *sqlStmt = (AbsSqlStatement*) env->GetLongField( obj, fid );

    // Validate pos
    // Handle conversion

    // Read data at column
    void *fvp = sqlStmt->getFieldValuePtr( pos );
    return( * ((char*)fvp) );
}

/*
 * Class:     JSqlStatement
 * Method:    getFloat
 * Signature: (I)F
 */
JNIEXPORT jfloat JNICALL Java_csql_jdbc_JSqlStatement_getFloat
  (JNIEnv *env, jobject obj, jint pos)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass( obj );
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0) 
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return(-1);
    }
    AbsSqlStatement *sqlStmt = (AbsSqlStatement*) env->GetLongField( obj, fid );

    // Validate pos
    // Handle conversion

    // Read data at column
    void *fvp = sqlStmt->getFieldValuePtr( pos );
    return( * ((float*)fvp) );
}

/*
 * Class:     JSqlStatement
 * Method:    getDouble
 * Signature: (I)D
 */
JNIEXPORT jdouble JNICALL Java_csql_jdbc_JSqlStatement_getDouble
  (JNIEnv *env, jobject obj, jint pos)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass( obj );
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0) 
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return(-1);
    }
    AbsSqlStatement *sqlStmt = (AbsSqlStatement*) env->GetLongField( obj, fid );

    // Validate pos
    // Handle conversion

    // Read data at column
    void *fvp = sqlStmt->getFieldValuePtr( pos );
    return( * ((double*)fvp) );
}

/*
 * Class:     JSqlStatement
 * Method:    getString
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_csql_jdbc_JSqlStatement_getString
  (JNIEnv *env, jobject obj, jint pos)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass( obj );
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0) 
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return( (jstring) 0 );
    }
    AbsSqlStatement *sqlStmt = (AbsSqlStatement*) env->GetLongField( obj, fid );

    // Validate pos
    // Handle conversion

    // Read data at column
    void *fvp = sqlStmt->getFieldValuePtr( pos );
    return( env->NewStringUTF( (char*) fvp ) );
}

/*
 * Class:     JSqlStatement
 * Method:    getBytes
 * Signature: (I)[B
 */
JNIEXPORT jbyteArray JNICALL Java_csql_jdbc_JSqlStatement_getBytes
  (JNIEnv *, jobject, jint);

/*
 * Class:     JSqlStatement
 * Method:    getDate
 * Signature: (I)Ljava/sql/Date;
 */
JNIEXPORT jobject JNICALL Java_csql_jdbc_JSqlStatement_getDate
  (JNIEnv *env, jobject obj, jint pos)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass( obj );
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0) 
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return( (jobject) 0 );
    }
    AbsSqlStatement *sqlStmt = (AbsSqlStatement*) env->GetLongField( obj, fid );

    // Validate pos
    // Handle conversion

    // Read data at column
    void *fvp = sqlStmt->getFieldValuePtr( pos );

    // Create Java Object
    jclass cDate = env->FindClass("java/sql/Date"); 
    jmethodID methodID = env->GetMethodID( cDate, "<init>", "(III)V" );
    jobject dateObj;

    Date *dt = (Date*) fvp;
    dateObj = env->NewObject( cDate, methodID, 
        (jint) dt->year()-1900, (jint) dt->month() - 1, 
        (jint) dt->dayOfMonth() );

    return( dateObj );
}

/*
 * Class:     JSqlStatement
 * Method:    getTime
 * Signature: (I)Ljava/sql/Time;
 */
JNIEXPORT jobject JNICALL Java_csql_jdbc_JSqlStatement_getTime
  (JNIEnv *env, jobject obj, jint pos)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass( obj );
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0) 
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return( (jobject) 0 );
    }
    AbsSqlStatement *sqlStmt = (AbsSqlStatement*) env->GetLongField( obj, fid );

    // Validate pos
    // Handle conversion

    // Read data at column
    void *fvp = sqlStmt->getFieldValuePtr( pos );

    // Create Java Object
    jclass cTime = env->FindClass("java/sql/Time"); 
    jmethodID methodID = env->GetMethodID( cTime, "<init>", "(III)V" );
    jobject timeObj;

    Time *tm = (Time*) fvp;
    timeObj = env->NewObject( cTime, methodID, 
        (jint) tm->hours(), (jint) tm->minutes(), 
        (jint) tm->seconds() );

    return( timeObj );
}

/*
 * Class:     JSqlStatement
 * Method:    getTimestamp
 * Signature: (I)Ljava/sql/Timestamp;
 */
JNIEXPORT jobject JNICALL Java_csql_jdbc_JSqlStatement_getTimestamp
  (JNIEnv *env, jobject obj, jint pos)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass( obj );
    fid = env->GetFieldID( cls, "sqlStmtPtr", "J");
    if (fid == 0) 
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return( (jobject) 0 );
    }
    AbsSqlStatement *sqlStmt = (AbsSqlStatement*) env->GetLongField( obj, fid );

    // Validate pos
    // Handle conversion

    // Read data at column
    void *fvp = sqlStmt->getFieldValuePtr( pos );

    // Create Java Object
    jclass cTimestamp = env->FindClass("java/sql/Timestamp"); 
    jmethodID methodID = env->GetMethodID( cTimestamp, "<init>", "(IIIIIII)V" );
    jobject timeObj;

    TimeStamp *ts = (TimeStamp*) fvp;
    timeObj = env->NewObject( cTimestamp, methodID, \
        (jint) ts->year()-1900, (jint) ts->month() - 1, (jint) ts->dayOfMonth(), \
        (jint) ts->hours(), (jint) ts->minutes(), (jint) ts->seconds(), (jint) 0 );

    return( timeObj );
}

/*
 * Class:     JSqlStatement
 * Method:    getBoolean
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_csql_jdbc_JSqlStatement_getBoolean
  (JNIEnv *, jobject, jint);

#ifdef __cplusplus
}
#endif
