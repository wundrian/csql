%{
#include <CSql.h>
#include <stdlib.h>
#include "Parser.h"

class Predicate;

ParsedData *parsedData;
int yylex( void );
void yyerror(const char* Msg);
%}


%union
{
   char *stringval;
   void *predicate;
}

%token <stringval> STRING FIELD NUMBER_STRING BINARY_STRING DOUBLE OPERATOR PARAMETER
%token <stringval> SELECT FROM WHERE BETWEEN AND OR NOT
%token <stringval> STAR
%token <stringval> INSERT INTO VALUES
%token <stringval> DELETE UPDATE SET NULL_VALUE
%token ';' ',' '(' ')'
%type <stringval> ident field value 
%type <predicate> conditions condition

%%
command:  select_statement { YYACCEPT; }
        | insert_statement { YYACCEPT; }
        | delete_statement { YYACCEPT; }
        | update_statement { YYACCEPT; }
        ;
        
select_statement: SELECT field_list FROM ident where_clause_opt semicolon_opt
	{
            parsedData->setStmtType(SelectStatement);
            parsedData->setTableName($4); 
            free($4);
        }
        ;

field_list: field_list field_list_L
        | field 
        ;
field_list_L: ',' field
        ;
        
insert_statement: INSERT INTO ident field_list_opt VALUES '(' value_list ')' semicolon_opt
        {
            parsedData->setStmtType(InsertStatement);
            parsedData->setTableName($3); 
            free($3);
        }
        ;

field_list_opt:
        | '(' field_list ')'
        ;

value_list: value_list value_list_L
        | value
	{
            parsedData->insertValue((char*)$1);
            free($1);
        }
        ;
value_list_L: ',' value 
	{
            parsedData->insertValue((char*)$2);
            free($2);
        }
        ;
        
delete_statement: DELETE FROM ident where_clause_opt semicolon_opt
	{
            parsedData->setStmtType(DeleteStatement);
            parsedData->setTableName($3); 
            free($3);
	}
        ;
        
update_statement: UPDATE ident SET assign_list where_clause semicolon_opt
	{
            parsedData->setStmtType(UpdateStatement);
            parsedData->setTableName($2); 
            free( $2 );
	}
        ;

semicolon_opt: ';'
        |
        ;

assign_list: assign_list assign_list_L
        | assign_stmt
        ;

assign_list_L: ',' assign_stmt
        ;
assign_stmt: ident OPERATOR value 
        { 
            parsedData->insertUpdateValue( (char*) $1, (char*) $3);
            free( $1 ); free( $3 ); 
        }
        ;
 
where_clause_opt:  WHERE conditions
        |
        ;

conditions: condition AND condition
	{
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) $1, OpAnd, (Predicate*) $3);
            parsedData->setCondition((Predicate*)pred);
            $$= pred;

        }
        | condition OR condition
        {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) $1, OpOr, (Predicate*) $3);
            parsedData->setCondition((Predicate*)pred);
            $$= pred;
        }
        | NOT condition
        {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) $2, OpNot, NULL);
            parsedData->setCondition((Predicate*)pred);
            ((Predicate*)$2)->print();
            $$= pred;
        }
        | condition
        {
            parsedData->setCondition((Predicate*)$1);
            ((Predicate*)$1)->print();
            $$=$1;
        }
        ;
condition: ident OPERATOR value 
	{
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)$2);
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)$1, (char*)$3);
            pred = parsedData->insertPredicate((char*) $1, op, ptr);
            free( $1 ); free( $3 ); 
            $$=pred;
        }
        | ident BETWEEN value AND value
        {
            void **ptr1 = parsedData->insertCondValueAndGetPtr((char*)$1, (char*)$3);
            void **ptr2 = parsedData->insertCondValueAndGetPtr((char*)$1, (char*)$5);
            Predicate *pred1, *pred2, *pred3;
            pred1 = parsedData->insertPredicate((char*) $1, OpGreaterThanEquals, ptr1);
            pred2 = parsedData->insertPredicate((char*) $1, OpLessThanEquals, ptr2);
            pred3 = parsedData->insertPredicate(pred1, OpAnd, pred2);
            free( $1 );  free( $3 );  free( $5 );
            $$= pred3;
        }
        ;
field:   ident
        {
            parsedData->insertField((char*)$1);
            free( $1 );
        }
        | STAR
        { 
            parsedData->insertField((char*)$1);
            free( $1 );
        }
        ;
ident:    FIELD { $$ = $1; }
        ;
value:    STRING { $$ = $1; }
        | NUMBER_STRING { $$ = $1; }
        | BINARY_STRING { $$ = $1; }
        | DOUBLE { $$ = $1; }
        | PARAMETER { $$ = $1; }
        | NULL_VALUE { $$ = (char*) 0; }
        ;
%%

extern int lexEof;
void yyerror(const char* Msg) { 
    if( lexEof == 0 )
        fprintf(stderr, "[Parser: %s]\n", Msg);

    return;
}
