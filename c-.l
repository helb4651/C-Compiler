%{
#include <stdlib.h>
#include "scanType.h"   // must be defined before tab.h
#include "calc.tab.h"

static int lineno = 1;

int setTokenData(int tokenClass) {
    yylval.tokenData = new TokenData;
    yylval.tokenData->tokenclass = tokenClass;
    yylval.tokenData->linenum = lineno;
    yylval.tokenData->tokenstring = strdup(yytext);  // make a copy
    /*
    if (tokenClass == TRUE) {
       yylval.tokenData->bvalue = true;
    }
    */
    return tokenClass;
}

%}

%option noyywrap

%%
\n                              { lineno++; }
[ ]                             { printf("space-ln: %d\n", lineno); }
[\t]                            { printf("tab-ln: %d\n", lineno); }
[\/\/].*                        { printf("comment: %s\n", yytext); }
[a-zA-Z][a-zA-Z|0-9]*           { printf("ID: %s\n", yytext); setTokenData(ID); }
[0-9]+                          { printf("NUMCONST: %d\n", yytext[0]); setTokenData(NUMCONST); }
[\'a-zA-Z0-9\'|\\a-mo-zA-Z1-9]  { printf("CHARCONST: %c\n", yytext[0]); setTokenData(CHARCONST); }
[\(\)\*\-]                      { return yytext[0]; }
.                               { printf("ERROR(%d): bad character: '%c'\n", lineno, yytext[0]);}
%%