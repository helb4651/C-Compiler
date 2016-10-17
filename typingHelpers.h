#ifndef COMPILER_TYPINGHELPERS_H
#define COMPILER_TYPINGHELPERS_H
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
using namespace std;


map<string, map<string, vector<string> > > &getTypesDataStructure();

extern map<string, map<string, vector<string> > > types_map;


#endif //COMPILER_TYPINGHELPERS_H
