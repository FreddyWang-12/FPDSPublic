//
// Created by jonas on 4/18/2020.
//

#include "Word.h"
using namespace std;
// A class that is used to store a given word's information, such
// as its actual word string(data), its associated documents list,
// and the frequencies with those documents. This is stored in an
// AVL Tree in the query engine

// Default constructor
Word::Word(){
    data = "";
}

// Constructor that sets the word's string data
Word::Word(string newOne){
    data = newOne;
}

// Constructor of a given word plus the first document it is found in
Word::Word(string word, string docID, int x){
    data = word;
    this->addDoc(docID);
    this->addFrequency(x);
}

// Constructor of a given word plus the first document it is found in and its frequency in the document
Word::Word(string word, string docID){
    data = word;
    this->addDoc(docID);
}

// Constructor of a given word plus the documents it is found in and the frequencies
Word::Word(string word, vector<string> docids, vector<int> docFreq) {
    data = word;
    docIDs = docids;
    frequency = docFreq;
}
// Adds a new document id
void Word::addDoc(string& docID) {
    docIDs.push_back(docID);
}

// Adds a new frequency
void Word::addFrequency(int& x) {
    frequency.push_back(x);
}

// Destructor
Word::~Word()= default;

// Copy Constructor
Word::Word(const Word& other){
    data = other.data;
    docIDs = other.docIDs;
    frequency = other.frequency;
}

//Copy Assignment Operator
Word& Word::operator = (const Word& copy){
    data = copy.data;
    docIDs = copy.docIDs;
    frequency = copy.frequency;
    return *this;
}
//Compares the word object to another to see if its string value is lower than the other
int Word::operator < (const Word& other){
    if(data < other.data){
        return true;
    }
    return false;
}
//Compares the word object to another to see if its string value is higher than the other
int Word::operator > (const Word& other){
    if(data > other.data){
        return true;
    }
    return false;
}
// Set a specific string data to this word
void Word::setWordData(string newOne) {
    data = newOne;
}
// Determines if this word is associated with a specific word
bool Word::findDoc(string& docID) {
//    sort(docIDs.begin(),docIDs.end());
    return binary_search(docIDs.begin(),docIDs.end(),docID);
}
// Returns the word's string data
string& Word::getWordData() {
    return data;
}
// Returns the list of all document ids
vector<string>& Word::getDocs(){
    return docIDs;
}
// Prints out all document IDs for a given word object
void Word::printDocs() {
    for(int i = 0; i < docIDs.size(); i++){
        cout << docIDs[i] << endl;
    }
}
// Returns the size of "docIDs"
int Word::getDocSize() {
    return docIDs.size();
}
// Return the word object's string data
string& Word::getWord() {
    return data;
}
// Print out the documentOBJ's information
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
// Print out the documentOBJ's information to a file
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

//Returns the top 15 most relevant documents
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
// Returns the list of all frequencies
vector<int>& Word::getFrequency() {
    return frequency;
}
// Returns the size of "frequency"
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
