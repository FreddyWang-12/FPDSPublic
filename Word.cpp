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
Word::Word(string word, string docID, int x){
    data = word;
    this->addDoc(docID);
    this->addFrequency(x);
}

Word::Word(string word, string docID){
    data = word;
    this->addDoc(docID);
}

Word::Word(string word, vector<string> docids, vector<int> docFreq) {
    data = word;
    docIDs = docids;
    frequency = docFreq;
}

void Word::addDoc(string& docID) {
    docIDs.push_back(docID);
}

void Word::addFrequency(int& x) {
    frequency.push_back(x);
}

Word::~Word()= default;

Word::Word(const Word& other){
    data = other.data;
    docIDs = other.docIDs;
    frequency = other.frequency;
}

Word& Word::operator = (const Word& copy){
    data = copy.data;
    docIDs = copy.docIDs;
    frequency = copy.frequency;
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
//    sort(docIDs.begin(),docIDs.end());
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

string& Word::getWord() {
    return data;
}

std::ostream &operator<<(std::ostream & output, const Word & obj) {
    output <<'[' << obj.data << ']' << ',';
    for(int i = 0; i < obj.docIDs.size(); i++){
        if(i == obj.docIDs.size()-1){
            output << obj.docIDs[i] << "|";
        }else {
            output << obj.docIDs[i] << ',';
        }
    }
//    output << endl;
    return output;
}

std::ofstream &operator<<(std::ofstream &output, const Word &obj) {
//        output << '"' << obj.data.c_str() << '"' << ',';
        output <<'[' << obj.data << ']';
        for(int i = 0; i < obj.docIDs.size(); i++) {
            if (i == obj.docIDs.size() - 1) {
                output << obj.docIDs[i].c_str() << ",|,";
            } else {
                output << obj.docIDs[i].c_str() << ',';
            }
        }
        for(int j = 0; j < obj.frequency.size(); j++){
            if(j == obj.frequency.size()-1){
                output << obj.frequency[j] << ",||,";
            }else{
                output << obj.frequency[j] << ',';
            }
        }
//        output << endl;
    return output;
}

vector<string>& Word::getTop15Docs(vector<string>& finalVecTop) {
    vector<string> tempDocIds;
    tempDocIds = finalVecTop;
    vector<int> tempFrequency;
    tempFrequency = frequency;
    int counter = 0;
    while(counter != 15 && counter != finalVecTop.size()){
        int maxEleIndex = max_element(tempFrequency.begin(), tempFrequency.end()) - tempFrequency.begin();
        string tempID = tempDocIds[maxEleIndex];
        topElements.push_back(tempID);
        tempDocIds.erase(tempDocIds.begin() + maxEleIndex);
        tempFrequency.erase(tempFrequency.begin() + maxEleIndex);
        counter++;
    }
    return topElements;
}

vector<int>& Word::getFrequency() {
    return frequency;
}

int Word::getFreqSize() {
    return frequency.size();
}


//void Word::insertintoMap(string & newword, int & x) {
//    auto it = frequency.end();
//    frequency.insert(it,{newword,x});
//}
//
//map<string, int> &Word::getMap() {
//    return frequency;
//}


//void Word::sortMaxtoMin() {
//    sort(.begin(),docFrequency.end(),[](auto &left, auto &right){
//       return left.second < right.second;
//    });
//}
