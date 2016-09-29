
#ifndef UTIL_H
#define UTIL_H

#include "globals.h"
//#include "util.h"

void printTree(TreeNode *tree, int numOfSibs);
void printSpaces();
TreeNode *newStmtNode(StmtKind);
TreeNode *newExprNode(ExprKind);
TreeNode *newDeclNode(DeclKind);
#endif
