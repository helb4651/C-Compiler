%{
#include <stdio.h>
#include <stdlib.h>
#include "scanType.h"
#include "globals.h"
#include "symbolTable.h"
#include "util.h"
#include <ctype.h>
#include <getopt.h>
#define YYDEBUG 1
#define YYERROR_VERBOSE


extern int yylex();
extern FILE *yyin;
static TreeNode *syntaxTree;
SymbolTable st;
// static Scope st("global");

void yyerror(char const *msg) {
    printf("ERROR(): %s\n", msg);
}

// Check length of specific chars in the most brutal way possible.
void charerror(const char *rtxt) {
    int len = strlen(rtxt);
    if(len == 4 && rtxt[1] == '\\') {
        len -= 1;
    }
    if(len - 2 != 1) {
        printf("ERROR(%u): character is %u characters and not a single character: %s\n", yylineno, (unsigned)strlen(rtxt) - 2, rtxt);
    }
}

%}

%union {
    Token token;
    TreeNode *treeNode;
    DeclType declType;
    char *cstring;
}


%type <treeNode>        program
                        declaration
                        declarationList
                        varDeclaration
                        funDeclaration
                        recDeclaration
                        localDeclarations
                        scopedVarDeclaration
                        scopedTypeSpecifier
                        varDeclList
                        varDeclInitialize
                        varDeclId
                        simpleExpression
                        statement
                        statementList
                        params
                        paramList
                        paramTypeList
                        paramIdList
                        paramId
                        unmatched
                        matched
                        matched_selection
                        expressionStmt
                        compoundStmt
                        matched_iteration
                        unmatched_selection
                        unmatched_iteration
                        expression
                        returnStmt
                        breakStmt
                        mutable
                        andExpression
                        unaryRelExpression
                        relExpression
                        sumExpression
                        unaryExpression
                        term
                        factor
                        immutable
                        call
                        constant
                        args
                        argList
                        monkey



%type <declType>        typeSpecifier

%type <token>          unaryop
                        relop
                        mulop
                        sumop


%token <token>  ID
                NUMCONST
                CHARCONST
                BOOLCONST
                BOOL BREAK CHAR ELSE IF INT RETURN STATIC WHILE
                NOTEQ EQEQ LESSEQ GRTEQ INC DEC ADDASS SUBASS MULASS DIVASS
                EQ LESS GRT
                TRUE
                FALSE KEYWORD
                STAR MINUS PLUS DIVIDE MOD QMARK OPS RECORD AND OR NOT NULCHAR
                EMPTSTR
                RECTYPE
                '(' ')' '{' '}' '[' ']' '.' ','


%%

program             : declarationList { syntaxTree = $1; }
                    ;

declarationList     : declarationList declaration {
                               TreeNode *trav = $1;
                               if(trav != NULL) {
                                   while (trav->sibling != NULL) trav = trav->sibling;
                                   trav->sibling = $2;
                                   $$ = $1;
                               } else {
                                   $$ = $2;
                               }
                            }
                    | declaration      { $$ = $1; }
                    ;

declaration         : varDeclaration { $$ = $1; }
                    | funDeclaration { $$ = $1; }
                    | recDeclaration { $$ = $1; }
                    ;

/* ------------------------------------------------------------------------------------------------------------------ */

/* 4 */
recDeclaration      : RECORD ID '{' localDeclarations '}' {
              // printf("Print symbol table.\n");
              st.insert( $2.rtxt, (char *)"record");
              // st.insert("bravo", (char *)"bat");
              //st.print(pointerPrintStr);

                      }
                    ;

/* ------------------------------------------------------------------------------------------------------------------ */

/* 5 */
varDeclaration      : typeSpecifier varDeclList ';' {
                                TreeNode *complete = $2;
                                if(complete != NULL) {
                                    do {
                                        complete -> declType = $1;
                                        complete = complete -> sibling;

                                    } while(complete != NULL);
                                    $$ = $2;
                                } else {
                                    $$ = NULL;
                                }
                            }
                    ;

/* 6 */
scopedVarDeclaration: scopedTypeSpecifier varDeclList ';'  {
                                TreeNode *complete = $2;
                                if(complete != NULL) {
                                    do {
                                        complete->declType = $1->declType;
                                        complete->isStatic = $1->isStatic;
                                        complete = complete->sibling;
                                    } while(complete != NULL);
                                    $$ = $2;
                                } else {
                                    $$ = NULL;
                                }
                            }
                    ;

