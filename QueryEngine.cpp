#include "QueryEngine.h"
#include "cstring"

QueryEngine::QueryEngine() {}

QueryEngine::QueryEngine(QueryEngine &data) {
    userSearch = data.userSearch;
}

void QueryEngine::prefixIndentifier(string &arg) {
    int found;
    found = arg.find("AUTHOR");
    if(found != string::npos){
        cout << "Contains Author";
    }
    found = arg.find("AND" && "NOT");
    if(found != string::npos){
        cout << "Contains AND-NOT";
    }
    found = arg.find("AND");
    if(found!=string::npos){
        cout << "Contains AND";
    }
    found = arg.find("NOT");
    if(found != string::npos){
        cout << "Countains NOT";
    }
    found = arg.find("OR");
    if(found != string::npos){
        cout << "Contains OR";
    }

}

void QueryEngine::trimandstemSearchWord(string &word) {
    Porter2Stemmer::trim(word);
    Porter2Stemmer::stem(word);
}