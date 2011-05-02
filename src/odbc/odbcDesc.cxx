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
    ListIterator iter = descList_.getIterator();
    CSqlOdbcDesc *descElem = NULL;
    while (iter.hasElement()) {
        descElem = (CSqlOdbcDesc *) iter.nextElement();
        if (descElem == node) {
            iter.reset();
            delete node;    
            descList_.remove(descElem);
            return( SQL_SUCCESS );
        }
    }
    return(SQL_ERROR);
}

void CSqlOdbcDescList::freeAllDesc( void )
{
    ListIterator iter = descList_.getIterator();
    CSqlOdbcDesc *descElem = NULL;
    while (iter.hasElement()) {
        descElem = (CSqlOdbcDesc *) iter.nextElement();
        if (type_ == SQL_DESC_IMP) {
            if (descElem->dataPtr_ != NULL) { 
                if(descElem->csqlType_ == typeString || 
                                            descElem->csqlType_ == typeBinary) 
                    delete [] (char*)descElem->dataPtr_;
                else 
                    delete descElem->dataPtr_;
                descElem->dataPtr_=NULL;               
            }
        }
        delete descElem; 
        descElem = NULL;
    }
    descList_.reset();
}
         
SQLRETURN CSqlOdbcDescList::getDescWithColNum( int colNum, CSqlOdbcDesc **out )
{
    ListIterator iter = descList_.getIterator();
    CSqlOdbcDesc *descElem = NULL;
    while (iter.hasElement()) {
        descElem = (CSqlOdbcDesc *) iter.nextElement();
        if (colNum == descElem->col_) {
            *out = descElem;
            return (SQL_SUCCESS);
        }
    }
    return (SQL_ERROR);
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

