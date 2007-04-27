#ifndef lint
static char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define yyclearin (yychar=(-1))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING (yyerrflag!=0)
#define YYPREFIX "yy"
#line 2 "dmlyacc.y"
#include <CSql.h>
#include <stdlib.h>
#include "Parser.h"

class Predicate;

ParsedData *parsedData;
int yylex( void );
void yyerror(const char* Msg);
#line 14 "dmlyacc.y"
typedef union
{
   char *stringval;
   void *predicate;
} YYSTYPE;
#line 28 "dmlyacc.c"
#define STRING 257
#define FIELD 258
#define NUMBER_STRING 259
#define BINARY_STRING 260
#define DOUBLE 261
#define OPERATOR 262
#define PARAMETER 263
#define SELECT 264
#define FROM 265
#define WHERE 266
#define BETWEEN 267
#define AND 268
#define OR 269
#define NOT 270
#define STAR 271
#define INSERT 272
#define INTO 273
#define VALUES 274
#define DELETE 275
#define UPDATE 276
#define SET 277
#define NULL_VALUE 278
#define where_clause 279
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    0,    0,    0,    6,   10,   10,   13,    7,   14,
   14,   15,   15,   16,    8,    9,   12,   12,   17,   17,
   18,   19,   11,   11,    4,    4,    4,    4,    5,    5,
    2,    2,    1,    3,    3,    3,    3,    3,    3,
};
short yylen[] = {                                         2,
    1,    1,    1,    1,    6,    2,    1,    2,    9,    0,
    3,    2,    1,    2,    5,    6,    1,    0,    2,    1,
    2,    3,    2,    0,    3,    3,    2,    1,    3,    5,
    1,    1,    1,    1,    1,    1,    1,    1,    1,
};
short yydefred[] = {                                      0,
    0,    0,    0,    0,    0,    1,    2,    3,    4,   33,
   32,   31,    7,    0,    0,    0,    0,    0,    0,    6,
    0,    0,    0,    0,    8,    0,    0,    0,    0,    0,
    0,   20,    0,    0,    0,    0,    0,   23,    0,   17,
   15,    0,    0,    0,   19,    5,   11,    0,   27,    0,
    0,    0,    0,   34,   35,   36,   37,   38,   39,   22,
   21,   16,   13,    0,   29,    0,   25,   26,    0,    0,
   12,    0,   14,    9,   30,
};
short yydgoto[] = {                                       5,
   37,   13,   60,   38,   39,    6,    7,    8,    9,   14,
   29,   41,   20,   27,   64,   71,   31,   45,   32,
};
short yysindex[] = {                                   -258,
 -247, -261, -236, -219,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  -43, -219, -219, -244, -219, -247,    0,
    8, -216, -219, -216,    0, -247, -223, -245,   -7, -208,
  -44,    0,   -7,   -4,   15, -219, -246,    0, -224,    0,
    0, -225, -219,   -7,    0,    0,    0, -225,    0, -225,
 -225, -219, -219,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    5,    0, -212,    0,    0, -225,   -7,
    0, -225,    0,    0,    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 -217,    2,    0,    2,    0,    0,    0,    0,   58,    0,
    0,    0,   58,    0,    0,    0,    0,    0,    3,    0,
    0,    0,    0,   58,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   58,
    0,    0,    0,    0,    0,
};
short yygindex[] = {                                      0,
    4,   40,  -41,    0,  -10,    0,    0,    0,    0,   34,
   39,  -29,    0,    0,    0,    0,    0,    0,   21,
};
#define YYTABLESIZE 235
short yytable[] = {                                      43,
   19,   24,   28,   46,   12,    1,   63,   17,   65,   66,
   10,   15,   10,    2,   62,   50,    3,    4,   21,   22,
   51,   24,   12,   11,   36,   49,   30,   73,   16,   12,
   75,   54,   23,   55,   56,   57,   47,   58,   10,   19,
   74,   67,   68,   52,   53,   70,   30,   26,   69,   28,
   35,   40,   59,   42,   48,   72,   10,   18,   25,   34,
   24,   28,   33,   61,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   18,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   44,
};
short yycheck[] = {                                      44,
   44,    0,    0,   33,    1,  264,   48,    4,   50,   51,
  258,  273,  258,  272,   44,  262,  275,  276,   15,   16,
  267,   18,   19,  271,  270,   36,   23,   69,  265,   26,
   72,  257,  277,  259,  260,  261,   41,  263,  258,   44,
   70,   52,   53,  268,  269,   41,   43,   40,   44,  266,
  274,   59,  278,  262,   40,  268,  274,    0,   19,   26,
   59,   59,   24,   43,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  265,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  279,
};
#define YYFINAL 5
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 279
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'",0,0,"','",0,0,0,0,0,0,0,0,0,0,0,0,0,0,"';'",0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"STRING","FIELD",
"NUMBER_STRING","BINARY_STRING","DOUBLE","OPERATOR","PARAMETER","SELECT","FROM",
"WHERE","BETWEEN","AND","OR","NOT","STAR","INSERT","INTO","VALUES","DELETE",
"UPDATE","SET","NULL_VALUE","where_clause",
};
char *yyrule[] = {
"$accept : command",
"command : select_statement",
"command : insert_statement",
"command : delete_statement",
"command : update_statement",
"select_statement : SELECT field_list FROM ident where_clause_opt semicolon_opt",
"field_list : field_list field_list_L",
"field_list : field",
"field_list_L : ',' field",
"insert_statement : INSERT INTO ident field_list_opt VALUES '(' value_list ')' semicolon_opt",
"field_list_opt :",
"field_list_opt : '(' field_list ')'",
"value_list : value_list value_list_L",
"value_list : value",
"value_list_L : ',' value",
"delete_statement : DELETE FROM ident where_clause_opt semicolon_opt",
"update_statement : UPDATE ident SET assign_list where_clause semicolon_opt",
"semicolon_opt : ';'",
"semicolon_opt :",
"assign_list : assign_list assign_list_L",
"assign_list : assign_stmt",
"assign_list_L : ',' assign_stmt",
"assign_stmt : ident OPERATOR value",
"where_clause_opt : WHERE conditions",
"where_clause_opt :",
"conditions : condition AND condition",
"conditions : condition OR condition",
"conditions : NOT condition",
"conditions : condition",
"condition : ident OPERATOR value",
"condition : ident BETWEEN value AND value",
"field : ident",
"field : STAR",
"ident : FIELD",
"value : STRING",
"value : NUMBER_STRING",
"value : BINARY_STRING",
"value : DOUBLE",
"value : PARAMETER",
"value : NULL_VALUE",
};
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH 500
#endif
#endif
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short yyss[YYSTACKSIZE];
YYSTYPE yyvs[YYSTACKSIZE];
#define yystacksize YYSTACKSIZE
#line 185 "dmlyacc.y"

