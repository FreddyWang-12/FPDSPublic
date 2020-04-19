//
// Created by jonas on 4/18/2020.
//

#ifndef FINALPROJECT_WORD_H
#define FINALPROJECT_WORD_H

#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

class Word {
private:
    string data;
    vector<string> docIDs;

public:
    Word();
    Word(string newOne);
    Word(string word, string docID);
    Word(string);
    Word(string,string);
    ~Word();
    Word(const Word& other);
    Word& operator = (const Word& copy);

    int operator < (const Word& other);
    int operator > (const Word& other);
    void addDoc(string docID);
    void setWordData(string newOne);
    string findDoc(string docID);
    string& getWordData();
    vector<string>& getDocs();
};


#endif //FINALPROJECT_WORD_H
