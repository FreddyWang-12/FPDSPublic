//
// Created by jonas on 4/18/2020.
//

#ifndef FINALPROJECT_WORD_H
#define FINALPROJECT_WORD_H


#include <iostream>
#include <cstring>
#include <vector>
#include <bits/stdc++.h>
#include <map>
#include <string>
using namespace std;

class Word {
private:
    string data;
    vector<string> docIDs;
    vector<int> frequency;


public:
    Word();
    Word(string);
    Word(string,string);
    Word(string,string,int);
    Word(string,vector<string>);
    ~Word();
    Word(const Word& other);
    Word& operator = (const Word& copy);

    int operator < (const Word& other);
    int operator > (const Word& other);
    void addDoc(string& docID);
    void addFrequency(int);
    int getDocSize();
    string& getWord();
    void printDocs();
    void setWordData(string newOne);
    bool findDoc(string& );
    string& getWordData();
    vector<string>& getDocs();
    void sortMaxtoMin();
    void insertintoMap(string&,int&);
    map<string,int>& getMap();
    friend std::ostream& operator<<(std::ostream&, const Word&);
    friend std::ofstream& operator<<(std::ofstream&, const Word&);
};


#endif //FINALPROJECT_WORD_H