extern int lexEof;
void yyerror(const char* Msg) { 
    if( lexEof == 0 )
        fprintf(stderr, "[Parser: %s]\n", Msg);

    return;
}
#line 248 "dmlyacc.c"
#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse()
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register char *yys;
    extern char *getenv();

    if (yys = getenv("YYDEBUG"))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if (yyn = yydefred[yystate]) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yyss + yystacksize - 1)
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#ifdef lint
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#ifdef lint
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yyss + yystacksize - 1)
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 1:
#line 30 "dmlyacc.y"
{ YYACCEPT; }
break;
case 2:
#line 31 "dmlyacc.y"
{ YYACCEPT; }
break;
case 3:
#line 32 "dmlyacc.y"
{ YYACCEPT; }
break;
case 4:
#line 33 "dmlyacc.y"
{ YYACCEPT; }
break;
case 5:
#line 37 "dmlyacc.y"
{
            parsedData->setStmtType(SelectStatement);
            parsedData->setTableName(yyvsp[-2].stringval); 
            free(yyvsp[-2].stringval);
        }
break;
case 9:
#line 51 "dmlyacc.y"
{
            parsedData->setStmtType(InsertStatement);
            parsedData->setTableName(yyvsp[-6].stringval); 
            free(yyvsp[-6].stringval);
        }
break;
case 13:
#line 64 "dmlyacc.y"
{
            parsedData->insertValue((char*)yyvsp[0].stringval);
            free(yyvsp[0].stringval);
        }
break;
case 14:
#line 70 "dmlyacc.y"
{
            parsedData->insertValue((char*)yyvsp[0].stringval);
            free(yyvsp[0].stringval);
        }
