#include "semantic.h"
#include "typingHelpers.h"
#include "symbolTable.h"
#include <string.h>
#include <stdio.h>
#include <string>
#include <sstream>


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
        // cout << vec.front() << endl;
        if ( find(vec.begin(), vec.end(), str) != vec.end() ) {
                // printf("Exists\n");
                return true;
        }
        else{
                // printf("Doesn't Exist\n");
                return false;
        }
}

string node_type(TreeNode* node){
        cout << "AAAA" << endl;
        if(node->nodekind == ExprK) {
                cout << "node_type: ExprK" << endl;
                if(node->kind.expr == ConstK) {
                        // cout << "node_type1: " << Types[node->declType] << endl;
                        return Types[node->declType];
                }
                else if(node->kind.expr == OpK) {
                        cout << "Hit Operator: Recursing in node_type." << endl;
                                scopeAndType(node, 0, types_map, true);
                }
                else{
                        cout << "aaa: " << node->attr.name << endl;
                        TreeNode* def_node = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)node->attr.name));
                        cout << "node_type2: " << Types[def_node->declType] << endl;
                        return Types[def_node->declType];
                }
        }
        else{
                cout << "node_type function failed in semantic.cpp." << endl;
                return NULL;
        }
}

bool is_array_node(TreeNode* node){
        if(node->nodekind == ExprK && node->kind.expr == ConstK) {
                // cout << "node_type1: " << Types[node->declType] << endl;
                return false;
        }
        else if(node->nodekind == ExprK) {
                TreeNode* def_node = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)node->attr.name));
                // cout << "node_type2: " << Types[def_node->declType] << endl;
                return Types[def_node->isArray];
        }
        else{
                cout << "is_array function failed in semantic.cpp." << endl;
                return false;
        }
}

map<string, string> check_operands_types_same(TreeNode* t){
        // TreeNode* node_right = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)t->child[1]->attr.name));
        // printf("nodey->declType: %s\n", Types[node_right->declType]);
        // TreeNode* node_left = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)t->child[0]->attr.name));
        // printf("nodey->declType: %s\n", Types[node_left->declType]);

        string left_node_type = node_type(t->child[0]);
        string right_node_type = node_type(t->child[1]);


        stringstream ss;
        ss << t->linenum;
        string line_number = ss.str();
        string attribute_name(t->attr.name);
        map<string, string> data;
        data["linenum"] = line_number;
        data["name"] = attribute_name;
        if(left_node_type != right_node_type) {
                data["identical_types"] = "false";
                data["left_type"] = left_node_type;
                data["right_type"] =right_node_type;
                return data;
                // printf("ERROR(%d): '%s' requires operands of the same type but lhs is %s and rhs is %s.\n", t->linenum, t->attr.name, Types[node_left->declType], Types[node_right->declType]);
        }
        else{
                data["identical_types"] = "true";
                data["left_type"] = left_node_type;
                data["right_type"] = right_node_type;
                return data;
        }
}

// map<string, string> check_operands_types_same(TreeNode* t){
//         TreeNode* node_right = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)t->child[1]->attr.name));
//         // printf("nodey->declType: %s\n", Types[node_right->declType]);
//         TreeNode* node_left = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)t->child[0]->attr.name));
//         // printf("nodey->declType: %s\n", Types[node_left->declType]);
//
//         stringstream ss;
//         ss << t->linenum;
//         string line_number = ss.str();
//         string attribute_name(t->attr.name);
//         map<string, string> data;
//         data["linenum"] = line_number;
//         data["name"] = attribute_name;
//         if(node_left->declType != node_right->declType) {
//                 data["identical_types"] = "false";
//                 data["left_type"] = Types[node_left->declType];
//                 data["right_type"] =Types[node_right->declType];
//                 return data;
//                 // printf("ERROR(%d): '%s' requires operands of the same type but lhs is %s and rhs is %s.\n", t->linenum, t->attr.name, Types[node_left->declType], Types[node_right->declType]);
//         }
//         else{
//                 data["identical_types"] = "true";
//                 data["left_type"] = Types[node_left->declType];
//                 data["right_type"] = Types[node_right->declType];
//                 return data;
//         }
// }

