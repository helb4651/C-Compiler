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
static bool SCOPE_DEBUG=false;


SymbolTable semanticsSymbolTable;


char *Types[] = {"type void", "type int", "type bool", "type char", "type string", "type record", "undefined type"};

void recurse_through_children(TreeNode* node, bool Function_Recurse){

    for(int i = 0; i < MAXCHILDREN; i++) {
        chiIndex = i;
        scopeAndType(node->child[i], 0, Function_Recurse);
        chiIndex = 0;
    }
}


bool is_in_vector(vector<string> vec, string str){
    // cout << str << endl;
    // cout << vec.front() << endl;
    if ( find(vec.begin(), vec.end(), str) != vec.end() ) {
        // printf("Exists\n");
        return true;
    }
    else{
        // printf("Doesn't Exist\n");
        // cout << "1: " << str << "2: " << vec.front() << endl;
        return false;
    }
}

string node_type(TreeNode* node){
    if(DEBUG==true) cout << "   node_type" << endl;
    if(node->nodekind == ExprK) {
        // cout << "node_type: ExprK" << endl;
        if(node->kind.expr == ConstK) {
            // cout << "node_type1: " << Types[node->declType] << endl;
            return Types[node->declType];
        }
        else if(node->kind.expr == OpK ) {
            if(DEBUG==true) cout << "       Recursing in node_type." << endl;
            // scopeAndType(node, 0, false);
            recurse_through_children(node, false);
            return "node_type_recursing";
        }
        else if( node->kind.expr == IdK ) {
            if(DEBUG==true) cout << "   node name: " << node->attr.name << endl;
            TreeNode* def_node = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)node->attr.name));


            if(def_node==NULL) {
                printf("ERROR(%d): Symbol '%s' is not defined.\n", node->linenum, node->attr.name);
                number_of_errors++;
                return "not_defined";
            } else {
                // Assign Type to ID Node
                node->declType = def_node->declType;
                return "something";
            }

            if(DEBUG==true) cout << "   node_type2: " << Types[def_node->declType] << endl;

            return Types[def_node->declType];

        }
        else{
            recurse_through_children(node, false);
            return "node_type_recursing";

        }
    } else{
        TreeNode* def_node = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)node->attr.name));
        if(def_node==NULL) {
            printf("ERROR(%d): Symbol '%s' is not defined.\n", node->linenum, node->attr.name);
            number_of_errors++;
            return "not_defined";
        } else {
            // Assign Type to ID Node
            node->declType = def_node->declType;
        }                // cout << "node_type2: " << Types[def_node->declType] << endl;

        return Types[def_node->declType];
    }

    // cout << "node_type function failed in semantic.cpp." << endl;
    // return "not_defined";
}

bool is_array_node(TreeNode* node){
    if(node->nodekind == ExprK && node->kind.expr == ConstK) {
        // cout << "node_type1: " << Types[node->declType] << endl;
        return false;
    }
    else if(node->nodekind == ExprK) {
        TreeNode* def_node = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)node->attr.name));
        node->declType = def_node->declType;
        // cout << "node_type2: " << Types[def_node->declType] << endl;
        return Types[def_node->isArray];
    }
    else{
        cout << "is_array_node function failed in semantic.cpp." << endl;
        return false;
    }
}


