/***************************************************************************
 *   Copyright (C) 2007 by Prabakaran Thirumalai   *
 *   praba_tuty@yahoo.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
  ***************************************************************************/
#include "Statement.h"
#include <Info.h>
CreateTblStatement::CreateTblStatement()
{
    parsedData = NULL; 
    dbMgr = NULL; 
}

CreateTblStatement::~CreateTblStatement()
{

}
DbRetVal CreateTblStatement::execute(int &rowsAffected)
{
    DbRetVal rv = OK;
    rv = dbMgr->createTable(tblName, tblDef);
    return rv;
}

DbRetVal CreateTblStatement::resolve()
{
    DbRetVal rv = OK;
    strcpy(tblName, parsedData->getTableName());
    FieldIterator iter = parsedData->getCreFldList().getIterator();
    FieldDef fDef; 

    int i = 0;
    while (iter.hasElement())
    {
       fDef = iter.nextElement();
       //TODO : need a new addField function which can take FieldDef as parameter.
       i = tblDef.addField(fDef.fldName_, fDef.type_, fDef.length_, 
                        fDef.defaultValueBuf_,fDef.isNull_, fDef.isPrimary_  ); 
       if( 0 != i )
       {
          printf("Error while adding field \n");
          break;
       }
    } 
     
    return rv;
}