map<string, string> check_operands_types_int(TreeNode* t){

        if(t->child[1]->attr.name) {
                printf("Child 1 has a name!\n");
        }
        if(t->child[0]->attr.name) {
                printf("Child 0 has a name!\n");
        }
        TreeNode* node_right = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)t->child[1]->attr.name));
        // printf("nodey->declType: %s\n", Types[node_right->declType]);
        TreeNode* node_left = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)t->child[0]->attr.name));
        // printf("nodey->declType: %s\n", Types[node_left->declType]);

        stringstream ss;
        ss << t->linenum;
        string line_number = ss.str();
        string attribute_name(t->attr.name);
        map<string, string> data;
        data["linenum"] = line_number;
        data["name"] = attribute_name;
        if(node_left->declType != node_right->declType) {
                data["identical_types"] = "false";
                data["left_type"] = Types[node_left->declType];
                data["right_type"] =Types[node_right->declType];
                return data;
                // printf("ERROR(%d): '%s' requires operands of the same type but lhs is %s and rhs is %s.\n", t->linenum, t->attr.name, Types[node_left->declType], Types[node_right->declType]);
        }
        else{
                data["identical_types"] = "true";
                data["left_type"] = Types[node_left->declType];
                data["right_type"] = Types[node_right->declType];
                return data;
        }
}


