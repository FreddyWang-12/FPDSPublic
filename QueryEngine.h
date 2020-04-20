#ifndef QUERY_ENGINE_H
#define QUERY_ENGINE_H

#include <iostream>
#include <string>
#include "cstring"
#include "porter2_stemmer.h"
using namespace std;

class QueryEngine{
private:
    string userSearch;
public:
    QueryEngine();
    QueryEngine(QueryEngine&);
    void prefixIndentifier(string&);
    void trimandstemSearchWord(string&);

};



#endif