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
    int allArticlesIndexed;
    int totalUniqueWords;
    vector<string> finalVec;
    string userSearch;
    AVLTree<DocumentOBJ> docTree;
    AVLTree<Word> tree;
    hashTable<string,string> tableofHash;
    vector<Word> vecofWordss;
    vector<pair<string, int>> wordFreq;
public:
    QueryEngine();
    QueryEngine(QueryEngine&);
    void getDirectoryandParse(char*);
    void searchQuery(string& query);
    void printStatistics();
    void outputTree();
    void outputTreetoFile();
    void getTreeFromFile();
};



#endif