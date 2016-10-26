//
// Created by Cody Helbling on 10/15/16.
//

#include "typingHelpers.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
using namespace std;


map<string, map<string, vector<string> > > types_map;
int number_of_errors=0;

map<string, map<string, vector<string> > > & getTypesDataStructure(){
        string line;
        string bar_cell;
        string comma_cell;
        string Operator;

        vector<string> left_Operands;
        vector<string> right_Operands;
        vector<string> result_Operands;
        vector<string> left_right_type_match;
        vector<string> works_with_arrays;
        vector<string> type_is_left_node;
        vector<string> is_unary;
        map<string, vector<string> > Operator_Map;




        ifstream myfile ("types.csv");
        if (myfile)
        {
                while (getline( myfile, line) )
                {
                        // cout << line << endl;
                        istringstream istr1(line);
                        int x=0;

                        // Operator
                        getline(istr1, bar_cell, '|');
                        istringstream istr2(bar_cell);
                        // cout << "Operator: " << bar_cell << endl;
                        while (istr2.peek() == ' ') // skip spaces
                                istr2.get();
                        while (getline(istr2, comma_cell, ',')) {
                                if(comma_cell != " ") {
                                        // cout << "Operator: " << comma_cell << endl;
                                        Operator = comma_cell;
                                }
                        };
                        while (istr2.peek() == ' ') // skip spaces
                                istr2.get();

                        // Left
                        getline(istr1, bar_cell, '|');
                        istringstream istr3(bar_cell);
//            cout << "Left: " << bar_cell << endl;
                        while (istr3.peek() == ' ') // skip spaces
                                istr3.get();
                        while (getline(istr3, comma_cell, ',')) {
                                if(comma_cell != " ") {
//                    cout << "left type: " << comma_cell << endl;
                                        left_Operands.push_back(comma_cell);
                                }
                        };
                        while (istr3.peek() == ' ') // skip spaces
                                istr3.get();

                        // Right
                        getline(istr1, bar_cell, '|');
                        istringstream istr4(bar_cell);
                        // cout << "Right: " << bar_cell << endl;
                        while (istr4.peek() == ' ') // skip spaces
                                istr4.get();
                        while (getline(istr4, comma_cell, ',')) {
                                if(comma_cell != " ") {
//                    cout << "right type: " << comma_cell << endl;
                                        right_Operands.push_back(comma_cell);
                                }
                        };
                        while (istr4.peek() == ' ') // skip spaces
                                istr4.get();

                        // Result
                        getline(istr1, bar_cell, '|');
                        istringstream istr5(bar_cell);
                        // cout << "Result: " << bar_cell << endl;
                        while (istr5.peek() == ' ') // skip spaces
                                istr5.get();
                        while (getline(istr5, comma_cell, ',')) {
                                if(comma_cell != " ") {
//                    cout << "result type: " << comma_cell << endl;
                                        result_Operands.push_back(comma_cell);
                                }
                        };
                        while (istr5.peek() == ' ') // skip spaces
                                istr5.get();

                        getline(istr1, bar_cell, '|');
                        istringstream istr6(bar_cell);
                        // cout << "Result: " << bar_cell << endl;
                        while (istr6.peek() == ' ')         // skip spaces
                                istr6.get();
                        while (getline(istr6, comma_cell, ',')) {
                                if(comma_cell != " ") {
                                        //                    cout << "result type: " << comma_cell << endl;
                                        left_right_type_match.push_back(comma_cell);
                                }
                        };
                        while (istr6.peek() == ' ')         // skip spaces
                                istr6.get();


                        getline(istr1, bar_cell, '|');
                        istringstream istr7(bar_cell);
                        // cout << "Result: " << bar_cell << endl;
                        while (istr7.peek() == ' ')                 // skip spaces
                                istr7.get();
                        while (getline(istr7, comma_cell, ',')) {
                                if(comma_cell != " ") {
                                        //                    cout << "result type: " << comma_cell << endl;
                                        works_with_arrays.push_back(comma_cell);
                                }
                        };
                        while (istr7.peek() == ' ')                 // skip spaces
                                istr7.get();

                        getline(istr1, bar_cell, '|');
                        istringstream istr8(bar_cell);
                        // cout << "Result: " << bar_cell << endl;
                        while (istr8.peek() == ' ')                         // skip spaces
                                istr8.get();
                        while (getline(istr8, comma_cell, ',')) {
                                if(comma_cell != " ") {
                                        //                    cout << "result type: " << comma_cell << endl;
                                        type_is_left_node.push_back(comma_cell);
                                }
                        };
                        while (istr8.peek() == ' ')                         // skip spaces
                                istr8.get();

                        getline(istr1, bar_cell, '|');
                        istringstream istr9(bar_cell);
                        // cout << "Result: " << bar_cell << endl;
                        while (istr9.peek() == ' ')                                 // skip spaces
                                istr9.get();
                        while (getline(istr9, comma_cell, ',')) {
                                if(comma_cell != " ") {
                                        //                    cout << "result type: " << comma_cell << endl;
                                        is_unary.push_back(comma_cell);
                                }
                        };
                        while (istr9.peek() == ' ')                                 // skip spaces
                                istr9.get();

                        // Add operator operand types to Operator_Map
                        Operator_Map["left"]=left_Operands;
                        Operator_Map["right"]=right_Operands;
                        Operator_Map["result"]=result_Operands;
                        Operator_Map["LRMatch"]=left_right_type_match;
                        Operator_Map["WithArrays"]=works_with_arrays;
                        Operator_Map["ResultEnumIndex"]=type_is_left_node;
                        Operator_Map["Unary"]=is_unary;

                        // Add Operator Map to types operator map
                        types_map[Operator]=Operator_Map;

                        // Empty the Vectors and Maps for next iteration
                        left_Operands.clear();
                        right_Operands.clear();
                        result_Operands.clear();
                        left_right_type_match.clear();
                        works_with_arrays.clear();
                        type_is_left_node.clear();
                        is_unary.clear();
                        Operator_Map.clear();

                }
                myfile.close();
        }
        else cout << "Unable to open file";

        map<string, map<string, vector<string> > >& types = types_map;
        // cout << "ZZZZZZZ: " << types_map["+="]["left"].front() << endl;
        types = types_map;
        // cout << "XXXXXXX: " << types["not"]["WithArrays"].front() << endl;

        return types;
}
