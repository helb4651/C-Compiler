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
%token <tokenData> EQ
%token <tokenData> GRTEQ
%token <tokenData> OPS
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
	      if (bflg) {
		    errflg++;
		    printf("Someting\n");
		    }
	      else {
	        printf("Something else\n");
		    aflg++;
		    }
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
