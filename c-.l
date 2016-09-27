%{

/*
c-.l CS445 Cody Helbling
*/

#include <stdlib.h>
#include <cstdio>
#include "scanType.h"   // must be defined before tab.h
#include "util.h"
#include "symbolTable.h"
#include "c-.tab.h"
#include <string.h>

SymbolTable st;


void init() {
  yylval.token.lineno = yylineno;
  yylval.token.rtxt = strdup(yytext);
  printf("FLEX: %s\n", yytext);
}

void init(char* sval) {
  init();
  yylval.token.value.sval = sval;
}

void init(char cval) {
  init();
  yylval.token.value.cval = cval;
}

void init(int ival) {
  init();
  yylval.token.value.ival = ival;
}


// TODO: UPDATE THIS!!!
// Take in yytext containing "\0", "\n", "\." and return a string with '\0', '\n', '.'.
char* escstr(char* str) {
    int j = 0;
    char* esced = (char*)malloc(strlen(str) * sizeof(char));
    for(int i = 1; i < strlen(str) - 1; i++) {
        if(str[i] == '\\') {
            char eschar = str[i + 1];
            switch(eschar) {
                default : esced[j] = str[i + 1]; break;
                case 'n': esced[j] = '\n'; break;
                case '0': esced[j] = '\0'; break;
            }
            i++;
        } else {
            esced[j] = str[i];
        }
        j++;
    }
    char* resize = (char*)malloc(j * sizeof(char));
    strncpy(resize, esced, j);
    free(esced);
    yylval.token.slen = j;
    return resize;
}


static int lineno = 1;
/*
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
*/
%}

%option noyywrap
%option yylineno

%%
\n                                              { lineno++; }
[ ]                                             { /*printf("space-ln: %d\n", lineno);*/ }
[\t]                                            { /*printf("tab-ln: %d\n", lineno);*/ }
\/\/.*                                          { /*printf("comment: %s\n", yytext);*/ }
record                                          { init(strdup(yytext));
                                                  return RECORD;
                                                }
static                                          { init(strdup(yytext)); return STATIC; }
int                                             { init(strdup(yytext)); return INT; }
bool                                            { init(strdup(yytext)); return BOOL; }
char                                            { init(strdup(yytext)); return CHAR; }
if                                              { init(strdup(yytext)); return IF; }
else                                            { init(strdup(yytext)); return ELSE; }
while                                           { init(strdup(yytext)); return WHILE; }
return                                          { init(strdup(yytext)); return RETURN; }
break                                           { init(strdup(yytext)); return BREAK; }
and                                             { init(strdup(yytext)); return AND; }
or                                              { init(strdup(yytext)); return OR; }
not                                             { init(strdup(yytext)); return NOT; }
true                                            { init(1);              return BOOLCONST; }
false                                           { init(0);              return BOOLCONST; }
\!\=                                            { init(strdup(yytext)); return NOTEQ; }
\*\=                                            { init(strdup(yytext)); return MULASS; }
\+\+                                            { init(strdup(yytext)); return INC; }
\+\=                                            { init(strdup(yytext)); return ADDASS; }
\-\-                                            { init(strdup(yytext)); return DEC; }
\-\=                                            { init(strdup(yytext)); return SUBASS; }
\/\=                                            { init(strdup(yytext)); return DIVASS; }
\<\=                                            { init(strdup(yytext)); return LESSEQ; }
\=                                              { init(strdup(yytext)); return EQ; }
\=\=                                            { init(strdup(yytext)); return EQEQ; }
\>\=                                            { init(strdup(yytext)); return GRTEQ; }
\>                                              { init(strdup(yytext)); return GRT; }
\<                                              { init(strdup(yytext)); return LESS; }
\*                                              { init(strdup(yytext)); return STAR; }
\/                                              { init(strdup(yytext)); return DIVIDE; }
\-                                              { init(strdup(yytext)); return MINUS; }
\+                                              { init(strdup(yytext)); return PLUS; }
\%                                              { init(strdup(yytext)); return MOD; }
\?                                              { init(strdup(yytext)); return QMARK; }
\(|\)|\:|\;|\[|\]|\{|\}|\,|\.|\'                { init(yytext[0]); return yytext[0]; }
‘\0’                                            { init(strdup(yytext)); return NULCHAR; }
[a-zA-Z][a-zA-Z|0-9]*                           { init(strdup(yytext));
  st.print(pointerPrintStr);
                                                  return ID; }
[0-9]+                                          { init(atoi(yytext)); return NUMCONST; }
'((\\\')|[^\'\n])*\'                            { init(escstr(yytext)[0]); return CHARCONST; }
.                                               { printf("ERROR(%d): Invalid or misplaced input character: \"%c\"\n", lineno, yytext[0]);}
%%
