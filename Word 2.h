//
// Created by jonas on 4/18/2020.
//

#ifndef FINALPROJECT_WORD_H
#define FINALPROJECT_WORD_H


#include <iostream>
#include <cstring>
#include <vector>
//#include <bits/stdc++.h>
#include <sstream>
#include <fstream>
#include <map>
#include <string>

// Prototype Word
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
    Word(string,vector<string>,vector<int>);
    ~Word();
    Word(const Word& other);
    Word& operator = (const Word& copy);
    vector<string> topElements;
    int operator < (const Word& other);
    int operator > (const Word& other);
    vector<string>& getTop15Docs(vector<string>&);
    void addDoc(string& docID);
    void addFrequency(int&);
    int getDocSize();
    int getFreqSize();
    string& getWord();
    void printDocs();
    void setWordData(string newOne);
    bool findDoc(string& );
    string& getWordData();
    vector<string>& getDocs();
    vector<int>& getFrequency();
    void sortMaxtoMin();
    void insertintoMap(string&,int&);
    map<string,int>& getMap();
    friend std::ostream& operator<<(std::ostream&, const Word&);
    friend std::ofstream& operator<<(std::ofstream&, const Word&);
};


#endif //FINALPROJECT_WORD_H
