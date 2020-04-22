#ifndef QUERY_ENGINE_H
#define QUERY_ENGINE_H

#include <iostream>
#include <string>
#include "cstring"
#include "dirent.h"
#include "porter2_stemmer.h"
#include "AVLTree.h"
#include "DocumentParser.h"
#include "QueryEngine.h"
using namespace std;

class QueryEngine{
private:
    string userSearch;
    AVLTree<Word> tree;
    DocumentParser d;
public:
    QueryEngine();
    QueryEngine(QueryEngine&);
    void prefixIndentifier(string&);
    void trimandstemSearchWord(char*);
    void getDirectoryandParse(char*);

};



#endif