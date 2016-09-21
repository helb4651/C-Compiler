%{
#include <stdio.h>
#include <stdlib.h>
#include "scanType.h"
#include <ctype.h>
#include <getopt.h>
#define YYDEBUG 1


extern int yylex();
char stripper(char* value);
char* toUppercaseString(char* str);

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
%token <tokenData> NOTEQ
%token <tokenData> MULASS
%token <tokenData> INC
%token <tokenData> ADDASS
%token <tokenData> DEC
%token <tokenData> SUBASS
%token <tokenData> DIVASS
%token <tokenData> LESSEQ
%token <tokenData> LESS
%token <tokenData> EQ
%token <tokenData> EQEQ
%token <tokenData> GRTEQ
%token <tokenData> GRT
%token <tokenData> STAR
%token <tokenData> MINUS
%token <tokenData> PLUS
%token <tokenData> DIVIDE
%token <tokenData> MOD
%token <tokenData> QMARK
%token <tokenData> OPS
%token <tokenData> RECORD
%token <tokenData> STATIC
%token <tokenData> INT
%token <tokenData> BOOL
%token <tokenData> CHAR
%token <tokenData> IF
%token <tokenData> ELSE
%token <tokenData> WHILE
%token <tokenData> RETURN
%token <tokenData> BREAK
%token <tokenData> AND
%token <tokenData> OR
%token <tokenData> NOT
%token <tokenData> LPAREN
%token <tokenData> RPAREN
%token <tokenData> SEMICOL
%token <tokenData> NULCHAR
%token <tokenData> EMPTSTR
%token <tokenData> LCURLY
%token <tokenData> RCURLY
%token <tokenData> LBRACK
%token <tokenData> RBRACK
%token <tokenData> COLON
%token <tokenData> COMMA
%token <tokenData> DOT
%token <tokenData> RECTYPE

%define parse.error verbose



%union {
    TokenData *tokenData;
}

%%

/* 1 */
program             : declarationList { printf("1\n"); }
                    ;
/* 2 */
declarationList     : declarationList declaration  { printf("2a\n"); }
                    | declaration                  { printf("2b\n"); }
                    ;
/* 3 */
declaration         : varDeclaration { printf("3a\n"); }
                    | funDeclaration { printf("3b\n"); }
                    | recDeclaration { printf("3c\n"); }
                    ;

/* ------------------------------------------------------------------------------------------------------------------ */

/* 4 */
recDeclaration      : RECORD ID LCURLY localDeclarations RCURLY { printf("4\n"); }
                    ;

/* ------------------------------------------------------------------------------------------------------------------ */

/* 5 */
varDeclaration      : typeSpecifier varDeclList SEMICOL { printf("5\n"); }
                    ;

/* 6 */
scopedVarDeclaration: scopedTypeSpecifier varDeclList SEMICOL  { printf("6\n"); }
                    ;

/* 7 */
varDeclList         : varDeclList COMMA varDeclInitialize { printf("7a\n"); }
                    | varDeclInitialize { printf("7b\n"); }
                    ;

/* 8 */
varDeclInitialize   : varDeclId                        { printf("8a\n"); }
                    | varDeclId COLON simpleExpression { printf("8b\n"); }
                    ;

/* 9 */
varDeclId           : ID                         { printf("9a\n"); }
                    | ID LBRACK NUMCONST RBRACK  { printf("9b\n"); }
                    ;

/* 10 */
scopedTypeSpecifier : STATIC typeSpecifier  { printf("10a\n"); }
                    | typeSpecifier         { printf("10b\n"); }
                    ;

/* 11 TODO: What is RECTYPE supposed to be? */

typeSpecifier       : returnTypeSpecifier   { printf("11a\n"); }
                    | RECTYPE               { printf("11b\n"); }
                    ;

/* 12 */
returnTypeSpecifier : INT                   { printf("12a\n"); }
                    | BOOL                  { printf("12b\n"); }
                    | CHAR                  { printf("12c\n"); }
                    ;

/* ------------------------------------------------------------------------------------------------------------------ */

/* 13 */
funDeclaration      : typeSpecifier ID LPAREN params RPAREN statement   { printf("13a\n"); }
                    | ID LPAREN params RPAREN statement                 { printf("13b\n"); }
                    ;

/* 14 */
params              : paramList     { printf("14a\n"); }
                    | /* EMPTSTR */       { printf("14b\n"); }
                    ;

/* 15 */
paramList           : paramList SEMICOL paramTypeList
                    | paramTypeList
                    ;

/* 16 */
paramTypeList       : typeSpecifier paramIdList
                    ;

/* 17 */
paramIdList         : paramIdList COMMA paramId
                    | paramId
                    ;

/* 18 */
paramId             : ID
                    | ID LBRACK RBRACK
                    ;

/* ------------------------------------------------------------------------------------------------------------------ */

/* 19 */
statement           : expressionStmt
                    | compoundStmt
                    | selectionStmt
                    | iterationStmt
                    | returnStmt
                    | breakStmt
                    ;

/* 20 */
compoundStmt        : LCURLY localDeclarations statementList RCURLY
                    ;

/* 21 */
localDeclarations   : localDeclarations scopedVarDeclaration
                    | /* EMPTSTR */
                    ;


/* 22 */
statementList       : statementList statement
                    | /* EMPTSTR */
                    ;

/* 23 */
expressionStmt      : expression SEMICOL
                    | SEMICOL
                    ;

/* 24 */
selectionStmt       : IF LPAREN simpleExpression RPAREN statement
                    | IF LPAREN simpleExpression RPAREN statement ELSE statement
                    ;

/* 25 */
iterationStmt       : WHILE LPAREN simpleExpression RPAREN statement
                    ;


/* 26 */
returnStmt          : RETURN SEMICOL
                    | RETURN expression SEMICOL
                    ;

/* 27 */
breakStmt           : BREAK SEMICOL


/* ------------------------------------------------------------------------------------------------------------------ */

/* 28 */
expression          : mutable EQ  expression
                    | mutable ADDASS expression
                    | mutable SUBASS expression
                    | mutable MULASS expression
                    | mutable DIVASS expression
                    | mutable INC expression
                    | mutable DEC expression
                    | simpleExpression
                    ;

/* 29 */
simpleExpression    : simpleExpression OR andExpression
                    | andExpression
                    ;


/* 30 */
andExpression       : andExpression AND unaryRelExpression
                    | unaryRelExpression
                    ;


/* 31 */
unaryRelExpression  : NOT unaryRelExpression
                    | relExpression
                    ;

/* 32 */
relExpression       : sumExpression relop sumExpression
                    | sumExpression
                    ;

/* 33 */
relop               : LESSEQ
                    | LESS
                    | GRT
                    | GRTEQ
                    | EQEQ
                    | NOTEQ
                    ;

/* 34 */
sumExpression       : sumExpression sumop term
                    | term
                    ;

/* 35 */
sumop               : PLUS
                    | MINUS
                    ;

/* 36 */
term                : term mulop unaryExpression
                    | unaryExpression
                    ;

/* 37 */
mulop               : STAR
                    | DIVIDE
                    | MOD
                    ;

/* 38 */
unaryExpression     : unaryop unaryExpression
                    | factor
                    ;

/* 39 */
unaryop             : MINUS
                    | STAR
                    | QMARK
                    ;

/* 40 */
factor              : immutable
                    | mutable
                    ;

/* 41 */
mutable             : ID
                    | mutable LBRACK expression RBRACK
                    | mutable DOT ID
                    ;

/* 42 */
immutable           : LPAREN expression RPAREN
                    | call
                    | constant
                    ;

/* 43 */
call                : ID LPAREN args RPAREN
                    ;

/* 44 */
args                : argList
                    | /* EMPTSTR */
                    ;

/* 45 */
argList             : argList COMMA expression
                    | expression
                    ;

/* 46 */
constant            : NUMCONST
                    | CHARCONST
                    | TRUE
                    | FALSE
                    ;




/* -------------------------------- Old Stuff -----------------------------------------------------------
tokens      : tokens token
            | token
            ;

token       : ID { printf("Line %d Token: ID Value: %s\n",
                    $1->linenum,
                    $1->tokenstring); }
            | NUMCONST  { printf("Line %d Token: NUMCONST Value: %d  Input: %s\n",
                    $1->linenum,
                    atoi($1->tokenstring),
                    $1->tokenstring); }
            | TRUE { printf("Line %d Token: BOOLCONST Value: %d  Input: %s\n",
                    $1->linenum,
                    $1->bvalue,
                    $1->tokenstring); }
            | FALSE { printf("Line %d Token: BOOLCONST Value: %d  Input: %s\n",
                    $1->linenum,
                    $1->bvalue,
                    $1->tokenstring); }
            | CHARCONST { printf("Line %d Token: CHARCONST Value: '%c'  Input: %s\n",
                    $1->linenum,
                    stripper($1->tokenstring),
                    $1->tokenstring); }
            | KEYWORD { printf("Line %d Token: %s\n",
                    $1->linenum,
                    toUppercaseString($1->tokenstring)); }
            | NOTEQ { printf("Line %d Token: NOTEQ\n",
                    $1->linenum); }
            | MULASS { printf("Line %d Token: MULASS\n",
                    $1->linenum); }
            | INC { printf("Line %d Token: INC\n",
                    $1->linenum); }
            | ADDASS { printf("Line %d Token: ADDASS\n",
                    $1->linenum); }
            | DEC { printf("Line %d Token: DEC\n",
                    $1->linenum); }
            | SUBASS { printf("Line %d Token: SUBASS\n",
                    $1->linenum); }
            | DIVASS { printf("Line %d Token: DIVASS\n",
                    $1->linenum); }
            | LESSEQ { printf("Line %d Token: LESSEQ\n",
                    $1->linenum); }
            | EQ { printf("Line %d Token: EQ\n",
                    $1->linenum); }
            | GRTEQ{ printf("Line %d Token: GRTEQ\n",
                    $1->linenum); }
            | OPS{ printf("Line %d Token: %s\n",
                    $1->linenum,
                    $1->tokenstring); }
            ;

-------------------------------------------------------------------------------------------------------- */
%%

int main(int argc, char **argv)
{
    extern FILE *yyin;
    yyin = fopen(argv[1], "r");
    yyparse();

    // GET OPT

    int c;
    extern char *optarg;
    extern int optind;
    int aflg = 0;
    int bflg = 0;
    int errflg = 0;
    char *ofile = NULL;



	while ((c = getopt(argc, argv, "d"))	!= EOF)
	   switch (c) {
	   case	'd':
	      yydebug = 1;
	      printf( "YYDEBUG Enabled!\n" );
	      break;
	   case	'?':
	      errflg++;
	   }
	if (errflg) {
	   (void)fprintf(stderr,
	      "usage: cmd [-a|-b] [-o <filename>] files...\n");
	   exit	(2);
	    }
	    for	( ; optind < argc; optind++)
	  (void)printf("%s\n", argv[optind]);


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

char* toUppercaseString( char* str ){

    int i=0;
    while(str[i])
    {
      str[i] = (toupper(str[i]));
      i++;
    }
    return str;
}
