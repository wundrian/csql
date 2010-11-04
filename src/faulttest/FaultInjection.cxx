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
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include<CSql.h>
#include<HelperFunc.cxx>
#include<FaultFunc.cxx>
void callFunction(char *tname, void *obj);
void injectFault(char *testname, void *object)
{
    char *enabledTest =  os::getenv("CSQL_INJECT");
    if (enabledTest == NULL) return;
    if (strcmp(testname, enabledTest) == 0)
    {
        callFunction(testname, object);
    }
    return;
}

void callFunction(char *testname, void *object)
{
    if (strcmp(testname, "test1") == 0) set_rv_timeout(object);
    else if (strcmp(testname, "test2") ==0) kill_myself(object);
    else printf("Fault Injection Test Name is wrong\n");
}
