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

// A class that is used to store a given word's information, such
// as its actual word string(data), its associated documents list,
// and the frequencies with those documents. This is stored in an
// AVL Tree in the query engine
class Word {
private:
    string data; // The actual word's string data
    vector<string> docIDs; // The word's list of associated document ids
    vector<int> frequency; // A corresponding list of frequencies to go alongside the ids
    // Thank you Emily and Fernando for your advice. It really helps!


public:
    Word(); // Default constructor
    Word(string); // Constructor that sets the word's string data
    Word(string,string); // Constructor of a given word plus the first document it is found in
    Word(string,string,int); // Constructor of a given word plus the first document it is found in and its frequency in the document
    Word(string,vector<string>,vector<int>); // Constructor of a given word plus the documents it is found in and the frequencies
    ~Word(); // Destructor
    Word(const Word& other); // Copy Constructor
    Word& operator = (const Word& copy); //Copy Assignment Operator
    vector<string> topElements; //Returns the top 15 most relevant documents
    int operator < (const Word& other); //Compares the word object to another to see if its string value is lower than the other
    int operator > (const Word& other); //Compares the word object to another to see if its string value is higher than the other
    vector<string>& getTop15Docs(vector<string>&); //Returns the top 15 most relevant documents
    void addDoc(string& docID); // Adds a new document id
    void addFrequency(int&); // Adds a new frequency
    int getDocSize(); // Returns the size of "docIDs"
    int getFreqSize(); // Returns the size of "frequency"
    string& getWord(); // Return the word object's string data
    void printDocs(); // Prints out all document IDs for a given word object
    void setWordData(string newOne); // Set a specific string data to this word
    bool findDoc(string& ); // Determines if this word is associated with a specific word
    string& getWordData(); // Returns the word's string data
    vector<string>& getDocs(); // Returns the list of all document ids
    vector<int>& getFrequency(); // Returns the list of all frequencies
    void sortMaxtoMin();
    void insertintoMap(string&,int&);
    map<string,int>& getMap();
    friend std::ostream& operator<<(std::ostream&, const Word&); // Print out the documentOBJ's information
    friend std::ofstream& operator<<(std::ofstream&, const Word&); // Print out the documentOBJ's information to a file
};


#endif //FINALPROJECT_WORD_H
