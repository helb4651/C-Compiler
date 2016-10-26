
#ifndef PRINTTREE_H
#define PRINTTREE_H

#include "globals.h"

void printTree(TreeNode *tree, int numOfSibs, bool printTypes);
TreeNode *newStmtNode(StmtKind);
TreeNode *newExprNode(ExprKind);
TreeNode *newDeclNode(DeclKind);
#endif
