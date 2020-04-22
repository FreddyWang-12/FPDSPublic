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
Word::Word(string word, string docID){
    data = word;
    this->addDoc(docID);
}

void Word::addDoc(string& docID) {
    docIDs.push_back(docID);
}

Word::~Word(){
}

Word::Word(const Word& other){
    data = other.data;
    docIDs = other.docIDs;
}

Word& Word::operator = (const Word& copy){
    data = copy.data;
    docIDs = copy.docIDs;
    return *this;
}

int Word::operator < (const Word& other){
    if(data < other.data){
        return true;
    }
    return false;
}

int Word::operator > (const Word& other){
    if(data > other.data){
        return true;
    }
    return false;
}

void Word::setWordData(string newOne) {
    data = newOne;
}

bool Word::findDoc(string& docID) {
    return binary_search(docIDs.begin(),docIDs.end(),docID);
}

string& Word::getWordData() {
    return data;
}

vector<string>& Word::getDocs(){
    return docIDs;
}

void Word::printDocs() {
    for(int i = 0; i < docIDs.size(); i++){
        cout << docIDs[i] << endl;
    }
}

int Word::getDocSize() {
    return docIDs.size();
}
