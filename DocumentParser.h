//
// Created by jonas on 4/14/2020.
//

#ifndef FINALPROJECT_DOCUMENTPARSER_H
#define FINALPROJECT_DOCUMENTPARSER_H
#include "rapidjson\include\rapidjson\document.h"
#include "rapidjson\include\rapidjson\writer.h"
#include "rapidjson\include\rapidjson\filereadstream.h"
#include "rapidjson/include/rapidjson/stringbuffer.h"
#include "fstream"
#include "dirent.h"
#include "unistd.h"
#include "sys/stat.h"
#include "sys/types.h"
#include <algorithm>
#include <string>
#include "hashTable.h"
#include "CSVReader.h"
using namespace rapidjson;
using namespace std;

class DocumentParser {
public:
    void parseDocument(string&);
    void printDocument(Document&);
    void getDocumentsinDirectory(string&);
    void csvParse();
};


#endif //FINALPROJECT_DOCUMENTPARSER_H
