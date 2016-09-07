%{
#include <stdio.h>
#include <stdlib.h>
#include "scanType.h"

extern int yylex();

void yyerror(char *msg) {
    printf("ERROR(): %s\n", msg);
}

%}

%token <tokenData> ID
%token <tokenData> NUMCONST
%token <tokenData> CHARCONST


%union {
    TokenData *tokenData;
}

%%

legal_tokens    : ID { printf("Line %d Token: %d Value: %s",
                        $1->linenum,
                        $1->tokenstring,
                        $1->tokenclass); }
                | NUMCONST
                | CHARCONST { printf("Line %d Token: %d Value: %s Input: ",
                        $1->linenum,
                        $1->tokenstring,
                        $1->tokenclass); };

/*
statementlist : statementlist statement
              | statement
              ;

statement     : exp
              | QUIT   { exit(0); }
              ;

exp           : '(' exp ')'
              | TRUE   { printf("True (%d) on line %d typed as %s\n",
                                $1->bvalue,
                                $1->linenum,
                                $1->tokenstring); }
              | FALSE  { printf("False on line %d\n", $1->linenum); }
              ;
*/
%%

int main()
{
    yyparse();

    return 0;
}