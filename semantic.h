
#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "globals.h"

#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void scopeAndType(TreeNode *tree, int numOfSibs, map<string, map<string, vector<string> > > type_map);
bool is_in_vector(vector<string> vec, string str);
TreeNode *newStmtNode(StmtKind);
TreeNode *newExprNode(ExprKind);
TreeNode *newDeclNode(DeclKind);
#endif
