
#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "globals.h"

#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

void scopeAndType(TreeNode *tree, int numOfSibs, bool FuncKRecurse);
bool is_in_vector(vector<string> vec, string str);
map<string, string> check_operands_types_same(TreeNode* t);
TreeNode *newStmtNode(StmtKind);
TreeNode *newExprNode(ExprKind);
TreeNode *newDeclNode(DeclKind);
extern const char *Types[];
extern SymbolTable semanticsSymbolTable;
extern bool main_function_exists;
#endif
