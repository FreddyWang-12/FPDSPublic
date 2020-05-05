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
#include "DocumentOBJ.h"
#include <cmath>
#include <stdio.h>
using namespace std;
class QueryEngine{
private:
    vector<string> finalVec;
    string userSearch;
    AVLTree<DocumentOBJ> docTree;
    AVLTree<Word> tree;
    hashTable<string,string> tableofHash;
public:
    QueryEngine();
    QueryEngine(QueryEngine&);
    void getDirectoryandParse(char*);
    void getAuthorsQuick(char*);
    void searchQuery(string& query);
    void printStatistics();
    void outputTree();
    void outputTreetoFile();
    void getTreeFromFile();
    void getDocTreeFromFile();
    multimap<int,string,greater<int>> getWhatMatters(map<string,int>&,vector<string>&);
    vector<int> calculateIDF(Word&);
    vector <string> getIntersection(vector<vector<string>>&);
    void searchMenue();
    void statisticsPrint();

};



#endif