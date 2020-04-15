#ifndef QUERY_ENGINE_H
#define QUERY_ENGINE_H

#include <iostream>
#include <string>
using namespace std;

class QueryEngine{
private:
    string userSearch;
public:
    QueryEngine();
    QueryEngine(QueryEngine&);
    void removeStopWords();
    void prefixIndentifier(string&);
    void rankRelevancy();
    string parseString(string&);

};



#endif