%{
#include <stdio.h>
#include <stdlib.h>
#include "scanType.h"

extern int yylex();

void yyerror(char const *msg) {
    printf("ERROR(): %s\n", msg);
}

%}


%token <tokenData> ID
%token <tokenData> NUMCONST
%token <tokenData> CHARCONST
%define parse.error verbose


%union {
    TokenData *tokenData;
}

%%


token       : token ID
            | token NUMCONST
            | token CHARCONST
            | ID
            | NUMCONST
            | CHARCONST
            ;
%%

int main()
{
    yyparse();
    return 0;
}