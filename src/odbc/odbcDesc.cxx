/*  Class CSqlOdbcDescList
    Description: Generic Descriptor manager. 

    Functions:
        CSqlOdbcDescList::delDesc();
        CSqlOdbcDescList::freeAllDesc();
        CSqlOdbcDescList::getDescWithColNum();

        CSqlOdbcDesc::CSqlOdbcDesc();
*/

#include "odbcCommon.h"

// Class CSqlOdbcDescList Member functions
//----------------------------------
// Delete descriptor from list
SQLRETURN CSqlOdbcDescList::delDesc( CSqlOdbcDesc *node )
{
    CSqlOdbcDescList::iterator iter;
    iter = this->begin();
    while( iter != this->end() )
    {
        if( *iter == node )
        {
            delete node;
            this->erase( iter );
            return( SQL_SUCCESS );
        }
        iter++;
    }

    return(SQL_ERROR);
}

void CSqlOdbcDescList::freeAllDesc( void )
{
    int size=(int)this->size();
    if(size  > 0)
    {
	    CSqlOdbcDescList::iterator iter;
	    iter = this->begin();
	    while( iter != this->end() )
	    {
		    if(type_ == SQL_DESC_IMP)
		    {
			    if((*iter)->dataPtr_!= NULL)
			    {
				    if((*iter)->cType_ == SQL_C_CHAR || (*iter)->cType_ == SQL_C_BINARY)
					    delete []  (*iter)->dataPtr_;
				    else
					    delete (*iter)->dataPtr_;
				    (*iter)->dataPtr_=NULL;
			    }
		    }
		    delete *iter;
		    *iter=NULL;
		    iter++;
	    }
	    this->clear();
    }
}

SQLRETURN CSqlOdbcDescList::getDescWithColNum( int colNum, CSqlOdbcDesc **out )
{
    CSqlOdbcDescList::iterator iter;
    iter = this->begin();
    while( iter != this->end() )
    {
        if( colNum == (*iter)->col_ )
        {
            *out = *iter;
            return( SQL_SUCCESS );
        }
        iter++;
    }

    return( SQL_ERROR );
}

CSqlOdbcDescList::CSqlOdbcDescList( int descType )
{
    type_=descType;
}

// Class CSqlOdbcDesc Functions
//----------------------------------
CSqlOdbcDesc::CSqlOdbcDesc( void ) :
    col_( 0 ),
    dataPtr_( 0 ),
    length_( 0 ),
    precision_( 0 ),
    scale_( 0 ),
    indPtr_( 0 ),
    cType_( -1 ),
    sqlType_( -1 ),
    csqlType_( -1 ),
    paramType_( SQL_PARAM_TYPE_UNKNOWN )
{
    schemaName_[0] = '\0';
    tableName_[0] = '\0';
    colName_[0] = '\0';
}

