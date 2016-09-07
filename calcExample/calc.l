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
    if (tokenClass == TRUE) {
       yylval.tokenData->bvalue = true;
    }

    return tokenClass;
}

%}

%option noyywrap

%%
[ \t] ;
\n    { lineno++; }
[Tt]  { return setTokenData(TRUE); }
true  { return setTokenData(TRUE); }
[Ff]  { return setTokenData(FALSE); }
quit  { return QUIT; } // return token class
[\(\)\*\-]  { return yytext[0]; }
.     { printf("ERROR(%d): bad character: '%c'\n", lineno, yytext[0]);}
%%