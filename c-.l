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
record                                          { printf("--- %s\n", yytext); return setTokenData(RECORD); }
static                                          { printf("--- %s\n", yytext); return setTokenData(STATIC); }
int                                             { printf("--- %s\n", yytext); return setTokenData(INT); }
bool                                            { printf("--- %s\n", yytext); return setTokenData(BOOL); }
char                                            { printf("--- %s\n", yytext); return setTokenData(CHAR); }
if                                              { printf("--- %s\n", yytext); return setTokenData(IF); }
else                                            { printf("--- %s\n", yytext); return setTokenData(ELSE); }
while                                           { printf("--- %s\n", yytext); return setTokenData(WHILE); }
return                                          { printf("--- %s\n", yytext); return setTokenData(RETURN); }
break                                           { printf("--- %s\n", yytext); return setTokenData(BREAK); }
and                                             { printf("--- %s\n", yytext); return setTokenData(AND); }
or                                              { printf("--- %s\n", yytext); return setTokenData(OR); }
not                                             { printf("--- %s\n", yytext); return setTokenData(NOT); }
true                                            { printf("--- %s\n", yytext); return setTokenData(TRUE); }
false                                           { printf("--- %s\n", yytext); return setTokenData(FALSE); }
\!\=                                            { printf("--- %s\n", yytext); return setTokenData(NOTEQ); }
\*\=                                            { printf("--- %s\n", yytext); return setTokenData(MULASS); }
\+\+                                            { printf("--- %s\n", yytext); return setTokenData(INC); }
\+\=                                            { printf("--- %s\n", yytext); return setTokenData(ADDASS); }
\-\-                                            { printf("--- %s\n", yytext); return setTokenData(DEC); }
\-\=                                            { printf("--- %s\n", yytext); return setTokenData(SUBASS); }
\/\=                                            { printf("--- %s\n", yytext); return setTokenData(DIVASS); }
\<\=                                            { printf("--- %s\n", yytext); return setTokenData(LESSEQ); }
\=                                              { printf("--- %s\n", yytext); return setTokenData(EQ); }
\=\=                                            { printf("--- %s\n", yytext); return setTokenData(EQEQ); }
\>\=                                            { printf("--- %s\n", yytext); return setTokenData(GRTEQ); }
\>                                              { printf("--- %s\n", yytext); return setTokenData(GRT); }
\<                                              { printf("--- %s\n", yytext); return setTokenData(LESS); }
\*                                              { printf("--- %s\n", yytext); return setTokenData(STAR); }
\/                                              { printf("--- %s\n", yytext); return setTokenData(DIVIDE); }
\-                                              { printf("--- %s\n", yytext); return setTokenData(MINUS); }
\+                                              { printf("--- %s\n", yytext); return setTokenData(PLUS); }
\%                                              { printf("--- %s\n", yytext); return setTokenData(MOD); }
\?                                              { printf("--- %s\n", yytext); return setTokenData(QMARK); }
\(                                              { printf("--- %s\n", yytext); return setTokenData(LPAREN); }
\)                                              { printf("--- %s\n", yytext); return setTokenData(RPAREN); }
\;                                              { printf("--- %s\n", yytext); return setTokenData(SEMICOL); }
\{                                              { printf("--- %s\n", yytext); return setTokenData(LCURLY); }
\}                                              { printf("--- %s\n", yytext); return setTokenData(RCURLY); }
\[                                              { printf("--- %s\n", yytext); return setTokenData(LBRACK); }
\]                                              { printf("--- %s\n", yytext); return setTokenData(RBRACK); }
\:                                              { printf("--- %s\n", yytext); return setTokenData(COLON); }
\,                                              { printf("--- %s\n", yytext); return setTokenData(COMMA); }
\.                                              { printf("--- %s\n", yytext); return setTokenData(DOT); }
‘\0’                                            { printf("--- %s\n", yytext); return setTokenData(NULCHAR); }
[a-zA-Z][a-zA-Z|0-9]*                           { printf("ID: %s\n", yytext); return setTokenData(ID); }
[0-9]+                                          { /*printf("NUMCONST: %d\n", yytext[0]);*/  printf("--- %s\n", yytext); return setTokenData(NUMCONST); }
'[a-zA-Z0-9"\\\']'|'\\[a-zA-Z0-9\\\'"]'         { /*printf("CHARCONST: %c\n", yytext[0]);*/ printf("--- %s\n", yytext); return setTokenData(CHARCONST); }
""                                              { printf("EMPTY STRING?\n"); return setTokenData(EMPTSTR); }
.                                               { printf("ERROR(%d): Invalid or misplaced input character: \"%c\"\n", lineno, yytext[0]);}
%%