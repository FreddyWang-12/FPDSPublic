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

// Takes in a query string, parses it, and
// Finds results of documents based on it. Stores
// all words and documents on AVL Trees and all
// author info on a hash table
class QueryEngine{
private:
    vector<string> finalVec; // Final Vector of Document IDs
    string userSearch; // The user's query search
    AVLTree<DocumentOBJ> docTree; // All of the documents
    AVLTree<Word> tree; // All of the words
    hashTable<string,string> tableofHash; // All author info
public:
    QueryEngine(); // Default constructor
    QueryEngine(QueryEngine&); //Copy Constructor
    void getDirectoryandParse(char*); // Takes a directory of json files, parses them, and then stores their info on the AVL Trees and hahs tables
    void getAuthorsQuick(char*); //Grabs an author and his/her info from the author hash table
    void searchQuery(string& query); //Takes a query search and finds all documents associated with that search
    void printStatistics();
    void outputTree(); // Outputs the word AVL Tree
    void outputTreetoFile(); //Puts all of the word AVL Tree's data into an output file
    void getTreeFromFile(); //Grabs that output file and repopulates the word AVL Tree
    void getDocTreeFromFile(); //Grabs that output file and repopulates the documentOBJ AVL Tree
    multimap<int,string,greater<int>> getWhatMatters(map<string,int>&,vector<string>&); // Grabs the most revalent documentOBJs
    vector<int> calculateIDF(Word&); // Calculates the frequencies for a given document and its words
    vector <string> getIntersection(vector<vector<string>>&); //Finds intersecting values in the "AND" part of searchQuery
    void searchMenue(); // Menu for the program
    void statisticsPrint(); // Prints some basic statistics

};



#endif