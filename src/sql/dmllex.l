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
%array yytext
%{
#include "dmlyacc.h"
#include <stdlib.h>
#include <string.h>

int echo_on=0;
int lexEof=0;
extern char *lexInput;

#undef ECHO
#define ECHO { if(echo_on) printf("%s",yytext); }


/*    Macro definitions  */
%}


letter          [a-zA-Z_.]
digit           [0-9]
hex             [0-9A-Fa-f]
letter_or_digit [a-zA-Z_0-9.]
sign            [\+\-]
string_char     [\]\[\\\+\"=\)\(\{\}\*&\^\%\$#@!:;,\|\~\`\.\<\>\?\/a-zA-Z_0-9 \t\n\-]
white_space     [ \t\n]
blank           [ \t]
quota           \'\'
non_double_quota [^\"\n]
other           .
operator        "<"|">"|">="|"<="|"="|"\!="


%%
{operator}  { 
                yylval.stringval = strdup((const char*)yytext);
                return(OPERATOR);
            }

\'({quota}|{string_char})*\'{blank}*$   {
                int len; ECHO;
                if(*yytext != '\'') 
                    printf("ERROR: wanted a string, got: %s\n",yytext);
                len = yyleng - 1;
                while (yytext[len] == ' ' || yytext[len] == '\t') 
                { 
                    yytext[len] = '\0';
                    len--;
                }
                yylval.stringval = strdup((const char*)yytext + 1);
                //printf("rule1: %s.\n", yylval.stringval );
                return (STRING);
            }

\'({quota}|{string_char})*\'    {  ECHO;
                if(*yytext != '\'')
                    printf("ERROR: wanted a string, got: %s\n",yytext);
                yytext[yyleng-1]='\0';
                yylval.stringval = strdup((const char*)yytext + 1);
                //printf("rule2: %s.\n", yylval.stringval );
                return (STRING);
            }

\"{non_double_quota}*\"    {  ECHO;
                yytext[yyleng-1] = '\0'; /*remove the beginning and ending quota*/
                    yytext[0]=' ';
                yylval.stringval = strdup((const char*)yytext + 1);
                return (STRING);
            }

{letter}{letter_or_digit}*   {
	            int token; 
                char *fieldname;
                token = FIELD;
                ECHO;

                if(strcasecmp(yytext,"SELECT") == 0) token = SELECT;
                if(strcasecmp(yytext,"FROM") == 0) token = FROM;
                if(strcasecmp(yytext,"WHERE") == 0) token = WHERE;
                if(strcasecmp(yytext,"BETWEEN") == 0) token = BETWEEN;
                if(strcasecmp(yytext,"AND") == 0) token = AND;
                if(strcasecmp(yytext,"OR") == 0) token = OR;
                if(strcasecmp(yytext,"NOT") == 0) token = NOT;
                if(strcasecmp(yytext,"INSERT") == 0) token = INSERT;
                if(strcasecmp(yytext,"INTO") == 0) token = INTO;
                if(strcasecmp(yytext,"VALUES") == 0) token = VALUES;
                if(strcasecmp(yytext,"DELETE") == 0) token = DELETE;
                if(strcasecmp(yytext,"UPDATE") == 0) token = UPDATE;
                if(strcasecmp(yytext,"SET") == 0) token = SET;
                if(strcasecmp(yytext,"NULL") == 0) token = NULL_VALUE;

                if( token == FIELD )
                    yylval.stringval = strdup((const char*)yytext);
                else
                    yylval.stringval = 0;

                return(token);
            }

{sign}?{digit}+      { ECHO;
                yylval.stringval = strdup((const char*)yytext);
                return (NUMBER_STRING);
            }

{sign}?(({digit}*\.{digit}+)|({digit}+(\.{digit}*)?))([eE]{sign}?{digit}+)?   {   ECHO;
                yylval.stringval = strdup((const char*)yytext);
                return (DOUBLE);
            }

{hex}+      {   ECHO;
                yylval.stringval = strdup((const char*)yytext);
                return (BINARY_STRING);
            }
\*          {
                yylval.stringval = strdup((const char*)yytext);
                return(STAR);
            }
\?          {
                yylval.stringval = strdup((const char*)yytext);
                return(PARAMETER);
            }
{white_space}+ 	{ ECHO; }
"#"{other}* 	{ ECHO; }
"//"{other}* 	{ ECHO; }
"--"{other}* 	{ ECHO; }

%{
/*    Watch this C comment folks */
%}
"/*""/"*([^*/]|[^*]"/"|"*"[^/])*"*"*"*/" { ECHO; }

{other} { ECHO; return yytext[0]; }


%%

int yywrap()
{
    lexEof = 1;
    return 1;
}
