%{
#include <stdio.h>
#include <stdlib.h>
#include "scanType.h"
#include <ctype.h>
#include <getopt.h>


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


program             : declarationList
                    ;

declarationList     : declarationList declaration
                    | declaration
                    ;

declaration         : varDeclaration
                    | funDeclaration
                    | recDeclaration
                    ;

/* ------------------------------------------------------------------------------------------------------------------ */


recDeclaration      : RECORD ID LCURLY localDeclarations RCURLY
                    ;

/* ------------------------------------------------------------------------------------------------------------------ */

varDeclaration      : typeSpecifier varDeclList SEMICOL
                    ;

scopedVarDeclaration: scopedTypeSpecifier varDeclList SEMICOL
                    ;

varDeclList         : varDeclList COMMA varDeclInitialize
                    | varDeclInitialize
                    ;

varDeclInitialize    : varDeclId
                    | varDeclId COLON simpleExpression
                    ;

varDeclId           : ID | ID LBRACK NUMCONST RBRACK
                    ;

scopedTypeSpecifier : STATIC typeSpecifier
                    | typeSpecifier
                    ;

/* TODO: What is RECTYPE supposed to be? */
typeSpecifier       : returnTypeSpecifier
                    | RECTYPE
                    ;

returnTypeSpecifier : INT
                    | BOOL
                    | CHAR
                    ;

/* ------------------------------------------------------------------------------------------------------------------ */

funDeclaration      : returnTypeSpecifier ID LPAREN params LPAREN statement
                    | ID LPAREN params LPAREN statement
                    ;

params              : paramList
                    | EMPTSTR
                    ;

paramList           : paramList SEMICOL paramTypeList
                    | paramTypeList
                    ;

paramTypeList       : typeSpecifier paramIdList
                    ;


paramIdList         : paramIdList COMMA paramId
                    | paramId
                    ;


paramId             : ID
                    | ID LBRACK RBRACK
                    ;

/* ------------------------------------------------------------------------------------------------------------------ */

statement           : expressionStmt
                    | compoundStmt
                    | selectionStmt
                    | iterationStmt
                    | returnStmt
                    | breakStmt
                    ;

compoundStmt        : LCURLY localDeclarations statementList RCURLY
                    ;

localDeclarations   : localDeclarations scopedVarDeclaration
                    | EMPTSTR
                    ;



statementList       : statementList statement
                    | EMPTSTR
                    ;

expressionStmt      : expression SEMICOL
                    | SEMICOL
                    ;

selectionStmt       : IF LPAREN simpleExpression LPAREN statement
                    ;

iterationStmt       : WHILE LPAREN simpleExpression LPAREN statement
                    ;

returnStmt          : RETURN SEMICOL
                    | RETURN expression SEMICOL
                    ;

breakStmt           : BREAK SEMICOL


/* ------------------------------------------------------------------------------------------------------------------ */


expression          : mutable EQ  expression
                    | mutable ADDASS expression
                    | mutable SUBASS expression
                    | mutable MULASS expression
                    | mutable DIVASS expression
                    | mutable INC expression
                    | mutable DEC expression
                    | simpleExpression
                    ;

simpleExpression    : simpleExpression OR andExpression
                    | andExpression
                    ;


andExpression       : andExpression AND unaryRelExpression
                    | unaryRelExpression
                    ;


unaryRelExpression  : NOT unaryRelExpression
                    | relExpression
                    ;

relExpression       : sumExpression relop sumExpression
                    | sumExpression
                    ;

relop               : LESSEQ
                    | LESS
                    | GRT
                    | GRTEQ
                    | EQEQ
                    | NOTEQ
                    ;

sumExpression       : sumExpression sumop term
                    | term
                    ;

sumop               : PLUS
                    | MINUS
                    ;

term                : term mulop unaryExpression
                    | unaryExpression
                    ;

mulop               : STAR
                    | DIVIDE
                    | MOD
                    ;

unaryExpression     : unaryop unaryExpression
                    | factor
                    ;

unaryop             : MINUS
                    | STAR
                    | QMARK
                    ;

factor              : immutable
                    | mutable
                    ;

mutable             : ID
                    | ID LBRACK expression RBRACK
                    | mutable DOT ID
                    ;

immutable           : LPAREN expression RPAREN
                    | call
                    | constant
                    ;

call                : ID LPAREN args RPAREN
                    ;

args                : argList
                    | EMPTSTR
                    ;

argList             : argList COMMA expression
                    | expression
                    ;

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
	      printf( "Monkey!\n" );
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
