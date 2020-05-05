//
// Created by jonas on 4/14/2020.
//
///Domentation related to code that was used
// No longer in use
///https://thispointer.com/how-to-read-data-from-a-csv-file-in-c/
#ifndef FINALPROJECT_CSVREADER_H
#define FINALPROJECT_CSVREADER_H

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include "hashTable.h"
using namespace std;
class CSVReader {
string fileName;
string delimeter;
vector<string> sha;
vector<string> has_pdf_parse;
public:
    CSVReader();
    CSVReader(string filename, string delm = ","):
    fileName(filename), delimeter(delm){}
    void getData();
    void printVector();
    void putInHashTable();
    string getHashValue(string&);
    bool ifExists(string&);
    hashTable<string,string> hash;
};


#endif //FINALPROJECT_CSVREADER_H
