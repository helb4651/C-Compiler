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


static map<string, map<string, vector<string> > > types_map;

map<string, map<string, vector<string> > > & getTypesDataStructure(){
        string line;
        string bar_cell;
        string comma_cell;
        string Operator;

        vector<string> left_Operands;
        vector<string> right_Operands;
        vector<string> result_Operands;
        map<string, vector<string> > Operator_Map;




        ifstream myfile ("types.csv");
        if (myfile)
        {
                while (getline( myfile, line) )
                {
                        //cout << line << endl;
                        istringstream istr1(line);
                        int x=0;

                        // Operator
                        getline(istr1, bar_cell, '|');
                        istringstream istr2(bar_cell);
//            cout << "Operator: " << bar_cell << endl;
                        while (getline(istr2, comma_cell, ',')) {
                                if(comma_cell != " ") {
                                        // cout << "Operator: " << comma_cell << endl;
                                        Operator = comma_cell;
                                }
                        };


                        // Left
                        getline(istr1, bar_cell, '|');
                        istringstream istr3(bar_cell);
//            cout << "Left: " << bar_cell << endl;
                        while (getline(istr3, comma_cell, ',')) {
                                if(comma_cell != " ") {
//                    cout << "left type: " << comma_cell << endl;
                                        left_Operands.push_back(comma_cell);
                                }
                        };


                        // Right
                        getline(istr1, bar_cell, '|');
                        istringstream istr4(bar_cell);
                        // cout << "Right: " << bar_cell << endl;
                        while (getline(istr4, comma_cell, ',')) {
                                if(comma_cell != " ") {
//                    cout << "right type: " << comma_cell << endl;
                                        right_Operands.push_back(comma_cell);
                                }
                        };


                        // Result
                        getline(istr1, bar_cell, '|');
                        istringstream istr5(bar_cell);
                        // cout << "Result: " << bar_cell << endl;
                        while (getline(istr5, comma_cell, ',')) {
                                if(comma_cell != " ") {
//                    cout << "result type: " << comma_cell << endl;
                                        result_Operands.push_back(comma_cell);
                                }
                        };

                        // Add operator operand types to Operator_Map
                        Operator_Map["left"]=left_Operands;
                        Operator_Map["right"]=right_Operands;
                        Operator_Map["result"]=result_Operands;

                        // Add Operator Map to types operator map
                        types_map[Operator]=Operator_Map;

                        // Empty the Vectors and Maps for next iteration
                        left_Operands.clear();
                        right_Operands.clear();
                        result_Operands.clear();
                        Operator_Map.clear();

                }
                myfile.close();
        }
        else cout << "Unable to open file";

        map<string, map<string, vector<string> > >& types = types_map;
        // cout << "ZZZZZZZ: " << types_map["+="]["left"].front() << endl;
        types = types_map;
        // cout << "XXXXXXX: " << types["+="]["left"].front() << endl;

        return types;
}
