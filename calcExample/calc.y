%{
#include <stdio.h>
#include <stdlib.h>
#include "scanType.h"

extern int yylex();

void yyerror(const char *msg) {
    printf("ERROR(): %s\n", msg);
}

%}

%token QUIT
%token <tokenData> TRUE
%token <tokenData> FALSE

%union {
    TokenData *tokenData;
}

%%
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

%%

int main()
{
    yyparse();

    return 0;
}