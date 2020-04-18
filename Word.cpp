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

string Word::findDoc(string docID) {
    vector<string>::iterator it = find(docIDs.begin(), docIDs.end(), docID);
    if(it->data() == docID){
        return docID;
    }
    else{
        return "Negative";
    }
}

string& Word::getWordData() {
    return data;
}

vector<string>& Word::getDocs(){
    return docIDs;
}