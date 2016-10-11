%{
/****************************************************/
/* File: c.l                                        */
/* Flex specification for c-                        */
/* CS445                                            */
/* University of Idaho                              */
/****************************************************/

#include <stdlib.h>
#include "scanType.h"   // must be defined before tab.h
#include "util.h"
#include "symbolTable.h"
#include "c-.tab.h"
#include <string.h>


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

void init() {
  yylval.token.linenum = yylineno;
  yylval.token.tokenstring = strdup(yytext);
  // printf("FLEX: %s\n", yytext);
}


void init(char* sval) {
  init();
  yylval.token.sval = sval;
}


void init(char cval) {
  init();
  yylval.token.cval = cval;
}


void init(int ival) {
  init();
  yylval.token.ival = ival;
}





%}

%option noyywrap
%option yylineno

%%
\n                                              { /*linenum++;*/ }
[ ]                                             { /*printf("space-ln: %d\n", linenum);*/ }
[\t]                                            { /*printf("tab-ln: %d\n", linenum);*/ }
\/\/.*                                          { /*printf("comment: %s\n", yytext);*/ }
record                                          { init(strdup(yytext)); return RECORD; }
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

                                                std::string words[] = {strdup(yytext)};
                                                int wordsLen = 1;
                                                //printf("\nGeneral Lookup FLEX\n");
                                                for (int i=0; i<wordsLen; i++) {
                                                    void *data;
                                                    if ((data = st.lookup(words[i]))==NULL){
                                                      //printf("%s: %s\n", words[i].c_str(), (char *)"NULL");
                                                      return ID;
                                                    }
                                                    else{
                                                      return RECTYPE;
                                                       //printf("%s: %s\n", words[i].c_str(), (char *)data);
                                                      }
                                                }


                                                    if ((st.lookup(strdup(yytext))==NULL)) return ID;
                                                    else return RECORD;
                                                }
[0-9]+                                          { init(atoi(yytext)); return NUMCONST; }
'((\\\')|[^\'\n])*\'                            { init(stripper(yytext)); return CHARCONST; }
.                                               { printf("ERROR(%d): Invalid or misplaced input character: \"%c\"\n", yylineno, yytext[0]);}
%%
