//
// Created by Frederick Wang on 4/18/20.
//

#include "word.h"
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

word::word(){
    data = "";
}

word::word(string newOne){
    data = newOne;
}

void word::addDoc(string docID) {
    docIDs.push_back(docID);
}

void word::setWordData(string newOne) {
    data = newOne;
}

string word::findDoc(string docID) {
    vector<string>::iterator it = find(docIDs.begin(), docIDs.end(), docID);
    if(it->data() == docID){
        return docID;
    }
    else{
        return "Negative";
    }
}

string word::getWordData() {
    return data;
}