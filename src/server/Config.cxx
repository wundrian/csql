/***************************************************************************
 *   Copyright (C) 2007 by www.databasecache.com                           *
 *   Contact: praba_tuty@databasecache.com                                 *
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
#include<Config.h>
#include<Debug.h>

int Config::readLine(FILE *fp, char * buffer)
{
  char c =0;
  int count =0;
  while ( true)
  {
      c = fgetc(fp);
      if (c == '\n') break;
      if (c == EOF) return EOF;
      buffer[count++] = c;
  }
  return count;
}
int Config::storeKeyVal(char *key, char *value)
{
    if (strcasestr(key, "PAGE_SIZE") != NULL )
           { cVal.pageSize = atoi(value);  }
    else if (strcasestr(key, "MAX_TRANS") != NULL)
           { cVal.maxTrans = atoi(value);  }
    else if (strcasestr(key, "MAX_PROCS") != NULL)
           { cVal.maxProcs = atoi(value);  }
    else if (strcasestr(key, "MAX_SYS_DB_SIZE") != NULL)
           { cVal.maxSysSize = atol(value);  }
    else if (strcasestr(key, "MAX_DB_SIZE") != NULL)
           { cVal.maxDbSize = atol(value);  }
    else if (strcasestr(key, "SYS_DB_KEY") != NULL)
           { cVal.sysDbKey = atoi(value);  }
    else if (strcasestr(key, "USER_DB_KEY") != NULL)
           { cVal.userDbKey = atoi(value);  }
    else if (strcasestr(key, "LOG_FILE") != NULL)
           { strcpy(cVal.logFile , value);  }
    else if (strcasestr(key, "MAP_ADDRESS") != NULL)
           { cVal.mapAddr = atol(value);  }
    else if (strcasestr(key, "MUTEX_TIMEOUT_SECS") != NULL)
           { cVal.mutexSecs = atoi(value);  }
    else if (strcasestr(key, "MUTEX_TIMEOUT_USECS") != NULL)
           { cVal.mutexUSecs = atoi(value);  }
    else  return 1;
    return 0;
}
int Config::readAllValues(char *fileName)
{
    FILE *fp;

    fp = fopen(fileName,"r");
    if( fp == NULL ) {
        printError(ErrSysInit, "Invalid path/filename in CSQL_CONFIG_FILE.");
	return !OK;
    }

    int hasData = 1;
    char buffer[1024];
    char key[1024];
    char value[1024];
    while (hasData)
    {
        memset(buffer, 0, 1024);
        //int ret = fscanf(fp,"%s\r",buffer);
        int ret = readLine(fp, buffer);
        if (ret == EOF) break;
        bool isComment= false;
        int posEqual =0;
        for (int i = 0; i <1024; i++)
        {
              if (buffer[i] == '=' ) posEqual=i;
              if (buffer[i] == '#' ) { isComment = true; break; }
              if (buffer[i] == '\n') { break; }
              if (buffer[i] == '\0') { break; }
        }
      if (isComment) continue;
      if (!posEqual) continue;
      strncpy(key, buffer, posEqual);
      key[posEqual] = '\0';
      posEqual++;
      strcpy(value, &buffer[posEqual]);
      storeKeyVal(key, value);
    }
    fclose(fp);
    return 0;
}




