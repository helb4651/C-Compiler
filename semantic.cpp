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
static int loop_layer = 0;

bool main_function_exists = false;

// static bool DEBUG=true;
static bool DEBUG = false;
static bool SCOPE_DEBUG = false;

static TreeNode *currentFunction;
static bool hasReturned = false;

SymbolTable semanticsSymbolTable;


char const *Types[] = {"type void", "type int", "type bool", "type char", "type string", "type record",
                       "undefined type"};

void recurse_through_children(TreeNode *node, bool Function_Recurse) {

    for (int i = 0; i < MAXCHILDREN; i++) {
        chiIndex = i;
        scopeAndType(node->child[i], 0, Function_Recurse);
        chiIndex = 0;
    }
}


int get_number_of_siblings(TreeNode *t){
    int num_sibs=0;

    while(t->sibling!=NULL){
        t=t->sibling;
        num_sibs++;
    }
//    cout << t->linenum << " " << num_sibs << endl;
    return num_sibs;
}

bool check_node_defined(TreeNode *t) {
    if ((t->nodekind == ExprK && t->kind.expr == IdK) || (t->nodekind == DeclK && t->kind.decl == VarK)) {
        TreeNode *node = static_cast<TreeNode *>(semanticsSymbolTable.lookup((char *) t->attr.name));
        if (node != NULL) return true;
    }
    return false;
}


bool is_in_vector(vector <string> vec, string str) {
    // cout << str << endl;
    // cout << vec.front() << endl;
    if (find(vec.begin(), vec.end(), str) != vec.end()) {
        // printf("Exists\n");
        return true;
    } else {
        // printf("Doesn't Exist\n");
        // cout << "1: " << str << "2: " << vec.front() << endl;
        return false;
    }
}

void check_children_bool(TreeNode* t){
    if(DEBUG) printf("   Start: check_children_bool\n");

    if(t->child[0]->declType!=Bool){
        printf("ERROR(%d): Expecting Boolean test condition in %s statement but got %s.\n", t->linenum, t->attr.name, Types[t->child[0]->declType]);
    }
    if(t->child[0]!=NULL && t->child[0]->isArray){
        printf("ERROR(%d): Cannot use array as test condition in %s statement.\n",t->linenum, t->attr.name);
    }
    if(t->child[1]!=NULL && t->child[1]->isArray){
        printf("ERROR(%d): Cannot use array as test condition in %s statement.\n",t->linenum, t->attr.name);
    }
    if(t->child[2]!=NULL && t->child[2]->isArray){
        printf("ERROR(%d): Cannot use array as test condition in %s statement.\n",t->linenum, t->attr.name);
    }


    if(DEBUG) printf("   End: check_children_bool\n");
}

//void semantics(TreeNode* t){
//        if(DEBUG) printf("    Beginning Assignment Semantics...\n");
//        if( t->child[0]->declType != t->child[1]->declType && t->child[1]->declType!=UndefinedType && t->child[0]->declType!=UndefinedType) {
//                //if(DEBUG==true) printf("Right: %s, Left: %s\n", Types[t->child[1]->declType], Types[t->child[0]->declType]);
//                printf("ERROR(%d): '%s' requires operands of the same type but lhs is %s and rhs is %s.\n", t->linenum, t->attr.name, Types[t->child[0]->declType], Types[t->child[1]->declType]);
//                number_of_errors++;
//        }
//        if(DEBUG) printf("    Completed Assignment Semantics...\n");
//
//}

string node_type(TreeNode *node) {
    if (DEBUG == true) cout << "   node_type" << endl;
    return Types[node->declType];
    // if(node->attrType==Name) {
    //         if(DEBUG==true) printf("    Looking up type...\n");
    //         TreeNode* typed_node = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)node->attr.name));
    //         if(DEBUG==true) printf("    Returning type...\n");
    //         return Types[typed_node->declType];
    // } else if(node->attrType==UndefinedAttrType) {
    //         printf("      node_type: Help, Help UndefinedAttrType!\n");
    //         return "undefined type";
    // }
    // else {
    //         printf("      node_type: Help, Help!\n");
    //         return "undefined type";
    // }


}

bool is_array_node(TreeNode *node) {
    if (node->nodekind == ExprK && node->kind.expr == ConstK) {
        // cout << "node_type1: " << Types[node->declType] << endl;
        return false;
    } else if (node->nodekind == ExprK) {
        TreeNode *def_node = static_cast<TreeNode *>(semanticsSymbolTable.lookup((char *) node->attr.name));
        node->declType = def_node->declType;
        // cout << "node_type2: " << Types[def_node->declType] << endl;
        return Types[def_node->isArray];
    } else {
        cout << "is_array_node function failed in semantic.cpp." << endl;
        return false;
    }
}