void process_node(TreeNode* t){

    // If Node Has a Sibling..
    if(t->sibling!=NULL) {
        if(DEBUG==true) cout << "   Recursing Through Sibling Node." << endl;
        recurse_through_children(t->sibling, false);
    }

    string NodeName(t->attr.name);
    if(DEBUG==false) cout << "   NodeName: " << NodeName << endl;
    int LineNumber = t->linenum;
    TreeNode* LeftNode = t->child[0];
    string left_node_type = node_type(t->child[0]);
    vector<string> left_types_vec = types_map[NodeName]["left"];


    // cout << "here1" << endl;

    // If One Child Node
    if(t->child[0]!=NULL && t->child[1]==NULL && left_node_type!="not_defined" && left_node_type!="node_type_recursing") {
        if(DEBUG==true) cout << "   Processing Single Child Node" << endl;

        // TODO: Add some logic to not just assume the first type in the vector is the correct type.
        // Is Unary Operand Type Incorrect?
        if(left_node_type != left_types_vec.front()) {
            printf("ERROR(%d): Unary '%s' requires an operand of type %s but was given %s.\n", LineNumber, NodeName.c_str(), left_types_vec.front().c_str(), left_node_type.c_str() );
            number_of_errors++;
        }
        // cout << "here1.5" << endl;
    }

    // cout << "here2" << endl;

    // If Two Child Node
    if(t->child[0]!=NULL && t->child[1]!=NULL) {
        if(DEBUG==true) cout << "   Processing Two Child Node" << endl;

        TreeNode* RightNode = t->child[1];
        string right_node_type = node_type(t->child[1]);
        vector<string> right_types_vec = types_map[NodeName]["right"];

        if(right_node_type == left_node_type ) {
            TreeNode* n = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)t->child[0]->attr.name));
            if(n == NULL) {
                cout << "Null for " << t->child[0]->attr.name << "." << endl;
                t->declType = UndefinedType;
            } else {
                t->declType = n->declType;
            }


        }

        if(right_node_type!="not_defined" && left_node_type!="not_defined" && right_node_type!="node_type_recursing" && left_node_type!="node_type_recursing") {
            // Do operands need to be the same type?
            if(types_map[NodeName]["LRMatch"].front()=="true") {
                if(DEBUG==true) cout << "   Checking Left and Right Node Types Match: " << NodeName << endl;

                // map<string, string> info = check_operands_types_same(t);
                if(left_node_type != right_node_type) {
                    printf("ERROR(%d): '%s' requires operands of the same type but lhs is %s and rhs is %s.\n", LineNumber, NodeName.c_str(), left_node_type.c_str(), right_node_type.c_str());
                    number_of_errors++;
                }
                return;
                // if(is_array_node(t->child[0])==true || is_array_node(t->child[1])==true) {
                //         printf("ERROR(%d): The operation '%s' does not work with arrays.\n", t->linenum, t->attr.name);
                // }
            }

            // TODO: Note that it is assumed if these get executed there is only one correct type? This may need more logic....
            // Is the left operand of the correct type?
            if(is_in_vector(left_types_vec, left_node_type)==false) {
                if(DEBUG==true) cout << "    Left Node Incorrect Type: " << NodeName << endl;
                printf("ERROR(%d): '%s' requires operands of %s but lhs is of %s.\n", LineNumber, NodeName.c_str(), left_types_vec.front().c_str(), left_node_type.c_str());
                number_of_errors++;
            }

            // TODO: Note that it is assumed if these get executed there is only one correct type? This may need more logic....
            // Is the right operand of the correct type?
            if(is_in_vector(right_types_vec, right_node_type)==false) {
                if(DEBUG==true) cout << "    Right Node Incorrect Type: " << NodeName << endl;
                printf("ERROR(%d): '%s' requires operands of %s but rhs is of %s.\n", LineNumber, NodeName.c_str(), right_types_vec.front().c_str(), right_node_type.c_str());
                number_of_errors++;
            }
                // Does the operator work with arrays?
            else if((is_array_node(t->child[0])==true || is_array_node(t->child[1])==true) && types_map[NodeName]["WithArrays"].front()=="false") {
                printf("ERROR(%d): The operation '%s' does not work with arrays.\n", t->linenum, t->attr.name);
                number_of_errors++;
            }


        }


    }
}


