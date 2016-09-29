/****************************************************/
/* File: globals.h                                  */
/* Modified from Tiny Compiler                      */
/* must come before other include files             */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef GLOBALS_H
#define GLOBALS_H


#include <cstdlib>
#include <cstring>
#include "symbolTable.h"

#define MAXRESERVED 8

extern int yylineno;

extern SymbolTable st;

typedef int TokenType;
typedef enum {DeclK, StmtK, ExprK} NodeKind;
typedef enum {FuncK, VarK, ParamK, RecordK} DeclKind;
typedef enum {IfK, WhileK, CompK, ReturnK, BreakK} StmtKind;
typedef enum {ConstK, IdK, OpK, AssignK, CallK} ExprKind;
typedef enum {Void, Int, Bool, Char, String, Record} DeclType;


#define MAXCHILDREN 3

typedef struct treeNode {
        struct treeNode *child[MAXCHILDREN];
        struct treeNode *sibling;
        int linenum;
        NodeKind nodekind;

        union {
                DeclKind decl;
                StmtKind stmt;
                ExprKind expr;
        } kind;

        union {
                int value;
                unsigned char cvalue;
                char *string;
                char *name;
        } attr;

        DeclType declType;
        bool isStatic;
        bool isArray;
        int arrayLen;
        bool isRecord;
} TreeNode;
#endif
