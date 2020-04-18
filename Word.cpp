//
// Created by jonas on 4/18/2020.
//

#include "Word.h"
using namespace std;

Word::Word(){
    data = "";
}

Word::Word(string newOne){
    data = newOne;
}

void Word::addDoc(string docID) {
    docIDs.push_back(docID);
}

void Word::setWordData(string newOne) {
    data = newOne;
}

string Word::findDoc(string docID) {
    vector<string>::iterator it = find(docIDs.begin(), docIDs.end(), docID);
    if(it->data() == docID){
        return docID;
    }
    else{
        return "Negative";
    }
}

string Word::getWordData() {
    return data;
}