vector<string> getUnaryOps(){
        // cout << "Getting Unary Ops" << endl;
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


void recurse_through_children(TreeNode* node){
  for(int i = 0; i < MAXCHILDREN; i++) {
          chiIndex = i;
          scopeAndType(node->child[i], 0, types_map, true);
          chiIndex = 0;
  }
}



void scopeAndType(TreeNode *tree, int numOfSibs, map<string, map<string, vector<string> > > & types, bool FuncKRecurse) {

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
                printf("---- line: %d\n", t->linenum );
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
                        // for(int i = 0; i < MAXCHILDREN; i++) {
                        //         chiIndex = i;
                        //         scopeAndType(t->child[i], 0, types, true);
                        //         chiIndex = 0;
                        // }
                        recurse_through_children(t);
                        if(t->kind.decl==FuncK) { semanticsSymbolTable.leave(); }

                }
                // Scope Statements
                else if(t->nodekind == StmtK && t->kind.stmt == CompK) {
                        if(DEBUG==true) { printf("Compound Statement: Adding Scope\n"); }
                        if(FuncKRecurse==false) {semanticsSymbolTable.enter("Compound"); }
                        // for(int i = 0; i < MAXCHILDREN; i++) {
                        //         chiIndex = i;
                        //         scopeAndType(t->child[i], 0, types, false);
                        //         chiIndex = 0;
                        // }
                        recurse_through_children(t);
                        if(FuncKRecurse==false) {
                                semanticsSymbolTable.leave();
                                if(DEBUG==true) { printf("Leaving Scope\n"); }
                        }
                }

                // Scope Expressions
                else if(t->nodekind == ExprK && t->kind.expr==CallK) {
                        if(DEBUG==true) { printf("Expression Statement: Function Call\n"); }
                        TreeNode* node = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)t->attr.name));
                        if(node==NULL) { printf("ERROR(%d): Symbol '%s' is not defined.\n", t->linenum, t->attr.name); }
                        // for(int i = 0; i < MAXCHILDREN; i++) {
                        //         chiIndex = i;
                        //         scopeAndType(t->child[i], 0, types, false);
                        //         chiIndex = 0;
                        // }
                        recurse_through_children(t);
                }
                else if(t->nodekind == ExprK && t->kind.expr==IdK) {
                        if(DEBUG==true) { printf("Expression Statement: ID\n"); }
                        TreeNode* node = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)t->attr.name));
                        if(node==NULL) { printf("ERROR(%d): Symbol '%s' is not defined.\n", t->linenum, t->attr.name); }
                        // for(int i = 0; i < MAXCHILDREN; i++) {
                        //         chiIndex = i;
                        //         scopeAndType(t->child[i], 0, types, false);
                        //         chiIndex = 0;
                        // }
                        recurse_through_children(t);
                }
                else if(t->nodekind == ExprK)
                {

                        if(t->kind.expr==OpK) {
                                printf("Op: %s \n", t->attr.name);
                                if(strcmp(t->attr.name, ">")==0 || strcmp(t->attr.name, "<")==0) {
                                        printf("Op: %s \n", t->attr.name);
                                        map<string, string> info = check_operands_types_same(t);
                                        if(info["identical_types"] == "false") {
                                                printf("ERROR(%s): '%s' requires operands of the same type but lhs is %s and rhs is %s.\n", info["linenum"].c_str(), info["name"].c_str(), info["left_type"].c_str(), info["right_type"].c_str());
                                        }
                                        else if(is_array_node(t->child[0])==true || is_array_node(t->child[1])==true) {
                                                printf("ERROR(%d): The operation '%s' does not work with arrays.\n", t->linenum, t->attr.name);
                                        }
                                }
                                if(strcmp(t->attr.name, "+")==0 || strcmp(t->attr.name, "-")==0 || strcmp(t->attr.name, "*")==0) {
                                        // cout << "made it!" << endl;
                                        string left_node_type = node_type(t->child[0]);
                                        // cout << "left_node_type: " << left_node_type << endl;
                                        string right_node_type = node_type(t->child[1]);
                                        // cout << "right_node_type: " << right_node_type << endl;
                                        int line = t->linenum;
                                        // cout << "line: " << line << endl;
                                        char* name = t->attr.name;
                                        // cout << "name: " << name << endl;
                                        string req_right_op = types[t->attr.name]["right"].front();
                                        // cout << "req_right_op: " << req_right_op << endl;
                                        string req_left_op = types[t->attr.name]["left"].front();
                                        // cout << "req_right_op: " << req_left_op << endl;
                                        if(is_in_vector(types[t->attr.name]["left"], left_node_type)==false) {
                                                printf("ERROR(%d): '%s' requires operands of %s but lhs is of %s.\n", line, name, req_left_op.c_str(), left_node_type.c_str());
                                        }
                                        if(is_in_vector(types[t->attr.name]["right"], right_node_type)==false) {
                                                printf("ERROR(%d): '%s' requires operands of %s but lhs is of %s.\n", line, name, req_right_op.c_str(), right_node_type.c_str());
                                        }
                                }
                                // if(is_in_vector(getUnaryOps(), t->attr.name)==false) {
                                //         // printf("Op2: %s \n", t->attr.name);
                                //         // printf("IDK what this is %s.\n", t->child[1]->attr.name);
                                //         TreeNode* node = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)t->child[1]->attr.name));
                                //         // printf("Type? %u\n", node->declType );
                                //         // if(node->declType != Bool) {printf("ERROR(%d): '%s' requires operands of %s but lhs is of %s.\n", node->linenum, "jhgf", Types[2], Types[node->declType]); }
                                //         if(is_in_vector(types[t->attr.name]["left"], Types[node->declType])==false) {
                                //                 printf("ERROR(%d): '%s' requires operands of %s but lhs is of %s.\n", t->linenum, t->attr.name, types[t->attr.name]["result"].front().c_str(), Types[node->declType]);
                                //         }
                                //
                                //         TreeNode* node2 = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)t->child[0]->attr.name));
                                //         // printf("Type? %u\n", node->declType );
                                //         // if(node->declType != Bool) {printf("ERROR(%d): '%s' requires operands of %s but lhs is of %s.\n", node->linenum, "jhgf", Types[2], Types[node->declType]); }
                                //         if(is_in_vector(types[t->attr.name]["right"], Types[node2->declType])==false) {
                                //                 printf("ERROR(%d): '%s' requires operands of %s but rhs is of %s.\n", t->linenum, t->attr.name, types[t->attr.name]["result"].front().c_str(), Types[node2->declType]);
                                //         }
                                // }
                                if(strcmp(t->attr.name, "==")==0) {
                                        map<string, string> info = check_operands_types_same(t);
                                        if(info["identical_types"] == "false") {
                                                printf("ERROR(%s): '%s' requires operands of the same type but lhs is %s and rhs is %s.\n", info["linenum"].c_str(), info["name"].c_str(), info["left_type"].c_str(), info["right_type"].c_str());
                                        }
                                }
                                if(strcmp(t->attr.name, "not")==0) {
                                        cout << "yay" << endl;
                                        if(t->child[0]!=NULL) {
                                                cout << "yay2" << endl;
                                                string left_type = node_type(t->child[0]);
                                                cout << left_type << endl;
                                                if(left_type != types[t->attr.name]["left"].front()) {
                                                        printf("ERROR(%d): Unary '%s' requires an operand of type %s but was given %s.\n", t->linenum, t->attr.name, types[t->attr.name]["left"].front().c_str(),left_type.c_str() );
                                                }
                                        }

                                        // if(t->child[2] != NULL) {
                                        //         string right_type = node_type(t->child[2]);
                                        //         cout << right_type << endl;
                                        //         if(right_type != types[t->attr.name]["right"].front()) {
                                        //                 printf("ERROR(%d): Unary '%s' requires an operand of type %s but was given %s.\n", t->linenum, t->attr.name, types[t->attr.name]["right"].front().c_str(),right_type.c_str() );
                                        //         }
                                        // }
                                        cout << "endddd" <<endl;
                                }
                        }

                        if(t->kind.expr==AssignK) {
                                // printf("ExprK1: %s\n", t->attr.name);
                                if(strcmp(t->attr.name,"=")==0) {
                                        // printf("ExprK2: %s, line: %d\n", t->attr.name, t->linenum);
                                        TreeNode* nodex = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)t->child[1]->attr.name));
                                        // printf("child[1]: %s, line: %d\n", nodex->attr.name, t->linenum);
                                        bool insertion = semanticsSymbolTable.insert((char *)t->attr.name, t);
                                        // printf("insertion %u\n", insertion);
                                        if(insertion==1) {
                                                TreeNode* node = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)t->child[1]->attr.name));
                                                if(node->kind.decl==FuncK) {
                                                        printf("ERROR(%d): Cannot use function '%s' as a variable.\n", t->linenum, node->attr.name);
                                                }
                                        }


                                }
                                if(strcmp(t->attr.name, "=")==0 || strcmp(t->attr.name, ">")==0) {
                                        TreeNode* node_right = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)t->child[1]->attr.name));
                                        // printf("nodey->declType: %s\n", Types[node_right->declType]);
                                        TreeNode* node_left = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)t->child[0]->attr.name));
                                        // printf("nodey->declType: %s\n", Types[node_left->declType]);
                                        if(node_left->declType != node_right->declType) {
                                                printf("ERROR(%d): '%s' requires operands of the same type but lhs is %s and rhs is %s.\n", t->linenum, t->attr.name, Types[node_left->declType], Types[node_right->declType]);
                                        }
                                }
                                else if(strcmp(t->attr.name, "+=")==0 || strcmp(t->attr.name, "-=")==0) {
                                        TreeNode* node_right = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)t->child[1]->attr.name));
                                        // printf("nodey->declType: %s\n", Types[node_right->declType]);
                                        TreeNode* node_left = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)t->child[0]->attr.name));
                                        // printf("nodey->declType: %s\n", Types[node_left->declType]);

                                        if(is_in_vector(types[t->attr.name]["left"], Types[node_left->declType])==false) {
                                                printf("ERROR(%d): '%s' requires operands of %s but lhs is of %s.\n", t->linenum, t->attr.name, types[t->attr.name]["left"].front().c_str(), Types[node_left->declType]);
                                        }
                                        if(is_in_vector( types[t->attr.name]["right"], Types[node_right->declType] )==false) {
                                                printf("ERROR(%d): '%s' requires operands of %s but rhs is of %s.\n", t->linenum, t->attr.name, types[t->attr.name]["right"].front().c_str(), Types[node_right->declType]);
                                        }
                                }
                        }

                }
                else{
                        for(int i = 0; i < MAXCHILDREN; i++) {
                                chiIndex = i;
                                scopeAndType(t->child[i], 0, types, false);
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
                //         scopeAndType(t->child[i], 0, types, false);
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
