%{
#include <stdlib.h>
#include "scanType.h"   // must be defined before tab.h
#include "c-.tab.h"
#include <string.h>

static int lineno = 1;

int setTokenData(int tokenClass) {
    yylval.tokenData = new TokenData;
    yylval.tokenData->tokenclass = tokenClass;
    yylval.tokenData->linenum = lineno;
    yylval.tokenData->tokenstring = strdup(yytext);  // make a copy
    if (tokenClass == TRUE) {
       yylval.tokenData->bvalue = 1;
    }
    if (tokenClass == FALSE) {
       yylval.tokenData->bvalue = 0;
    }
    return tokenClass;
}

%}

%option noyywrap

%%
\n                                              { lineno++; }
[ ]                                             { /*printf("space-ln: %d\n", lineno);*/ }
[\t]                                            { /*printf("tab-ln: %d\n", lineno);*/ }
\/\/.*                                          { /*printf("comment: %s\n", yytext);*/ }
record                                          { return setTokenData(RECORD); }
static                                          { return setTokenData(STATIC); }
int                                             { return setTokenData(INT); }
bool                                            { return setTokenData(BOOL); }
char                                            { return setTokenData(CHAR); }
if                                              { return setTokenData(IF); }
else                                            { return setTokenData(ELSE); }
while                                           { return setTokenData(WHILE); }
return                                          { return setTokenData(RETURN); }
break                                           { return setTokenData(BREAK); }
and                                             { return setTokenData(AND); }
or                                              { return setTokenData(OR); }
not                                             { return setTokenData(NOT); }
true                                            { return setTokenData(TRUE); }
false                                           { return setTokenData(FALSE); }
\!\=                                            { return setTokenData(NOTEQ); }
\*\=                                            { return setTokenData(MULASS); }
\+\+                                            { return setTokenData(INC); }
\+\=                                            { return setTokenData(ADDASS); }
\-\-                                            { return setTokenData(DEC); }
\-\=                                            { return setTokenData(SUBASS); }
\/\=                                            { return setTokenData(DIVASS); }
\<\=                                            { return setTokenData(LESSEQ); }
\=                                              { return setTokenData(EQ); }
\=\=                                            { return setTokenData(EQEQ); }
\>\=                                            { return setTokenData(GRTEQ); }
\>                                              { return setTokenData(GRT); }
\<                                              { return setTokenData(LESS); }
\*                                              { return setTokenData(STAR); }
\/                                              { return setTokenData(DIVIDE); }
\-                                              { return setTokenData(MINUS); }
\+                                              { return setTokenData(PLUS); }
\%                                              { return setTokenData(MOD); }
\?                                              { return setTokenData(QMARK); }
\(                                              { return setTokenData(LPAREN); }
\)                                              { return setTokenData(RPAREN); }
\;                                              { return setTokenData(SEMICOL); }
\{                                              { return setTokenData(LCURLY); }
\}                                              { return setTokenData(RCURLY); }
\[                                              { return setTokenData(LBRACK); }
\]                                              { return setTokenData(RBRACK); }
\:                                              { return setTokenData(COLON); }
\,                                              { return setTokenData(COMMA); }
\.                                              { return setTokenData(DOT); }
‘\0’                                            { return setTokenData(NULCHAR); }
[a-zA-Z][a-zA-Z|0-9]*                           { /*printf("ID: %s\n", yytext);*/           return setTokenData(ID); }
[0-9]+                                          { /*printf("NUMCONST: %d\n", yytext[0]);*/  return setTokenData(NUMCONST); }
'[a-zA-Z0-9"\\\']'|'\\[a-zA-Z0-9\\\'"]'         { /*printf("CHARCONST: %c\n", yytext[0]);*/ return setTokenData(CHARCONST); }

""/.                                            { return setTokenData(EMPTSTR); }
.                                               { printf("ERROR(%d): Invalid or misplaced input character: \"%c\"\n", lineno, yytext[0]);}
%%