/* 7 */
varDeclList         : varDeclList ',' varDeclInitialize {
                               TreeNode *trav = $1;
                               if(trav != NULL) {
                                    while(trav->sibling != NULL) trav = trav->sibling;
                                    trav->sibling = $3;
                                    $$ = $1;
                                } else {
                                    $$ = $3;
                                }
                            }
                    | varDeclInitialize { $$ = $1; }
                    ;

/* 8 */
varDeclInitialize   : varDeclId                        { $$ = $1; }
                    | varDeclId ':' simpleExpression  {
                            $1->child[0] = $3; // <- NOT NULL, SHOULD BE $3
                            $$ = $1;
                        }
                    ;

/* 9 */
varDeclId           : ID    {
                                $$ = newDeclNode(VarK);
                                $$->attr.name = $1.value.sval;
                                $$->lineno = $1.lineno;
                            }
                    | ID '[' NUMCONST ']'  {
                            $$ = newDeclNode(VarK);
                            $$->attr.name = $1.value.sval;
                            $$->isArray = true;
                            $$->arrayLen = $3.value.ival;
                            $$->lineno = $1.lineno;
                        }
                    ;

/* 10 */
scopedTypeSpecifier : STATIC typeSpecifier  {
                                $$ = newDeclNode(VarK);
                                $$->isStatic = true;
                                $$->declType = $2;
                            }
                    | typeSpecifier         {
                            $$ = newDeclNode(VarK);
                            $$->declType = $1;
                        }
                    ;

/* 11 TODO: What is RECTYPE supposed to be? */
/* Look in everything06 for the record Point {....}
   Put a if statement lookup in the scanner
   Bison will ask the scanner if it's a rectype or ID


typeSpecifier       : returnTypeSpecifier   { $$ = $1; }
                    | RECTYPE               { $1 = Record; }
                    ;

returnTypeSpecifier : INT
                    | BOOL
                    | CHAR
                    ;
*/


typeSpecifier       : INT             { $$ = Int; }
                    | RECTYPE         { $$ = Record; }
                    | BOOL            { $$ = Bool; }
                    | CHAR            { $$ = Char; }
                    ;


/* ------------------------------------------------------------------------------------------------------------------ */

/* 13 */
funDeclaration      : typeSpecifier ID '(' params ')' statement {
                                $$ = newDeclNode(FuncK);
                                $$->declType = $1;
                                $$->attr.name = $2.value.sval;
                                $$->child[0] = $4;
                                $$->child[1] = $6;
                                $$->lineno = $3.lineno; // Allows for correct line no
                            }
                    | ID '(' params ')' statement {
                           $$ = newDeclNode(FuncK);
                           $$->declType = Void;
                           $$->attr.name = $1.value.sval;
                           $$->child[0] = $3;
                           $$->child[1] = $5;
                           $$->lineno = $2.lineno;
                        }
                    ;

/* 14 */
params              : paramList     { $$ = $1; }
                    | /* EMPTSTR */       { $$ = NULL; }
                    ;

/* 15 */
paramList           : paramList ';' paramTypeList {
                                TreeNode *trav = $1;
                                if(trav != NULL) {
                                    while(trav->sibling != NULL) trav = trav->sibling;
                                    trav->sibling = $3;
                                    $$ = $1;
                                } else {
                                    $$ = $3;
                                }
                            }
                    | paramTypeList { $$ = $1; }
                    ;

/* 16 */
paramTypeList       : typeSpecifier paramIdList {
                                TreeNode *complete = $2;
                                if(complete != NULL) {
                                    do {
                                        complete->declType = $1;
                                        complete = complete->sibling;
                                    } while(complete != NULL);
                                    $$ = $2;
                                } else {
                                    $$ = NULL;
                                }
                            }
                    ;

/* 17 */
paramIdList         : paramIdList ',' paramId {
                               TreeNode *trav = $1;
                               if(trav != NULL) {
                                   while(trav->sibling != NULL) trav = trav->sibling;
                                   trav->sibling = $3;
                                   $$ = $1;
                               } else {
                                   $$ = $3;
                               }
                            }
                    | paramId { $$ = $1; }
                    ;

