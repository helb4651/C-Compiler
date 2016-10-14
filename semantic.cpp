#include "semantic.h"
#include "symbolTable.h"
#include <string.h>
#include <stdio.h>



static int spaces = 0;
static int chiIndex = 0;
static int sibIndex = 0;

static bool DEBUG=false;

SymbolTable semanticsSymbolTable;


// void addSpacesAndExMark() {
//         int x=0;
//         while( x < spaces ) {
//                 if(x%4 == 0) {
//                         printf("!");
//                 } else{
//                         printf(" ");
//                 }
//                 x++;
//         }
// }

const char *Types[] = {"type void", "type int", "type bool", "type char", "type string", "type record", NULL};


bool is_in_vector(vector<string> vec, string str){
  // cout << str << endl;
  if ( find(vec.begin(), vec.end(), str) != vec.end() ){
          printf("Exists\n");
          return true;
      }
  else{
          printf("Doesn't Exist\n");
          return false;
        }
}

vector<string> getUnaryOps(){
  cout << "Getting Unary Ops" << endl;
  vector<string> UnaryOps;
  UnaryOps.push_back("+");
  UnaryOps.push_back("<");
  UnaryOps.push_back(">");
  UnaryOps.push_back("==");
  UnaryOps.push_back("*");
  UnaryOps.push_back("not");
  UnaryOps.push_back("-");
  UnaryOps.push_back("[");
  UnaryOps.push_back("or");
  UnaryOps.push_back("and");
  return UnaryOps;
}


