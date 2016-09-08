%{
#include <stdio.h>
#include <stdlib.h>
#include "scanType.h"

extern int yylex();
char stripper(char* value);

void yyerror(char const *msg) {
    printf("ERROR(): %s\n", msg);
}

%}


%token <tokenData> ID
%token <tokenData> NUMCONST
%token <tokenData> CHARCONST
%token <tokenData> TRUE
%token <tokenData> FALSE
%token <tokenData> KEYWORD
%define parse.error verbose


%union {
    TokenData *tokenData;
}

%%

tokens      : tokens token
            | token
            ;

token       : ID { printf("Line %d Token: ID Value: %s\n",
                    $1->linenum,
                    $1->tokenstring); }
            | NUMCONST  { printf("Line %d Token: NUMCONST Value: %s Input: %s\n",
                    $1->linenum,
                    $1->tokenstring,
                    $1->tokenstring); }
            | TRUE { printf("Line %d Token: BOOLCONST Value: %d Input: %s\n",
                    $1->linenum,
                    $1->bvalue,
                    $1->tokenstring); }
            | FALSE { printf("Line %d Token: BOOLCONST Value: %d Input: %s\n",
                    $1->linenum,
                    $1->bvalue,
                    $1->tokenstring); }
            | CHARCONST { printf("Line %d Token: CHARCONST Value: '%c' Input: %s\n",
                    $1->linenum,
                    stripper($1->tokenstring),
                    $1->tokenstring); }
            | KEYWORD { printf("Line %d Token: %s\n",
                    $1->linenum,
                    $1->tokenstring); }
            ;
%%

int main()
{
    yyparse();
    return 0;
}

char stripper(char* value){

    if(value[2] == '0'){
        return 0; }
    else if( value[2] == 'n' ){
        return 10;
     }
    else if( value[1] == '\\'){
        return value[2]; }
    else {
        return value[1];
    }
}