/* 18 */
paramId             : ID    {
                               $$ = newDeclNode(ParamK);
                               $$->attr.name = $1.value.sval;
                            }
                    | ID '[' ']' {
                                $$ = newDeclNode(ParamK);
                                $$->attr.name = $1.value.sval;
                                $$->isArray = true;
                              }
                    ;

/* ------------------------------------------------------------------------------------------------------------------ */

/* 19 */
/* ###################################
statement           : expressionStmt
                    | compoundStmt
                    | selectionStmt
                    | iterationStmt
                    | returnStmt
                    | breakStmt
                    ;
   ###################################
*/

statement           : unmatched { $$ = $1; }
                    | matched { $$ = $1; }
                    ;

matched             : matched_selection { $$ = $1; }
                    | expressionStmt { $$ = $1; }
                    | compoundStmt { $$ = $1; }
                    | matched_iteration { $$ = $1; }
                    | returnStmt { $$ = $1; }
                    | breakStmt { $$ = $1; }
                    ;

unmatched           : unmatched_selection { $$ = $1; }
                    | unmatched_iteration { $$ = $1; }
                    ;


matched_iteration   : WHILE '(' simpleExpression ')' matched {
                                $$ = newStmtNode(WhileK);
                                $$->attr.name = $1.rtxt;
                                $$->child[0] = $3;
                                $$->child[1] = $5;
                                $$->lineno = $1.lineno;
                            }
                    ;

unmatched_iteration : WHILE '(' simpleExpression ')' unmatched {
                                $$ = newStmtNode(WhileK);
                                $$->attr.name = $1.rtxt;
                                $$->child[0] = $3;
                                $$->child[1] = $5;
                                $$->lineno = $1.lineno;
                            }
                    ;


/* 20 */
compoundStmt        : '{' localDeclarations statementList '}' {
                               $$ = newStmtNode(CompK);
                               $$->child[0] = $2;
                               $$->child[1] = $3;
                               $$->lineno = $1.lineno;
                            }
                    ;

/* 21 */
localDeclarations   : localDeclarations scopedVarDeclaration {
                                TreeNode *trav = $1;
                                if(trav != NULL) {
                                    while(trav->sibling != NULL) trav = trav->sibling;
                                    trav->sibling = $2;
                                    $$ = $1;
                                } else {
                                    $$ = $2;
                                }
                            }
                    | { $$ = NULL; }
                    ;


/* 22 */
statementList       : statementList statement {
                                TreeNode *trav = $1;
                                if(trav != NULL) {
                                    while(trav->sibling != NULL) trav = trav->sibling;
                                    trav->sibling = $2;
                                    $$ = $1;
                                } else {
                                    $$ = $2;
                                }
                            }
                    | { $$ = NULL; }
                    ;

/* 23 */
expressionStmt      : expression ';' { $$ = $1; }
                    | ';' { $$ = NULL; }
                    ;

/* 24 */
/* ########################################################################
selectionStmt       : IF '(' simpleExpression ')' statement
                    | IF '(' simpleExpression ')' statement ELSE statement
                    ;
   ########################################################################  */

matched_selection   : IF '(' simpleExpression ')' matched ELSE matched {
                                $$ = newStmtNode(IfK);
                                $$->attr.name = $1.rtxt;
                                $$->child[0] = $3;
                                $$->child[1] = $5;
                                $$->child[2] = $7;
                                $$->lineno = $1.lineno;
                            }
                    ;

unmatched_selection : IF '(' simpleExpression ')' matched ELSE unmatched {
                                $$ = newStmtNode(IfK);
                                $$->attr.name = $1.rtxt;
                                $$->child[0] = $3;
                                $$->child[1] = $5;
                                $$->child[2] = $7;
                                $$->lineno = $1.lineno;
                            }
                    | IF '(' simpleExpression ')' statement {
                            $$ = newStmtNode(IfK);
                            $$->attr.name = $1.rtxt;
                            $$->child[0] = $3;
                            $$->child[1] = $5;
                            $$->lineno = $1.lineno;
                        }
                    ;


