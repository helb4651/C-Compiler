/****************************************************/
/* File: util.cpp                                   */
/* Modified from...                                 */
/* Utility function implementation                  */
/* for the TINY compiler                            */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/


#include "util.h"

static int spaces = 0;
static int chiIndex = 0;
static int sibIndex = 0;


void addSpacesAndExMark() {
        int x=0;
        while( x < spaces ) {
                if(x%4 == 0) {
                        printf("!");
                } else{
                        printf(" ");
                }
                x++;
        }
}

void printTree(TreeNode *tree, int numOfSibs) {
        bool recursivePrint = false;
        if(numOfSibs == -1) {
                numOfSibs++;
                recursivePrint = true;
        } else {
                spaces += 4;
        }
        for(TreeNode *t = tree; t != NULL; t = t->sibling) {
                addSpacesAndExMark();
                if(numOfSibs > 0) {
                        printf("Sibling: %i  ", numOfSibs-1);
                } else if(numOfSibs == 0 && recursivePrint == false) {
                        printf("Child: %i  ", chiIndex);
                }
                numOfSibs++;

                if(t->nodekind == StmtK) {
                        switch(t->kind.stmt) {

                        case IfK:
                                printf("If ");
                                break;
                        case WhileK:
                                printf("While ");
                                break;
                        case CompK:
                                printf("Compound ");
                                break;
                        case ReturnK:
                                printf("Return ");
                                break;
                        case BreakK:
                                printf("Break ");
                                break;
                        }
                } else if(t->nodekind == ExprK) {
                        switch(t->kind.expr) {
                        case ConstK:
                                printf("Const: ");
                                switch(t->declType) {
                                case Int:
                                        printf("%i ", t->attr.value);
                                        break;
                                case Bool:
                                        if(t->attr.value == 0) {
                                                printf("false ");
                                        } else {
                                                printf("true ");
                                        }
                                        break;
                                case Char:
                                        printf("'%c' ", t->attr.cvalue);
                                        break;
                                case String:
                                        printf("\"%s\" ", t->attr.string);
                                        break;
                                default:
                                        break;
                                }
                                break;
                        case IdK:
                                printf("Id: %s ", t->attr.name);
                                break;
                        case OpK:
                                printf("Op: %s ", t->attr.name);
                                break;
                        case AssignK:
                                printf("Assign: %s ", t->attr.name);
                                break;
                        case CallK:
                                printf("Call: %s ", t->attr.name);
                                break;
                        }
                } else if(t->nodekind == DeclK) {
                        switch(t->kind.decl) {
                        case FuncK:
                                printf("Func %s returns ", t->attr.name);
                                break;
                        case VarK:
                                if(t->isArray == true) {
                                        printf("Var %s is array of ", t->attr.name); // TODO:
                                } else {
                                        printf("Var %s of ", t->attr.name);
                                }
                                break;
                        case ParamK:
                                if(t->isArray == true) {
                                        printf("Param %s is array of ", t->attr.name); // TODO:
                                } else {
                                        printf("Param %s of ", t->attr.name);
                                }
                                break;
                        case RecordK:
                                printf("Record %s  ", t->attr.name);
                        default:
                                break;
                        }
                        switch(t->declType) {
                        case Void:
                                printf("type void ");
                                break;
                        case Int:
                                printf("type int ");
                                break;
                        case Bool:
                                printf("type bool ");
                                break;
                        case Char:
                                printf("type char ");
                                break;
                        case Record:
                                if(t->isRecord!=true) {
                                        printf("type record ");
                                }
                                break;
                        default:
                                break;
                        }
                } else {
                        printf("Failed printing tree nodekind index: %u\n", t->nodekind);
                }
                printf("[line: %d]\n", t->linenum);
                for(int i = 0; i < MAXCHILDREN; i++) {
                        chiIndex = i;
                        printTree(t->child[i], 0);
                        chiIndex = 0;
                }
        }
        sibIndex--;
        spaces -= 4;
}


TreeNode *newStmtNode(StmtKind kind) {
        TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
        for(int i = 0; i < MAXCHILDREN; i++) t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = StmtK;
        t->kind.stmt = kind;
        t->linenum = yylineno;
        return t;
}

TreeNode *newExprNode(ExprKind kind) {
        TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
        for(int i = 0; i < MAXCHILDREN; i++) t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = ExprK;
        t->kind.expr = kind;
        t->linenum = yylineno;
        return t;
}

TreeNode *newDeclNode(DeclKind kind) {
        TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
        for(int i = 0; i < MAXCHILDREN; i++) t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = DeclK;
        t->kind.decl = kind;
        t->linenum = yylineno;
        return t;
}
