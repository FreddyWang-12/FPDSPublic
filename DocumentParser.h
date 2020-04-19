//
// Created by jonas on 4/14/2020.
//

#ifndef FINALPROJECT_DOCUMENTPARSER_H
#define FINALPROJECT_DOCUMENTPARSER_H
#include "rapidjson/include/rapidjson/document.h"
#include "rapidjson/include/rapidjson/writer.h"
#include "rapidjson/include/rapidjson/stringbuffer.h"
#include "rapidjson/include/rapidjson/filereadstream.h"
#include "fstream"
#include "dirent.h"
#include "unistd.h"
#include "sys/stat.h"
#include "sys/types.h"
#include <algorithm>
#include <string>
#include "hashTable.h"
#include "CSVReader.h"
#include "porter2_stemmer.h"
#include "vector"
#include "Word.h"
//#include <bits/stdc++.h>
#include "AVLTree.h"

using namespace rapidjson;
using namespace std;

class DocumentParser {
private:
    string paperid;
    string title ;
    string text;
    string bodytext;
    vector<string> token;
    vector<string> stopwords;

public:
    void parseDocument(string&);
    void printDocument(Document&);
    void getDocumentsinDirectory(string&);
    void removeNONLettersandLowercase(string&);
    void tokenization(string&);
    void printToken();
    void stemTokens();
    void stemStopWords();
    void getStopWords();
    void printStopWords();
    void removeStopWords();
    void cleanVector();
    void clearVector();
    void insertIntoAVLTree(AVLTree<Word> &);

};


#endif //FINALPROJECT_DOCUMENTPARSER_H