/* 25 */
/* ###########################################################
iterationStmt       : WHILE '(' simpleExpression ')' statement
                    ;
   ########################################################### */

/* 26 */
returnStmt          : RETURN ';' {
                                $$ = newStmtNode(ReturnK);
                                $$->attr.name = $1.rtxt;
                                $$->lineno = $1.lineno;
                            }
                    | RETURN expression ';' {
                            $$ = newStmtNode(ReturnK);
                            $$->attr.name = $1.rtxt;
                            $$->child[0] = $2;
                            $$->lineno = $1.lineno;
                        }
                    ;

/* 27 */
breakStmt           : BREAK ';' {
                                $$ = newStmtNode(BreakK);
                                $$->attr.name = $1.rtxt;
                            }


/* ------------------------------------------------------------------------------------------------------------------ */

/* 28 */
expression          : mutable EQ  expression {
                                $$ = newExprNode(AssignK);
                                $$->attr.name = $2.rtxt;
                                $$->child[0] = $1;
                                $$->child[1] = $3;
                                $$->lineno = $2.lineno;
                            }
                    | mutable ADDASS expression {
                            $$ = newExprNode(AssignK);
                            $$->attr.name = $2.rtxt;
                            $$->child[0] = $1;
                            $$->child[1] = $3;
                            $$->lineno = $2.lineno;
                        }
                    | mutable SUBASS expression {
                            $$ = newExprNode(AssignK);
                            $$->attr.name = $2.rtxt;
                            $$->child[0] = $1;
                            $$->child[1] = $3;
                            $$->lineno = $2.lineno;
                        }
                    | mutable MULASS expression {
                            $$ = newExprNode(AssignK);
                            $$->attr.name = $2.rtxt;
                            $$->child[0] = $1;
                            $$->child[1] = $3;
                            $$->lineno = $2.lineno;
                        }
                    | mutable DIVASS expression {
                            $$ = newExprNode(AssignK);
                            $$->attr.name = $2.rtxt;
                            $$->child[0] = $1;
                            $$->child[1] = $3;
                            $$->lineno = $2.lineno;
                        }
                    | mutable INC {
                            $$ = newExprNode(AssignK);
                            $$->attr.name = $2.rtxt;
                            $$->child[0] = $1;
                            //$$->child[1] = $3;
                            $$->lineno = $2.lineno;
                        }
                    | mutable DEC{
                            $$ = newExprNode(AssignK);
                            $$->attr.name = $2.rtxt;
                            $$->child[0] = $1;
                            //$$->child[1] = $3;
                            $$->lineno = $2.lineno;
                        }
                    | simpleExpression { $$ = $1; }
                    ;

/* 29 */
simpleExpression    : simpleExpression OR andExpression {
                                $$ = newExprNode(OpK);
                                $$->attr.name = $2.rtxt;
                                $$->child[0] = $1;
                                $$->child[1] = $3;
                            }
                    | andExpression { $$ = $1; }
                    ;


/* 30 */
andExpression       : andExpression AND unaryRelExpression {
                                $$ = newExprNode(OpK);
                                $$->attr.name = $2.rtxt;
                                $$->child[0] = $1;
                                $$->child[1] = $3;
                            }
                    | unaryRelExpression { $$ = $1; }
                    ;


/* 31 */
unaryRelExpression  : NOT unaryRelExpression {
                                $$ = newExprNode(OpK);
                                $$->attr.name = $1.rtxt;
                                $$->child[0] = $2;
                            }
                    | relExpression { $$ = $1; }
                    ;

/* 32 */
relExpression       : sumExpression relop sumExpression {
                               $$ = newExprNode(OpK);
                               $$->attr.name = $2.rtxt;
                               $$->child[0] = $1;
                               $$->child[1] = $3;
                            }
                    | sumExpression { $$ = $1; }
                    ;

/* 33 */
relop               : LESSEQ { $$ = $1; }
                    | LESS   { $$ = $1; }
                    | GRT    { $$ = $1; }
                    | GRTEQ  { $$ = $1; }
                    | EQEQ   { $$ = $1; }
                    | NOTEQ  { $$ = $1; }
                    ;

/* 34 */
sumExpression       : sumExpression sumop term {
                                $$ = newExprNode(OpK);
                                $$->attr.name = $2.rtxt;
                                $$->child[0] = $1;
                                $$->child[1] = $3;
                            }
                    | term { $$ = $1; }
                    ;

