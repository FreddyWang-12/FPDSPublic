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
#include "hashTable.h"
using namespace std;

class QueryEngine{
private:
    vector<string> finalVec;
    string userSearch;
    AVLTree<Word> tree;
    hashTable<string,string> tableofHash;
public:
    QueryEngine();
    QueryEngine(QueryEngine&);
    void prefixIndentifier(string&);
    void trimandstemSearchWord(string&);
    void wordanAuthorSearchWord(string&);
    void andSearch(string&);
    void getDirectoryandParse(char*);
    void orSearch(string&);
};



#endif