void scopeAndType(TreeNode *tree, int numOfSibs, map<string, map<string, vector<string> > > types) {

        // vector<string> or_map_left_types;
        // or_map_left_types.push_back("Boolean");
        //
        // vector<string> or_map_right_types;
        // or_map_right_types.push_back("Boolean");
        //
        // vector<string> or_map_result_types;
        // or_map_right_types.push_back("Boolean");
        //
        // map<string, vector<string> > or_map;
        // or_map["left"] = or_map_left_types;
        // or_map["right"] = or_map_right_types;
        // or_map["result"] = or_map_result_types;
        //
        //
        // map<string, map<string, vector<string> > > types_map;
        // types_map["or"] = or_map;
        //
        // vector<string> vec = types_map["or"]["left"];
        //
        // if ( find(vec.begin(), vec.end(), "Boolean") != vec.end() )
        //         printf("Exists\n");
        // else
        //         printf("Doesn't Exist\n");



        bool recursivePrint = false;
        if(numOfSibs == -1) {
                numOfSibs++;
                recursivePrint = true;
        } else {
                spaces += 4;
        }
        for(TreeNode *t = tree; t != NULL; t = t->sibling) {
                // addSpacesAndExMark();
                if(numOfSibs > 0) {
                        // printf("Sibling: %i  ", numOfSibs-1);
                } else if(numOfSibs == 0 && recursivePrint == false) {
                        // printf("Child: %i  ", chiIndex);
                }
                numOfSibs++;

                // Scope Declarations
                if(t->nodekind == DeclK) {
                        if(DEBUG==true) { printf("DeclK %s, line: %d\n", t->attr.name, t->linenum); }

                        bool insertion = semanticsSymbolTable.insert((char *)t->attr.name, t);
                        if(t->kind.decl==FuncK) { semanticsSymbolTable.enter(t->attr.name); }

                        if(insertion==0) { // If insertion failed == already exists in table
                                TreeNode* node = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)t->attr.name));
                                printf("ERROR(%d): Symbol '%s' is already defined at line %d.\n", t->linenum, t->attr.name, node->linenum);
                        }
                        //TODO: Put recurse through children into function
                        for(int i = 0; i < MAXCHILDREN; i++) {
                                chiIndex = i;
                                scopeAndType(t->child[i], 0, types);
                                chiIndex = 0;
                        }
                        if(t->kind.decl==FuncK) { semanticsSymbolTable.leave(); }

                }
                // Scope Statements
                else if(t->nodekind == StmtK && t->kind.stmt == CompK) {
                        if(DEBUG==true) { printf("Compound Statement: Adding Scope\n"); }
                        semanticsSymbolTable.enter("Compound");
                        for(int i = 0; i < MAXCHILDREN; i++) {
                                chiIndex = i;
                                scopeAndType(t->child[i], 0, types);
                                chiIndex = 0;
                        }
                        if(semanticsSymbolTable.depth() > 1) {
                                semanticsSymbolTable.leave();
                                if(DEBUG==true) { printf("Leaving Scope\n"); }
                        }
                }
                // Scope Expressions
                else if(t->nodekind == ExprK && t->kind.expr==CallK) {
                        if(DEBUG==true) { printf("Expression Statement: Function Call\n"); }
                        TreeNode* node = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)t->attr.name));
                        if(node==NULL) { printf("ERROR(%d): Symbol '%s' is not defined.\n", t->linenum, t->attr.name); }
                        for(int i = 0; i < MAXCHILDREN; i++) {
                                chiIndex = i;
                                scopeAndType(t->child[i], 0, types);
                                chiIndex = 0;
                        }
                }
                else if(t->nodekind == ExprK && t->kind.expr==IdK) {
                        if(DEBUG==true) { printf("Expression Statement: ID\n"); }
                        TreeNode* node = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)t->attr.name));
                        if(node==NULL) { printf("ERROR(%d): Symbol '%s' is not defined.\n", t->linenum, t->attr.name); }
                        for(int i = 0; i < MAXCHILDREN; i++) {
                                chiIndex = i;
                                scopeAndType(t->child[i], 0, types);
                                chiIndex = 0;
                        }
                }
                else if(t->nodekind == ExprK && t->kind.expr==OpK)
                {
                        printf("Op: %s \n", t->attr.name);
                        if(is_in_vector(getUnaryOps(), t->attr.name)==false){
                          printf("Op2: %s \n", t->attr.name);
                            // printf("IDK what this is %s.\n", t->child[1]->attr.name);
                            TreeNode* node = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)t->child[1]->attr.name));
                            // printf("Type? %u\n", node->declType );
                            // if(node->declType != Bool) {printf("ERROR(%d): '%s' requires operands of %s but lhs is of %s.\n", node->linenum, "jhgf", Types[2], Types[node->declType]); }
                            if(is_in_vector(types[t->attr.name]["result"], Types[node->declType])==false){
                              printf("ERROR(%d): '%s' requires operands of %s but lhs is of %s.\n", t->linenum, t->attr.name, types[t->attr.name]["result"].front().c_str(), Types[node->declType]);
                            }

                            TreeNode* node2 = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)t->child[0]->attr.name));
                            // printf("Type? %u\n", node->declType );
                            // if(node->declType != Bool) {printf("ERROR(%d): '%s' requires operands of %s but lhs is of %s.\n", node->linenum, "jhgf", Types[2], Types[node->declType]); }
                            if(is_in_vector(types[t->attr.name]["result"], Types[node2->declType])==false){
                              printf("ERROR(%d): '%s' requires operands of %s but rhs is of %s.\n", t->linenum, t->attr.name, types[t->attr.name]["result"].front().c_str(), Types[node2->declType]);
                            }
                        }
                }
                else{
                        for(int i = 0; i < MAXCHILDREN; i++) {
                                chiIndex = i;
                                scopeAndType(t->child[i], 0, types);
                                chiIndex = 0;
                        }
                }



                if(t->nodekind == StmtK) {
                        switch(t->kind.stmt) {

                        case IfK:
                                // printf("If ");
                                break;
                        case WhileK:
                                // printf("While ");
                                break;
                        case CompK:
                                // printf("Compound ");
                                break;
                        case ReturnK:
                                // printf("Return ");
                                break;
                        case BreakK:
                                // printf("Break ");
                                break;
                        }
                } else if(t->nodekind == ExprK) {
                        switch(t->kind.expr) {
                        case ConstK:
                                // printf("Const: ");
                                switch(t->declType) {
                                case Int:
                                        // printf("%i ", t->attr.value);
                                        break;
                                case Bool:
                                        if(t->attr.value == 0) {
                                                // printf("false ");
                                        } else {
                                                // printf("true ");
                                        }
                                        break;
                                case Char:
                                        // printf("'%c' ", t->attr.cvalue);
                                        break;
                                case String:
                                        // printf("\"%s\" ", t->attr.string);
                                        break;
                                default:
                                        break;
                                }
                                break;
                        case IdK:
                                // printf("Id: %s ", t->attr.name);
                                break;
                        case OpK:
                                // printf("Op: %s ", t->attr.name);
                                break;
                        case AssignK:
                                // printf("Assign: %s ", t->attr.name);
                                break;
                        case CallK:
                                // printf("Call: %s ", t->attr.name);
                                break;
                        }
                } else if(t->nodekind == DeclK) {
                        switch(t->kind.decl) {
                        case FuncK:
                                // printf("Func %s returns ", t->attr.name);
                                break;
                        case VarK:
                                if(t->isArray == true) {
                                        // printf("Var %s is array of ", t->attr.name); // TODO:
                                } else {
                                        // printf("Var %s of ", t->attr.name);
                                }
                                break;
                        case ParamK:
                                if(t->isArray == true) {
                                        // printf("Param %s is array of ", t->attr.name); // TODO:
                                } else {
                                        // printf("Param %s of ", t->attr.name);
                                }
                                break;
                        case RecordK:
                        // printf("Record %s  ", t->attr.name);
                        default:
                                break;
                        }
                        switch(t->declType) {
                        case Void:
                                // printf("type void ");
                                break;
                        case Int:
                                // printf("type int ");
                                break;
                        case Bool:
                                // printf("type bool ");
                                break;
                        case Char:
                                // printf("type char ");
                                break;
                        case Record:
                                if(t->isRecord!=true) {
                                        // printf("type record ");
                                }
                                break;
                        default:
                                break;
                        }
                } else {
                        printf("Failed printing tree nodekind index: %u\n", t->nodekind);
                }
                // printf("[line: %d]", t->linenum);
                // for(int i = 0; i < MAXCHILDREN; i++) {
                //         chiIndex = i;
                //         scopeAndType(t->child[i], 0, types);
                //         chiIndex = 0;
                // }
                // if(semanticsSymbolTable.depth() > 1) {
                //         semanticsSymbolTable.leave();
                //         if(DEBUG==true) { printf("Leaving Scope\n"); }
                // }


        }
        sibIndex--;
        // spaces -= 4;
}
