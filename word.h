//
// Created by Frederick Wang on 4/18/20.
//

#ifndef UNTITLED1_WORD_H
#define UNTITLED1_WORD_H
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

class word {
private:
    string data;
    vector<string> docIDs;

public:
    word();
    word(string newOne);
    void addDoc(string docID);
    void setWordData(string newOne);
    string findDoc(string docID);
    string getWordData();
};


#endif //UNTITLED1_WORD_H
