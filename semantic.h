
#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "globals.h"

void scopeAndType(TreeNode *tree, int numOfSibs);
TreeNode *newStmtNode(StmtKind);
TreeNode *newExprNode(ExprKind);
TreeNode *newDeclNode(DeclKind);
#endif