void scopeAndType(TreeNode *tree, int numOfSibs,  bool FuncKRecurse) {

    bool recursivePrint = false;
    bool recurse_already = false;
    if(numOfSibs == -1) {
        numOfSibs++;
        recursivePrint = true;
    } else {
        spaces += 4;
    }
    for(TreeNode *t = tree; t != NULL; t = t->sibling) {
        recurse_already=true;

        if(DEBUG==true) printf("\n---- line: %d ----\n", t->linenum );
        // if(t->nodekind == ExprK && t->kind.expr==IdK) {
        //         // if(DEBUG==true) { printf("Expression Statement: ID\n"); }
        //         // TreeNode* node = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)t->attr.name));
        //         // if(node==NULL) { printf("ERROR(%d): Symbol '%s' is not defined.\n", t->linenum, t->attr.name); }
        //         // recurse_through_children(t);
        // }

        if(t->nodekind == StmtK) {
            if(DEBUG==true) cout << "   StmtK" << endl;
            switch(t->kind.stmt) {

                case IfK:
                    // printf("If ");
                    break;
                case WhileK:
                    // printf("While ");
                    break;
                case CompK:
                {
                    // printf("Compound ");
                    if(SCOPE_DEBUG==true) { printf("Compound Statement: Adding Scope: Line %d\n", t->linenum); }
                    if(FuncKRecurse==false) {semanticsSymbolTable.enter("Compound"); }
                    recurse_through_children(t, false);
                    recurse_already  = true;
                    if(FuncKRecurse==false) {
                        semanticsSymbolTable.leave();
                        if(SCOPE_DEBUG==true) { printf("Coumpound Statement: Leaving Scope: Line %d\n", t->linenum); }
                    }
                    break;
                }
                case ReturnK:
                    if(DEBUG==true) cout << "return" << endl;
                    // process_node(t);
                    if(t->isArray) {
                        printf("ERROR(%d): Cannot return an array.\n", t->linenum);
                    }
                    // printf("Return ");
                    break;
                case BreakK:
                    // printf("Break ");
                    break;
            }
        }
        else if(t->nodekind == ExprK) {
            if(DEBUG==true) cout << "   ExprK-";
            switch(t->kind.expr) {
                case ConstK:
                {
                    if(DEBUG==true) cout << "ConstK-";
                    switch(t->declType) {
                        case Int:
                            if(DEBUG==true) cout << "Int" << endl;
                            // printf("%i ", t->attr.value);
                            break;
                        case Bool:
                            if(DEBUG==true) cout << "Bool" << endl;
                            if(t->attr.value == 0) {
                                // printf("false ");
                            } else {
                                // printf("true ");
                            }
                            break;
                        case Char:
                            if(DEBUG==true) cout << "Char" << endl;
                            // printf("'%c' ", t->attr.cvalue);
                            break;
                        case String:
                            if(DEBUG==true) cout << "String" << endl;
                            // printf("\"%s\" ", t->attr.string);
                            break;
                        default:
                            if(DEBUG==true) cout << "!Default!" << endl;
                            break;
                    }
                    break;
                }
                case IdK:
                {
                    if(DEBUG==true) cout << "IdK" << endl;
                    TreeNode* nodeIdK = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)t->attr.name));
                    if(nodeIdK==NULL) {
                        printf("ERROR(%d): Symbol '%s' is not defined.\n", t->linenum, t->attr.name);
                        t->declType = UndefinedType;
                        number_of_errors++;
                    }           else {
                        // Assign Type to ID Node
                        t->declType = nodeIdK->declType;
                        // printf("Id: %s assigning type: %s\n", t->attr.name, Types[nodeIdK->declType]);

                    }
                    recurse_through_children(t, false);
                    recurse_already  = true;
                    break;
                }
                case OpK:
                {
                    if(DEBUG==true) cout << "OpK-";
                    // printf("Op: %s ", t->attr.name);
                    // if(DEBUG==true) printf("Op: %s \n", t->attr.name);
                    if(strcmp(t->attr.name, ">")==0 || strcmp(t->attr.name, "<")==0) {
                        // printf("Op: %s \n", t->attr.name);
                        // process_node(t);
                        // map<string, string> info = check_operands_types_same(t);
                        // if(info["identical_types"] == "false") {
                        //         printf("ERROR(%s): '%s' requires operands of the same type but lhs is %s and rhs is %s.\n", info["linenum"].c_str(), info["name"].c_str(), info["left_type"].c_str(), info["right_type"].c_str());
                        // }
                        // else if(is_array_node(t->child[0])==true || is_array_node(t->child[1])==true) {
                        //         printf("ERROR(%d): The operation '%s' does not work with arrays.\n", t->linenum, t->attr.name);
                        // }
                    }
                    else if(strcmp(t->attr.name, "+")==0 || strcmp(t->attr.name, "-")==0 || strcmp(t->attr.name, "*")==0) {
                        if(DEBUG==true) cout << " +, -, *" << endl;

                        process_node(t);
                        // cout << "made it!" << endl;
                        // string left_node_type = node_type(t->child[0]);
                        // // cout << "left_node_type: " << left_node_type << endl;
                        // string right_node_type = "default_node_type";
                        // if(t->child[1]) {
                        //         // cout << "here" << endl;
                        //         right_node_type = node_type(t->child[1]);
                        //         // cout << "right_node_type: " << right_node_type << endl;
                        //         int line = t->linenum;
                        //         // cout << "line: " << line << endl;
                        //         char* name = t->attr.name;
                        //         // cout << "name: " << name << endl;
                        //         string req_right_op = types_map[t->attr.name]["right"].front();
                        //         // cout << "req_right_op: " << req_right_op << endl;
                        //         string req_left_op = types_map[t->attr.name]["left"].front();
                        //         // cout << "req_right_op: " << req_left_op << endl;
                        //         if(is_in_vector(types_map[t->attr.name]["left"], left_node_type)==false && left_node_type!="not_defined") {
                        //                 printf("ERROR(%d): '%s' requires operands of %s but lhs is of %s.\n", line, name, req_left_op.c_str(), left_node_type.c_str());
                        //         }
                        //         if(is_in_vector(types_map[t->attr.name]["right"], right_node_type)==false && right_node_type!="not_defined") {
                        //                 printf("ERROR(%d): '%s' requires operands of %s but lhs is of %s.\n", line, name, req_right_op.c_str(), right_node_type.c_str());
                        //         }
                        // }
                    }
                    else if(strcmp(t->attr.name, "==")==0) {
                        // process_node(t);
                        // if(DEBUG==true) cout << "==" << endl;
                        // map<string, string> info = check_operands_types_same(t);
                        // if(info["identical_types"] == "false") {
                        //         printf("ERROR(%s): '%s' requires operands of the same type but lhs is %s and rhs is %s.\n", info["linenum"].c_str(), info["name"].c_str(), info["left_type"].c_str(), info["right_type"].c_str());
                        // }
                    }
                    else if(strcmp(t->attr.name, "not")==0) {
                        if(DEBUG==true) cout << "NOT" << endl;
                        // process_node(t);
                        // cout << endl << endl;
                        //
                        //
                        //
                        // if(t->child[0]!=NULL) {
                        //         // cout << "yay2" << endl;
                        //         string left_type = node_type(t->child[0]);
                        //         if(left_type != types_map[t->attr.name]["left"].front()) {
                        //                 printf("ERROR(%d): Unary '%s' requires an operand of type %s but was given %s.\n", t->linenum, t->attr.name, types_map[t->attr.name]["left"].front().c_str(),left_type.c_str() );
                        //         }
                        // }
                    }
                    else if(strcmp(t->attr.name, "and")==0) {
                        if(DEBUG==true) cout << "AND" << endl;
                        //cout << endl; << endl
                        // process_node(t);
                        string left_node_type = node_type(t->child[0]);
                        // cout << "left: " << left_node_type << endl;
                        string right_node_type = node_type(t->child[1]);
                        // cout << "right: " << right_node_type << endl;
                        if(left_node_type != "type bool" && left_node_type != "not_defined") {
                            printf("ERROR(%d): '%s' requires operands of %s but lhs is of %s.\n", t->linenum, t->attr.name, types_map["and"]["left"].front().c_str(), left_node_type.c_str());
                            number_of_errors++;
                        }
                        if(right_node_type != "type bool" && right_node_type != "not_defined") {
                            printf("ERROR(%d): '%s' requires operands of %s but rhs is of %s.\n", t->linenum, t->attr.name, types_map["and"]["right"].front().c_str(), right_node_type.c_str());
                            number_of_errors++;
                        }

                    }
                    else if(strcmp(t->attr.name, "or")==0) {
                        if(DEBUG==true) cout << "OR" << endl;
                        process_node(t);
                    }


                    break;
                }
                case AssignK:
                {
                    if(DEBUG==true) cout << "AssignK";
                    if(DEBUG==true) printf("Assign: %s ", t->attr.name);
                    if(strcmp(t->attr.name,"=")==0) {
                        if(DEBUG==true) cout << "=" << endl;
                        // printf("ExprK2: %s, line: %d\n", t->attr.name, t->linenum);
                        // TreeNode* nodex = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)t->child[1]->attr.name));
                        // printf("child[1]: %s, line: %d\n", nodex->attr.name, t->linenum);
                        process_node(t);
                        // bool insertion = semanticsSymbolTable.insert((char *)t->attr.name, t);
                        // printf("insertion %u\n", insertion);

                        // TreeNode* node = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)t->child[1]->attr.name));

                        // if(node->kind.decl==FuncK) {
                        //         printf("ERROR(%d): Cannot use function '%s' as a variable.\n", t->linenum, node->attr.name);
                        // }

                        // if(node!=NULL) {t->declType = node->declType; }
                        // if(node==NULL) {
                        //         printf("ERROR(%d): Symbol '%s' is not defined.\n", t->linenum, t->attr.name);
                        //         t->declType = UndefinedType;
                        // }

                    }
                    if(strcmp(t->attr.name, "=")==0 || strcmp(t->attr.name, ">")==0) {
                        // TreeNode* node_right = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)t->child[1]->attr.name));
                        // printf("nodey->declType: %s\n", Types[node_right->declType]);
                        // TreeNode* node_left = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)t->child[0]->attr.name));
                        // printf("nodey->declType: %s\n", Types[node_left->declType]);


                        // process_node(t);
//                                        string node_right = node_type(t->child[1]);
//                                        string node_left = node_type(t->child[0]);
//                                        if(node_left != node_right) {
//                                                printf("ERROR(%d): '%s' requires operands of the same type but lhs is %s and rhs is %s.\n", t->linenum, t->attr.name, node_left.c_str(), node_right.c_str());
//                                        }
                    }
                    else if(strcmp(t->attr.name, "+=")==0 || strcmp(t->attr.name, "-=")==0) {
                        // TreeNode* node_right = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)t->child[1]->attr.name));
                        // // printf("nodey->declType: %s\n", Types[node_right->declType]);
                        // TreeNode* node_left = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)t->child[0]->attr.name));
                        // // printf("nodey->declType: %s\n", Types[node_left->declType]);
                        //
                        // if(is_in_vector(types_map[t->attr.name]["left"], Types[node_left->declType])==false) {
                        //         printf("ERROR(%d): '%s' requires operands of %s but lhs is of %s.\n", t->linenum, t->attr.name, types_map[t->attr.name]["left"].front().c_str(), Types[node_left->declType]);
                        // }
                        // if(is_in_vector( types_map[t->attr.name]["right"], Types[node_right->declType] )==false) {
                        //         printf("ERROR(%d): '%s' requires operands of %s but rhs is of %s.\n", t->linenum, t->attr.name, types_map[t->attr.name]["right"].front().c_str(), Types[node_right->declType]);
                        // }
                        // process_node(t);
                    }
                    break;
                }
                case CallK:
                {
                    printf("cow? %d\n", t->linenum);
                    if(DEBUG==true) cout << "CallK" << endl;
                    printf("Call: %s ", t->attr.name);
                    if(DEBUG==true) { printf("Expression Statement: Function Call\n"); }
                    TreeNode* node = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)t->attr.name));
                    if(node==NULL) { printf("ERROR(%d): Symbol '%s' is not defined.\n", t->linenum, t->attr.name);
                        number_of_errors++;
                        t->declType = UndefinedType; }
                    else {
                        // Assign Type to ID Node
                        t->declType = node->declType;
                    }
                    recurse_through_children(t, false);
                    recurse_already = false;


                    break;
                }
            }
        } else if(t->nodekind == DeclK) {
            if(DEBUG==true) cout << "   DeclK" << endl;
            // if(DEBUG==true) { printf("DeclK %s, line: %d\n", t->attr.name, t->linenum); }

            bool insertion = semanticsSymbolTable.insert((char *)t->attr.name, t);
            if(t->kind.decl==FuncK) {
                if(SCOPE_DEBUG==true) cout << "Function: Entering Scope: Line " << t->linenum << endl;
                semanticsSymbolTable.enter(t->attr.name);
            }

            if(insertion==0) { // If insertion failed == already exists in table
                TreeNode* node = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)t->attr.name));
                printf("ERROR(%d): Symbol '%s' is already defined at line %d.\n", t->linenum, t->attr.name, node->linenum);
                number_of_errors++;
            }
            recurse_through_children(t, true);
            recurse_already  = true;
            if(t->kind.decl==FuncK) {
                semanticsSymbolTable.leave();
                if(SCOPE_DEBUG==true) cout << "Function: Leaving Scope: Line " << t->linenum << endl;
            }
            switch(t->kind.decl) {
                case FuncK:
                    // printf("Func %s returns ", t->attr.name);

                    break;
                case VarK:
                    if(t->isArray == true) {
                        TreeNode* def_node = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)t->attr.name));
                        if(def_node==NULL) {
                            printf("ERROR(%d): Symbol '%s' is not defined.\n", t->linenum, t->attr.name);
                            number_of_errors++;
                            t->declType=UndefinedType;
                        }
                        else {
                            t->declType=def_node->declType;
                        }

                    } else {

                        // printf("Var %s of ", t->attr.name);
                        TreeNode* def_node = static_cast<TreeNode*>(semanticsSymbolTable.lookup((char *)t->attr.name));
                        if(def_node==NULL) {
                            printf("ERROR(%d): Symbol '%s' is not defined.\n", t->linenum, t->attr.name);
                            number_of_errors++;
                            t->declType=UndefinedType;
                        }
                        else {
                            t->declType=def_node->declType;
                        }
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
        }
        else {
            printf("Failed printing tree nodekind index: %u\n", t->nodekind);


        }
        // if (recurse  == true) recurse_through_children(t, false);
        if(recurse_already==false) recurse_through_children(t, false);
    }
}