/* 35 */
sumop               : PLUS { $$ = $1; }
                    | MINUS { $$ = $1; }
                    ;

/* 36 */
term                : term mulop unaryExpression {
                                $$ = newExprNode(OpK);
                                $$->attr.name = $2.rtxt;
                                $$->child[0] = $1;
                                $$->child[1] = $3;
                                $$->lineno = $2.lineno;
                            }
                    | unaryExpression { $$ = $1; }
                    ;

/* 37 */
mulop               : STAR { $$ = $1; }
                    | DIVIDE { $$ = $1; }
                    | MOD { $$ = $1; }
                    ;

/* 38 */
unaryExpression     : unaryop unaryExpression {
                                $$ = newExprNode(OpK);
                                $$->attr.name = $1.rtxt;
                                $$->child[0] = $2;
                            }
                    | factor { $$ = $1; }
                    ;

/* 39 */
unaryop             : MINUS { $$ = $1; }
                    | STAR { $$ = $1; }
                    | QMARK { $$ = $1; }
                    ;

/* 40 */
factor              : immutable { $$ = $1; }
                    | mutable { $$ = $1; }
                    ;

/* 41 */

mutable             : ID {
                               $$ = newExprNode(IdK);
                               $$->attr.name = $1.value.sval;
                            }
                    | mutable '[' expression ']' {
                           $$ = newExprNode(OpK);
                           $$->attr.name = $2.rtxt;
                           $$->child[0] = $1;
                           $$->child[1] = $3;
                        }
                    | mutable '.' monkey {
                            $$ = newExprNode(OpK);
                            $$->attr.name = $2.rtxt;
                            $$->child[0] = $1;
                            $$->child[1] = $3;
                                    }
                    ;
monkey              : ID {
                            $$ = newExprNode(IdK);
                            $$->attr.name = $1.value.sval;
                          }

/* 42 */
immutable           : '(' expression ')' { $$ = $2; }
                    | call { $$ = $1; }
                    | constant { $$ = $1; }
                    ;

/* 43 */
call                : ID '(' args ')' {
                               $$ = newExprNode(CallK);
                               $$->attr.name = $1.value.sval;
                               $$->child[0] = $3;
                            }
                    ;

/* 44 */
args                : argList { $$ = $1; }
                    | { $$ = NULL; }
                    ;

/* 45 */
argList             : argList ',' expression {
                                TreeNode *trav = $1;
                                if(trav != NULL) {
                                    while(trav->sibling != NULL) trav = trav->sibling;
                                    trav->sibling = $3;
                                    $$ = $1;
                                } else {
                                    $$ = $3;
                                }
                            }
                    | expression { $$ = $1; }
                    ;

/* 46 */
constant            : NUMCONST {
                                $$ = newExprNode(ConstK);
                                $$->attr.ivalue = $1.value.ival;
                                $$->declType = Int;
                            }
                    | CHARCONST {
                            $$ = newExprNode(ConstK);
                            $$->attr.cvalue = $1.value.cval;
                            $$->declType = Char;
                        }
                    | BOOLCONST {
                            $$ = newExprNode(ConstK);
                            $$->attr.ivalue = $1.value.ival;
                            $$->declType = Bool;
                        }
                    ;


%%
int main(int argc, char** argv) {
    // Get cmd line option arguments if they exist
    int opt;
    while((opt = getopt(argc, argv, "d")) != EOF) {
        switch(opt) { //in case we add more options
            default:
                abort();
                break;
            case 'd':
                yydebug = 1;
                break;
        }
    }

    // If there's a trailing argument, it must be the filename.
    if(argc > 1) {
        FILE *iFile;
        iFile = fopen(argv[argc - 1], "r");
        if(!iFile) {
            printf("File not found: %s\n", argv[argc - 1]);
            exit(-1);
        }
        yyin = iFile;
    }

    // Start the scanner now that our options and yyin have been changed (or not).
    do {
        yyparse();
    } while(!feof(yyin));

    printTree(syntaxTree, -1);
    printf("Number of warnings: %i\n", 0);
    printf("Number of errors: %i\n", 0);
    return 0;
}