void scopeAndType(TreeNode *tree, int numOfSibs, bool FuncKRecurse) {

    bool recursivePrint = false;
    bool recurse_already = false;
    if (numOfSibs == -1) {
        numOfSibs++;
        recursivePrint = true;
    } else {
        spaces += 4;
    }

    for (TreeNode *t = tree; t != NULL; t = t->sibling) {
        recurse_already = false;
        if(DEBUG==true) printf("-- line: %d\n", t->linenum );



        if (t->nodekind == StmtK) {
            if (DEBUG == true) cout << "   StmtK" << endl;
            switch (t->kind.stmt) {

                case IfK:
                    if(DEBUG) printf("   If\n");
                    semanticsSymbolTable.enter("If");
                    recurse_through_children(t, false);
                    recurse_already = true;
                    check_children_bool(t);
//                    if(t->child[0]!=NULL && t->child[0]->isArray==true){
//                        printf("ERROR(%d): Cannot use array as test condition in if statement.\n", t->linenum);
//                    }
//                    if(t->child[1]!=NULL && t->child[1]->isArray==true){
//                        printf("ERROR(%d): Cannot use array as test condition in if statement.\n", t->linenum);
//                    }
                    semanticsSymbolTable.leave();
                    break;
                case WhileK:
                    if(DEBUG) printf("   While\n");
                    loop_layer++;
                    semanticsSymbolTable.enter("While");
                    recurse_through_children(t, false);
                    recurse_already = true;
                    check_children_bool(t);
                    loop_layer--;
                    semanticsSymbolTable.leave();
                    break;
                case CompK: {
                    if(DEBUG) printf("   Compound\n");

                    if (FuncKRecurse == false) {
                        semanticsSymbolTable.enter("Compound");
                        if (SCOPE_DEBUG == true) { printf("   Compound Statement: Adding Scope: Line %d\n", t->linenum); }
                    }
                    recurse_through_children(t, false);
                    recurse_already = true;
                    if (FuncKRecurse == false) {
                        semanticsSymbolTable.leave();
                        if (SCOPE_DEBUG == true) { printf("   Compound Statement: Leaving Scope: Line %d\n", t->linenum); }
                    }

                    break;
                }
                case ReturnK:
                    if (DEBUG == true) cout << "ReturnK" << endl;
                    hasReturned = true;
                    if (t->child[0] != NULL && t->child[0]->nodekind == ExprK) {
                        if (t->child[0]->kind.expr == IdK) {
                            TreeNode *node = static_cast<TreeNode *>(semanticsSymbolTable.lookup(
                                    (char *) t->child[0]->attr.name));
                            if (node != NULL) {
                                if (node->isArray == true) {
                                    printf("ERROR(%d): Cannot return an array.\n", t->linenum);
                                    number_of_errors++;
                                }
                                if (node->declType!=currentFunction->declType){
                                    printf("ERROR(%d): Function '%s' at line %d is expecting to return %s but instead returns %s.\n",
                                           t->linenum,
                                           currentFunction->attr.name,
                                           currentFunction->linenum,
                                           Types[currentFunction->declType],
                                           Types[node->declType]
                                    );
                                }
                            }
                        }
                        else if (t->child[0]->attrType==Value && currentFunction->declType!=Void){
                            if (t->child[0]->declType!=currentFunction->declType){
                                printf("ERROR(%d): Function '%s' at line %d is expecting to return %s but instead returns %s.\n",
                                       t->linenum,
                                       currentFunction->attr.name,
                                       currentFunction->linenum,
                                       Types[currentFunction->declType],
                                       Types[t->child[0]->declType]
                                );
                            }
                        }
                    }
                    if(currentFunction->declType!=Void && t->child[0]==NULL) {
                        printf("ERROR(%d): Function '%s' at line %d is expecting to return %s but return has no return value.\n",
                               t->linenum, currentFunction->attr.name, currentFunction->linenum,
                               Types[currentFunction->declType]
                        );
                    }
                    if(currentFunction->declType==Void && t->child[0]!=NULL) {
                        printf("ERROR(%d): Function '%s' at line %d is expecting no return value, but return has return value.\n",
                               t->linenum, currentFunction->attr.name, currentFunction->linenum
                        );
                    }


                    // printf("Return ");
                    break;
                case BreakK:
                    if(loop_layer==0){
                        printf("ERROR(%d): Cannot have a break statement outside of loop.\n", t->linenum);
                    } else if(loop_layer<0){
                        cout << "HEY loop_layer is NEGATIVE!!!" << endl;
                    }
                    break;
            }
        } else if (t->nodekind == ExprK) {
            if (DEBUG == true) cout << "   ExprK-";
            switch (t->kind.expr) {
                case ConstK: {
                    if (DEBUG == true) cout << "ConstK-";
                    switch (t->declType) {
                        case Int:
                            if (DEBUG == true) cout << "Int" << endl;
                            // printf("%i ", t->attr.value);
                            break;
                        case Bool:
                            if (DEBUG == true) cout << "Bool" << endl;
                            if (t->attr.value == 0) {
                                // printf("false ");
                            } else {
                                // printf("true ");
                            }
                            break;
                        case Char:
                            if (DEBUG == true) cout << "Char" << endl;
                            // printf("'%c' ", t->attr.cvalue);
                            break;
                        case String:
                            if (DEBUG == true) cout << "String" << endl;
                            // printf("\"%s\" ", t->attr.string);
                            break;
                        default:
                            if (DEBUG == true) cout << "!Default!" << endl;
                            break;
                    }
                    break;
                }
                case IdK: {
                    if (DEBUG) cout << "IdK: " << t->attr.name << endl;
                    TreeNode *nodeIdK = static_cast<TreeNode *>(semanticsSymbolTable.lookup((char *) t->attr.name));
                    if (nodeIdK == NULL) {
                        printf("ERROR(%d): Symbol '%s' is not defined.\n", t->linenum, t->attr.name);
                        t->declType = UndefinedType;
                        number_of_errors++;
                    } else {
                        // Assign Type to ID Node

                        if (nodeIdK->child[0] != NULL && nodeIdK->child[0]->nodekind == ExprK &&
                            nodeIdK->child[0]->kind.expr == IdK) {
                            printf("ERROR(%d): Symbol '%s' is not defined.\n", t->linenum, t->attr.name);
                            number_of_errors++;
                            t->declType = UndefinedType;
                        } else {
                            // cout << "line: " << t->linenum << endl;
                            t->declType = nodeIdK->declType;
                        }
                        if (nodeIdK->isArray) {
                            // cout << "   Array node: " << t->attr.name << endl;
                            t->isArray = true;
                        }
                        // printf("Id: %s assigning type: %s\n", t->attr.name, Types[nodeIdK->declType]);

                        if (nodeIdK->nodekind == DeclK) {
                            if (nodeIdK->kind.decl == FuncK) {
                                printf("ERROR(%d): Cannot use function '%s' as a variable.\n", t->linenum,
                                       t->attr.name);
                                number_of_errors++;
                                t->declType = UndefinedType;
                            }
                        }

                    }
                    if (DEBUG) printf("   Leaving IdK\n");
                    break;
                }
                case OpK: {
                    if (DEBUG == true) cout << "OpK\n";
                    recurse_already = true;
                    recurse_through_children(t, false);

                    /*
                       TODO: Code more beautifully. This assigns the op a child ops type if there is a child op,
                          otherwise it defaults to the type of child[0].
                     */
                    if (t->child[1] != NULL) {
                        if (t->child[1]->nodekind == ExprK) {
                            if (t->child[1]->kind.expr == OpK) {
                                // cout << "Type1: " << Types[t->declType] << "line: " << t->linenum << endl;
                                t->declType = t->child[0]->declType;
                            } else {
                                // cout << "Type2: " << Types[t->declType] << "line: " << t->linenum << endl;
                                t->declType = t->child[0]->declType;
                            }
                        } else {
                            // cout << "Type2: " << Types[t->declType] << "line: " << t->linenum << endl;
                            t->declType = t->child[0]->declType;
                        }
                    } else {
                        // cout << "Type2: " << Types[t->declType] << "line: " << t->linenum << endl;
                        t->declType = t->child[0]->declType;
                    }

                    // t->declType=t->child[0]->declType;

                    // printf("Op: %s ", t->attr.name);
                    // if(DEBUG==true) printf("Op: %s \n", t->attr.name);

                    // if(t->attrType==Name) {

                    if (strcmp(t->attr.name, "[") == 0) {
                        if (DEBUG == true) cout << "   [" << endl;


                        if (strcmp(t->attr.name, "[") == 0 && t->child[0] != NULL) {
                            TreeNode *nodeIdK = static_cast<TreeNode *>(semanticsSymbolTable.lookup(
                                    (char *) t->child[0]->attr.name));
                            if (nodeIdK != NULL) {

//                                                cout << "asdf: " << t->attr.name << t->linenum <<endl;
                                if (nodeIdK->isArray == false && strcmp(nodeIdK->attr.name, "[") == 0) {

                                    printf("ERROR(%d): Cannot index nonarray.\n", t->linenum);
                                    number_of_errors++;
                                }
                                if (nodeIdK->isArray == false && strcmp(nodeIdK->attr.name, "[") != 0) {
                                    printf("ERROR(%d): Cannot index nonarray '%s'.\n",
                                           t->linenum, nodeIdK->attr.name);
                                    number_of_errors++;
                                }

                                // t->declType = nodeIdK->declType;
                            } else {
//                                                cout << "asdf: " << t->attr.name << t->linenum <<endl;
                                if (t->isArray == false && strcmp(t->child[0]->attr.name, "[") == 0) {
                                    printf("ERROR(%d): Cannot index nonarray.\n", t->linenum);
                                    number_of_errors++;
                                }
                                if (t->isArray == false && strcmp(t->child[0]->attr.name, "[") != 0) {
                                    printf("ERROR(%d): Cannot index nonarray '%s'.\n", t->linenum,
                                           t->child[0]->attr.name);
                                    number_of_errors++;
                                }

                                // t->declType = UndefinedType;
                                // t->child[0]->declType = UndefinedType;
                            }
                            if (t->child[1] != NULL) {
                                if (t->child[1]->declType != Int && t->child[1]->declType != UndefinedType) {
                                    // cout << "attr: " << t->child[1]->attrType << endl;
                                    printf("ERROR(%d): Array '%s' should be indexed by type int but got %s.\n",
                                           t->linenum, t->child[0]->attr.name, Types[t->child[1]->declType]);
                                    number_of_errors++;
                                }
                                if (strcmp(t->attr.name, "[") == 0 && t->child[0]->isArray == true &&
                                    t->child[1]->isArray == true //&& t->child[1]->chlid[1]==NULL
                                        ) {
                                    printf("ERROR(%d): Array index is the unindexed array '%s'.\n", t->linenum,
                                           t->child[1]->attr.name);
                                    number_of_errors++;
                                }
                            }


                            // t->declType=t->child[0]->declType;
//                                        printf("   child[0]: %s\n", t->child[0]->attr.name);

                        }
                    } else if (strcmp(t->attr.name, "and") == 0 || strcmp(t->attr.name, "or") == 0 ||
                               strcmp(t->attr.name, "+") == 0 || strcmp(t->attr.name, "-") == 0 ||
                               strcmp(t->attr.name, "*") == 0 || strcmp(t->attr.name, "/") == 0 ||
                               strcmp(t->attr.name, "%") == 0 || strcmp(t->attr.name, "not") == 0 ||
                               strcmp(t->attr.name, ">=") == 0 || strcmp(t->attr.name, "<=") == 0 ||
                               strcmp(t->attr.name, "==") == 0 || strcmp(t->attr.name, "!=") == 0 ||
                               strcmp(t->attr.name, ">") == 0 || strcmp(t->attr.name, "<") == 0 ||
                               strcmp(t->attr.name, "?") == 0) {
                        if (DEBUG == true) printf("   Beginning Op Processing...\n");

                        // if(DEBUG) printf("    Processing Ops: child[0]= %s line: %d\n", t->child[0]->attr.name, t->linenum);
                        // cout << "here: " << t->attr.name << endl;

                        if (t->child[0] != NULL && t->child[1] == NULL) {
                            if (types_map[t->attr.name]["Unary"].front() == "true" && t->child[1] == NULL
                                && Types[t->child[0]->declType] != types_map[t->attr.name]["result"].front()
                                && t->child[0]->declType != UndefinedType && strcmp(t->attr.name, "*") != 0) {
                                if (DEBUG) cout << "   Checking Unary stuff: " << t->linenum << endl;
                                printf("ERROR(%d): Unary '%s' requires an operand of %s but was given %s.\n",
                                       t->linenum, t->attr.name, types_map[t->attr.name]["result"].front().c_str(),
                                       Types[t->child[0]->declType]);
                                number_of_errors++;
                            }
                            if (t->child[0]->isArray == true) {
                                if (DEBUG)
                                    cout << "   Checking if op: " << t->attr.name << " works with arrays. line :"
                                         << t->linenum << endl;
                                if (types_map[t->attr.name]["WithArrays"].front() == "false") {
                                    printf("ERROR(%d): The operation '%s' does not work with arrays.\n", t->linenum,
                                           t->attr.name);
                                    number_of_errors++;
                                }
                            } else if (t->child[0]->isArray == false && strcmp(t->attr.name, "*") == 0 &&
                                       t->child[1] == NULL && t->child[0]->declType != UndefinedType) {
                                printf("ERROR(%d): The operation '%s' only works with arrays.\n", t->linenum,
                                       t->attr.name);
                                number_of_errors++;
                            }


                        }

                        // Not Unary
                        if (t->child[0] != NULL && t->child[1] != NULL) {
                            if (t->child[1] != NULL) {
                                // Line below seg faults
                                // cout << "here " << t->linenum << "att " << t->attr.name<< endl;

                                if (DEBUG) printf("   Checking lhs and rhs types...\n");
                                vector <string> allowed_left_ops = types_map[t->attr.name]["left"];
                                vector <string> allowed_right_ops = types_map[t->attr.name]["right"];

                                if ((allowed_left_ops.size() == 1 && allowed_right_ops.size() == 1) ||
                                    strcmp(t->attr.name, "!=") == 0 || strcmp(t->attr.name, "==") == 0) {
                                    if (is_in_vector(allowed_left_ops, Types[t->child[0]->declType]) == false &&
                                        t->child[0]->declType != UndefinedType) {
                                        if (t->child[0]->declType == Void &&
                                            (strcmp(t->attr.name, "!=") == 0 || strcmp(t->attr.name, "==") == 0)) {
                                            printf("ERROR(%d): '%s' requires operands of NONVOID but lhs is of %s.\n",
                                                   t->linenum, t->attr.name, Types[t->child[0]->declType]);
                                            number_of_errors++;
                                        } else {
                                            printf("ERROR(%d): '%s' requires operands of %s but lhs is of %s.\n",
                                                   t->linenum, t->attr.name,
                                                   types_map[t->attr.name]["left"].front().c_str(),
                                                   Types[t->child[0]->declType]);
                                            number_of_errors++;
                                        }

                                    }
                                    if (is_in_vector(allowed_right_ops, Types[t->child[1]->declType]) == false &&
                                        t->child[1]->declType != UndefinedType) {
                                        if (t->child[1]->declType == Void &&
                                            (strcmp(t->attr.name, "!=") == 0 || strcmp(t->attr.name, "==") == 0)) {
                                            printf("ERROR(%d): '%s' requires operands of NONVOID but rhs is of %s.\n",
                                                   t->linenum, t->attr.name, Types[t->child[1]->declType]);
                                            number_of_errors++;

                                        } else {
                                            printf("ERROR(%d): '%s' requires operands of %s but rhs is of %s.\n",
                                                   t->linenum, t->attr.name,
                                                   types_map[t->attr.name]["right"].front().c_str(),
                                                   Types[t->child[1]->declType]);
                                            number_of_errors++;
                                        }

                                    }

                                    if (t->child[0]->declType != t->child[1]->declType &&
                                        is_in_vector(allowed_right_ops, Types[t->child[1]->declType]) == true &&
                                        is_in_vector(allowed_left_ops, Types[t->child[0]->declType]) == true) {
                                        printf("ERROR(%d): '%s' requires operands of the same type but lhs is %s and rhs is %s.\n",
                                               t->linenum, t->attr.name, Types[t->child[0]->declType],
                                               Types[t->child[1]->declType]);
                                        number_of_errors++;
                                    }

                                } else if (allowed_left_ops.size() == 2 && allowed_right_ops.size() == 2) {

                                    if (is_in_vector(allowed_left_ops, Types[t->child[0]->declType]) == false &&
                                        t->child[0]->declType != UndefinedType) {
                                        printf("ERROR(%d): '%s' requires operands of %s or %s but lhs is of %s.\n",
                                               t->linenum, t->attr.name, types_map[t->attr.name]["left"][1].c_str(),
                                               types_map[t->attr.name]["left"][0].c_str(),
                                               Types[t->child[0]->declType]);
                                        number_of_errors++;
                                    }
                                    if (is_in_vector(allowed_right_ops, Types[t->child[1]->declType]) == false &&
                                        t->child[1]->declType != UndefinedType) {
                                        printf("ERROR(%d): '%s' requires operands of %s or %s but rhs is of %s.\n",
                                               t->linenum, t->attr.name, types_map[t->attr.name]["right"][1].c_str(),
                                               types_map[t->attr.name]["left"][0].c_str(),
                                               Types[t->child[1]->declType]);
                                        number_of_errors++;
                                    }
                                    if (t->child[0]->declType != t->child[1]->declType &&
                                        is_in_vector(allowed_right_ops, Types[t->child[1]->declType]) == true &&
                                        is_in_vector(allowed_left_ops, Types[t->child[0]->declType]) == true) {
                                        printf("ERROR(%d): '%s' requires operands of the same type but lhs is %s and rhs is %s.\n",
                                               t->linenum, t->attr.name, Types[t->child[0]->declType],
                                               Types[t->child[1]->declType]);
                                        number_of_errors++;
                                    }
                                }
                                if (t->child[0]->isArray == true || t->child[1]->isArray == true) {
                                    if (DEBUG)
                                        cout << "   Checking if op: " << t->attr.name << " works with arrays. line :"
                                             << t->linenum << endl;
                                    if (types_map[t->attr.name]["WithArrays"].front() == "false") {
                                        printf("ERROR(%d): The operation '%s' does not work with arrays.\n", t->linenum,
                                               t->attr.name);
                                        number_of_errors++;
                                    }
                                    if (strcmp(t->attr.name, "*") == 0 && t->child[0]->declType != UndefinedType &&
                                        t->child[1]->declType != UndefinedType) {
                                        printf("ERROR(%d): The operation '%s' does not work with arrays.\n", t->linenum,
                                               t->attr.name);
                                        number_of_errors++;
                                    }
                                }

                                if ((t->child[0]->isArray != t->child[1]->isArray) && (types_map[t->attr.name]["WithArrays"].front()=="true")){
                                    printf("ERROR(%d): ‘%s‘ requires that either both or neither operands be arrays.\n",
                                           t->linenum,
                                           t->attr.name
                                    );
                                    number_of_errors++;
                                }

                            }
                        }

                        if (types_map[t->attr.name]["result"].size() == 1) {
                            int x = 0;
                            stringstream convert(types_map[t->attr.name]["ResultEnumIndex"].front());
                            convert >> x;
                            t->declType = DeclType(x);
                        }
                        // }
                    }
                    break;
                }
                case AssignK: {
                    if (DEBUG == true) printf("AssignK: %s\n", t->attr.name);
                    // if(strcmp(t->attr.name,"=")==0 || strcmp(t->attr.name, "+=")==0 || strcmp(t->attr.name, "-=")==0) {
                    recurse_already = true;
                    recurse_through_children(t, false);
                    t->declType = t->child[0]->declType;
//                    if (DEBUG == true) cout << "   AssignK After Recursion" << endl;
//                     if(DEBUG==true) printf("ExprK1: %s, line: %d, child[0]: %s, type: %s\n", t->attr.name, t->linenum, t->child[0]->attr.name, Types[t->child[0]->declType]);
//                     if(DEBUG==true) printf("ExprKA: %s, line: %d, t: %s, type: %s\n", t->attr.name, t->linenum, t->attr.name, Types[t->declType]);

//                                if(t->child[1]!=NULL)
//                                        semantics(t);

                    if (strcmp(t->attr.name, "+=") == 0 || strcmp(t->attr.name, "-=") == 0 ||
                        strcmp(t->attr.name, "*=") == 0 || strcmp(t->attr.name, "/=") == 0 ||
                        strcmp(t->attr.name, "++") == 0 || strcmp(t->attr.name, "--") == 0 ||
                        strcmp(t->attr.name, "=") == 0
                            )
                    {


                        if (strcmp(t->attr.name, "=") != 0) t->declType = Int;


                        if (t->child[0] != NULL && t->child[1] == NULL) {
                            if (types_map[t->attr.name]["Unary"].front() == "true" && t->child[1] == NULL
                                && Types[t->child[0]->declType] != types_map[t->attr.name]["result"].front()
                                && t->child[0]->declType != UndefinedType) {
                                if (DEBUG) cout << "   Checking Unary stuff: " << t->linenum << endl;
                                printf("ERROR(%d): Unary '%s' requires an operand of type %s but was given %s.\n",
                                       t->linenum, t->attr.name, types_map[t->attr.name]["result"].front().c_str(),
                                       Types[t->child[0]->declType]);
                                number_of_errors++;
                            }

                            if (t->child[0]->isArray == true) {

                                if (DEBUG)
                                    cout << "   Checking if op: " << t->attr.name << " works with arrays. line :"
                                         << t->linenum << endl;
                                if (types_map[t->attr.name]["WithArrays"].front() == "false") {
                                    printf("ERROR(%d): The operation '%s' does not work with arrays.\n", t->linenum,
                                           t->attr.name);
                                    number_of_errors++;
                                }
                            } else if (t->child[0]->isArray == false && strcmp(t->attr.name, "*") == 0 &&
                                       t->child[1] == NULL && t->child[0]->declType != UndefinedType) {
                                printf("ERROR(%d): The operation '%s' only works with arrays.\n", t->linenum,
                                       t->attr.name);
                                number_of_errors++;
                            }
                        }

                        // Not Unary
                        if (t->child[0] != NULL && t->child[1] != NULL) {
                            if(DEBUG) printf("   Start Semantic checking both children\n");
                            if (t->child[1] != NULL) {
                                // Line below seg faults
                                // if(DEBUG==false) printf("    Processing Ops: child[1]= %s line: %d isArray: %d\n", t->child[1]->attr.name, t->linenum, t->child[1]->isArray);
                                // cout << "here " << t->linenum << "att " << t->attr.name<< endl;

                                //cout << "line: " << t->linenum << " test: " << types_map[t->attr.name]["WithArrays"].front() << endl;

                                if (DEBUG) printf("   Checking lhs and rhs types...\n");
                                vector <string> allowed_left_ops = types_map[t->attr.name]["left"];
                                vector <string> allowed_right_ops = types_map[t->attr.name]["right"];

                                if (t->child[0]->declType != t->child[1]->declType &&
                                    t->child[1]->declType != UndefinedType && t->child[0]->declType != UndefinedType
                                    && (strcmp(t->attr.name, "=") == 0)) {
                                    if (t->child[1]->declType == Void && (strcmp(t->attr.name, "=") == 0)) {
                                        printf("ERROR(%d): '%s' requires operands of NONVOID but rhs is of %s.\n",
                                               t->linenum, t->attr.name, Types[t->child[1]->declType]);
                                        number_of_errors++;
                                    } else {
                                        printf("ERROR(%d): '%s' requires operands of the same type but lhs is %s and rhs is %s.\n",
                                               t->linenum, t->attr.name, Types[t->child[0]->declType],
                                               Types[t->child[1]->declType]);
                                        number_of_errors++;
                                    }

                                } else if (((allowed_left_ops.size() == 1 && allowed_right_ops.size() == 1))) {
                                    if (is_in_vector(allowed_left_ops, Types[t->child[0]->declType]) != true &&
                                        t->child[0]->declType != UndefinedType) {
                                        printf("ERROR(%d): '%s' requires operands of %s but lhs is of %s.\n",
                                               t->linenum, t->attr.name,
                                               types_map[t->attr.name]["left"].front().c_str(),
                                               Types[t->child[0]->declType]);
                                        number_of_errors++;
                                    }
                                    if (is_in_vector(allowed_right_ops, Types[t->child[1]->declType]) != true &&
                                        t->child[1]->declType != UndefinedType) {
                                        printf("ERROR(%d): '%s' requires operands of %s but rhs is of %s.\n",
                                               t->linenum, t->attr.name,
                                               types_map[t->attr.name]["right"].front().c_str(),
                                               Types[t->child[1]->declType]);
                                        number_of_errors++;
                                    }

                                    if (t->child[0]->declType != t->child[1]->declType &&
                                        is_in_vector(allowed_right_ops, Types[t->child[1]->declType]) == true &&
                                        is_in_vector(allowed_left_ops, Types[t->child[0]->declType]) == true) {
                                        printf("ERROR(%d): '%s' requires operands of the same type but lhs is %s and rhs is %s.\n",
                                               t->linenum, t->attr.name, Types[t->child[0]->declType],
                                               Types[t->child[1]->declType]);
                                        number_of_errors++;
                                    }

                                } else if (allowed_left_ops.size() == 2 && allowed_right_ops.size() == 2) {

                                    if (is_in_vector(allowed_left_ops, Types[t->child[0]->declType]) == false &&
                                        t->child[0]->declType != UndefinedType) {
                                        printf("ERROR(%d): '%s' requires operands of %s or %s but lhs is of %s.\n",
                                               t->linenum, t->attr.name, types_map[t->attr.name]["left"][1].c_str(),
                                               types_map[t->attr.name]["left"][0].c_str(),
                                               Types[t->child[0]->declType]);
                                        number_of_errors++;
                                    }
                                    if (is_in_vector(allowed_right_ops, Types[t->child[1]->declType]) == false &&
                                        t->child[1]->declType != UndefinedType) {
                                        printf("ERROR(%d): '%s' requires operands of %s or %s but rhs is of %s.\n",
                                               t->linenum, t->attr.name, types_map[t->attr.name]["right"][1].c_str(),
                                               types_map[t->attr.name]["left"][0].c_str(),
                                               Types[t->child[1]->declType]);
                                        number_of_errors++;
                                    }
                                    if (t->child[0]->declType != t->child[1]->declType &&
                                        is_in_vector(allowed_right_ops, Types[t->child[1]->declType]) == true &&
                                        is_in_vector(allowed_left_ops, Types[t->child[0]->declType]) == true) {
                                        printf("ERROR(%d): '%s' requires operands of the same type but lhs is %s and rhs is %s.\n",
                                               t->linenum, t->attr.name, Types[t->child[0]->declType],
                                               Types[t->child[1]->declType]);
                                        number_of_errors++;
                                    }
                                }
                                if (t->child[0]->isArray == true || t->child[1]->isArray == true) {
                                    if (DEBUG)
                                        cout << "   Checking if op: " << t->attr.name << " works with arrays. line :"
                                             << t->linenum << endl;
                                    if (types_map[t->attr.name]["WithArrays"].front() == "false") {
                                        printf("ERROR(%d): The operation '%s' does not work with arrays.\n", t->linenum,
                                               t->attr.name);
                                        number_of_errors++;
                                    }

                                }
                                if ((t->child[0]->isArray != t->child[1]->isArray) && (types_map[t->attr.name]["WithArrays"].front()=="true")){
                                    printf("ERROR(%d): ‘%s‘ requires that either both or neither operands be arrays.\n",
                                           t->linenum,
                                           t->attr.name
                                    );
                                    number_of_errors++;
                                }
                                if(DEBUG) printf("   Done Semantic checking both children\n");
                            }
                        }


                    }
                    break;
                }
                case CallK: {
                    if (DEBUG == true) cout << "CallK" << endl;
//                                printf("Call: %s ", t->attr.name);

                    if (DEBUG == true) { printf("   Expression Statement: Function Call\n"); }

                    TreeNode *node = static_cast<TreeNode *>(semanticsSymbolTable.lookup((char *) t->attr.name));
                    if(node==NULL){
                        printf("ERROR(%d): Function '%s' is not defined.\n", t->linenum, t->attr.name);
                        number_of_errors++;
                    }
                    recurse_already = true;
                    recurse_through_children(t, false);

                    if (node == NULL) {
//                        printf("ERROR(%d): Function '%s' is not defined.\n", t->linenum, t->attr.name);
//                        number_of_errors++;
                        t->declType = UndefinedType;
                    } else {
                        // Assign Type to ID Node
                        t->declType = node->declType;
                        if (node->nodekind == DeclK) {
                            if (node->kind.decl == VarK) {
                                printf("ERROR(%d): '%s' is a simple variable and cannot be called.\n", t->linenum,
                                       t->attr.name);
                                number_of_errors++;
                            }
                        }
                        // Compare Params Types
                        // t is the call, node is the function decl node
                        if(t->child[0]!=NULL && node->child[0]!=NULL){
                            TreeNode* temp_t = t;
                            TreeNode* temp_node = node;
                            int sib_num=0;
                            while(temp_t->child[0]!=NULL &&  sib_num < 1){
//                                temp_t = t->child[0]->sibling;
//                                if(temp_node->child[0]->sibling!=NULL)
//                                    temp_node->child[0] = temp_node->child[0]->sibling;
                                sib_num++;

                                if((temp_t->child[0]->nodekind == ExprK && (temp_t->child[0]->kind.expr == IdK ||
                                        temp_t->child[0]->kind.expr==CallK)) ||
                                        (temp_t->child[0]->nodekind == DeclK && temp_t->child[0]->kind.decl == VarK))
                                {
                                    TreeNode *node1 = static_cast<TreeNode *>(semanticsSymbolTable.lookup(
                                            (char *) temp_t->child[0]->attr.name));
//                                cout << node->attr.name << node1->attr.name << Types[node1->declType] << Types[node->declType] << endl;
                                    if (node1->declType != temp_node->child[0]->declType) {
                                        printf("ERROR(%d): Expecting %s in parameter 1 of call to '%s' defined on line %d but got %s.\n",
                                               temp_t->linenum, Types[temp_node->child[0]->declType], temp_t->attr.name, temp_node->linenum,
                                               Types[node1->declType]
                                        );
                                    }
                                    if (node1->isArray==true && temp_node->child[0]->isArray==false){
                                        printf("ERROR(%d): Not expecting array in parameter 1 of call to '%s' defined on line %d.\n",
                                               temp_t->linenum,
                                               temp_node->attr.name,
                                               temp_node->linenum);
                                    }
                                } else if( temp_t->child[0]->declType!=temp_node->child[0]->declType){
                                    printf("ERROR(%d): Expecting %s in parameter 1 of call to '%s' defined on line %d but got %s.\n",
                                           temp_t->linenum, Types[temp_node->child[0]->declType], temp_t->attr.name, temp_node->linenum,
                                           Types[temp_t->child[0]->declType]
                                    );
                                }
                                if(get_number_of_siblings(temp_t->child[0]) > get_number_of_siblings(temp_node->child[0])){
                                    printf("ERROR(%d): Too many parameters passed for function '%s' defined on line %d.\n",
                                           temp_t->linenum, temp_node->attr.name, temp_node->linenum
                                    );
                                };
                                if(get_number_of_siblings(t->child[0]) < get_number_of_siblings(node->child[0])){
                                    printf("ERROR(%d): Too few parameters passed for function '%s' defined on line %d.\n",
                                           temp_t->linenum, temp_node->attr.name, temp_node->linenum
                                    );
                                };
                                if(temp_node->child[0]->isArray==true && temp_t->child[0]->isArray==false){
                                    printf("ERROR(%d): Expecting array in parameter 1 of call to '%s' defined on line %d.\n",
                                           temp_t->linenum,
                                           temp_node->attr.name,
                                           temp_node->linenum
                                    );
                                }
                            }
                            if(node->child[0]!=NULL && t->child[0]==NULL){
                                printf("ERROR(%d): Too few parameters passed for function '%s' defined on line %d.\n",
                                       t->linenum, node->attr.name, node->linenum
                                );
                            };
                            }

                    }
                    break;
                }
            }
        } else if (t->nodekind == DeclK) {
            if (DEBUG == true) cout << "   DeclK" << endl;
            // if(DEBUG==true) { printf("DeclK %s, line: %d\n", t->attr.name, t->linenum); }

            bool insertion = semanticsSymbolTable.insert((char *) t->attr.name, t);
            if (insertion == 0) { // If insertion failed == already exists in table
                TreeNode *node = static_cast<TreeNode *>(semanticsSymbolTable.lookup((char *) t->attr.name));
                printf("ERROR(%d): Symbol '%s' is already defined at line %d.\n", t->linenum, t->attr.name,
                       node->linenum);
                number_of_errors++;
            }
            if (t->kind.decl == FuncK) {
                if(DEBUG) printf("   FuncK1\n");
                hasReturned = false;
                currentFunction = t;
                if (SCOPE_DEBUG == true) cout << "Function: Entering Scope: Line " << t->linenum << endl;
                // t->declType=node->declType;
                semanticsSymbolTable.enter(t->attr.name);
                recurse_through_children(t, true);
                recurse_already = true;
            }

            if (t->kind.decl == FuncK) {
                if(hasReturned==false && (currentFunction->attr.name!="input"  && currentFunction->attr.name!="output"  &&
                                          currentFunction->attr.name!="inputb" && currentFunction->attr.name!="outputb" &&
                                          currentFunction->attr.name!="inputc" && currentFunction->attr.name!="outputc" &&
                                          currentFunction->attr.name!="outnl"
                ) && currentFunction->declType!=Void){
                    printf("WARNING(%d): Expecting to return %s but function '%s' has no return statement.\n",
                           t->linenum,
                           Types[currentFunction->declType],
                           currentFunction->attr.name
                    );
                }
                semanticsSymbolTable.leave();
                if (SCOPE_DEBUG == true) cout << "Function: Leaving Scope: Line " << t->linenum << endl;
            }
            switch (t->kind.decl) {
                case FuncK: {
                    if(DEBUG) printf("   FuncK2\n");

                    break;
                }
                case VarK:
//                    if (t->isArray == true) {
//
//
//                    } else {
//
//                        // printf("Var %s of ", t->attr.name);
//                    }
                    break;
                case ParamK:

                    break;
                case RecordK:
                    // printf("Record %s  ", t->attr.name);
                default:
                    break;
            }
            switch (t->declType) {
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
//                    if (t->isRecord != true) {
//                        // printf("type record ");
//                    }
                    break;
                default:
                    break;
            }
        } else {
            printf("Failed printing tree nodekind index: %u\n", t->nodekind);

        }
        if (recurse_already == false) recurse_through_children(t, true);
        //recurse_through_children(t, false);
    }

}