break;
case 15:
#line 77 "dmlyacc.y"
{
            parsedData->setStmtType(DeleteStatement);
            parsedData->setTableName(yyvsp[-2].stringval); 
            free(yyvsp[-2].stringval);
	}
break;
case 16:
#line 85 "dmlyacc.y"
{
            parsedData->setStmtType(UpdateStatement);
            parsedData->setTableName(yyvsp[-4].stringval); 
            free( yyvsp[-4].stringval );
	}
break;
case 22:
#line 103 "dmlyacc.y"
{ 
            parsedData->insertUpdateValue( (char*) yyvsp[-2].stringval, (char*) yyvsp[0].stringval);
            free( yyvsp[-2].stringval ); free( yyvsp[0].stringval ); 
        }
break;
case 25:
#line 114 "dmlyacc.y"
{
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) yyvsp[-2].predicate, OpAnd, (Predicate*) yyvsp[0].predicate);
            parsedData->setCondition((Predicate*)pred);
            yyval.predicate= pred;

        }
break;
case 26:
#line 122 "dmlyacc.y"
{
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) yyvsp[-2].predicate, OpOr, (Predicate*) yyvsp[0].predicate);
            parsedData->setCondition((Predicate*)pred);
            yyval.predicate= pred;
        }
break;
case 27:
#line 129 "dmlyacc.y"
{
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) yyvsp[0].predicate, OpNot, NULL);
            parsedData->setCondition((Predicate*)pred);
            ((Predicate*)yyvsp[0].predicate)->print();
            yyval.predicate= pred;
        }
break;
case 28:
#line 137 "dmlyacc.y"
{
            parsedData->setCondition((Predicate*)yyvsp[0].predicate);
            ((Predicate*)yyvsp[0].predicate)->print();
            yyval.predicate=yyvsp[0].predicate;
        }
break;
case 29:
#line 144 "dmlyacc.y"
{
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)yyvsp[-1].stringval);
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)yyvsp[-2].stringval, (char*)yyvsp[0].stringval);
            pred = parsedData->insertPredicate((char*) yyvsp[-2].stringval, op, ptr);
            free( yyvsp[-2].stringval ); free( yyvsp[0].stringval ); 
            yyval.predicate=pred;
        }
break;
case 30:
#line 153 "dmlyacc.y"
{
            void **ptr1 = parsedData->insertCondValueAndGetPtr((char*)yyvsp[-4].stringval, (char*)yyvsp[-2].stringval);
            void **ptr2 = parsedData->insertCondValueAndGetPtr((char*)yyvsp[-4].stringval, (char*)yyvsp[0].stringval);
            Predicate *pred1, *pred2, *pred3;
            pred1 = parsedData->insertPredicate((char*) yyvsp[-4].stringval, OpGreaterThanEquals, ptr1);
            pred2 = parsedData->insertPredicate((char*) yyvsp[-4].stringval, OpLessThanEquals, ptr2);
            pred3 = parsedData->insertPredicate(pred1, OpAnd, pred2);
            free( yyvsp[-4].stringval );  free( yyvsp[-2].stringval );  free( yyvsp[0].stringval );
            yyval.predicate= pred3;
        }
break;
case 31:
#line 165 "dmlyacc.y"
{
            parsedData->insertField((char*)yyvsp[0].stringval);
            free( yyvsp[0].stringval );
        }
break;
case 32:
#line 170 "dmlyacc.y"
{ 
            parsedData->insertField((char*)yyvsp[0].stringval);
            free( yyvsp[0].stringval );
        }
break;
case 33:
#line 175 "dmlyacc.y"
{ yyval.stringval = yyvsp[0].stringval; }
break;
case 34:
#line 177 "dmlyacc.y"
{ yyval.stringval = yyvsp[0].stringval; }
break;
case 35:
#line 178 "dmlyacc.y"
{ yyval.stringval = yyvsp[0].stringval; }
break;
case 36:
#line 179 "dmlyacc.y"
{ yyval.stringval = yyvsp[0].stringval; }
break;
case 37:
#line 180 "dmlyacc.y"
{ yyval.stringval = yyvsp[0].stringval; }
break;
case 38:
#line 181 "dmlyacc.y"
{ yyval.stringval = yyvsp[0].stringval; }
break;
case 39:
#line 182 "dmlyacc.y"
{ yyval.stringval = (char*) 0; }
break;
#line 561 "dmlyacc.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yyss + yystacksize - 1)
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
