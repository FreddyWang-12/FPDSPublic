//
// Created by jonas on 5/2/2020.
//

// Used to store all of the documents' information all in one
// object, including the authors associated with them. These are
// sorted into their own AVL Tree
#ifndef FINALPROJECT_DOCUMENTOBJ_H
#define FINALPROJECT_DOCUMENTOBJ_H

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
using namespace std;
class DocumentOBJ{
private:
    string id; // The document's id
    string title; // The title of the document
    vector<string> authors; //All authors associated with the document
public:
    DocumentOBJ(); // Default constructor
    DocumentOBJ(string); // Creates a document of a given id code
    DocumentOBJ(string id, string title, vector<string> authors); // Creates a document of a given id code, title, and set of authors
    DocumentOBJ(string id, string title); // Creates a document of a given id code and title
    DocumentOBJ(const DocumentOBJ& other); // Copy Constructor
    DocumentOBJ& operator = (const DocumentOBJ& other); //Copy Assignment Operator
    ~DocumentOBJ(); //Destructor
    int operator < (const DocumentOBJ& other); //Compares the documentOBJ to another to see if its id's ASCII value is higher than the other
    int operator > (const DocumentOBJ& other); //Compares the documentOBJ to another to see if its id's ASCII value is lower than the other
    void setID(string newID); //Set a specific id for the documentOBJ
    void setTitle(string newTitle); //Set a specific title for the documentOBJ
    void setAuthors(vector<string> newAuthors); //Set a specific set of authors for the documentOBJ
    void addAuthor(string& newAuth); // Add a new author for the documentOBJ
    void printAuthors(); // Print out all authors' names
    string& getID(); // Get the id
    string& getTitle(); // Get the title
    bool iftitleExists(string&); // Determines whether or not the documentOBJ has a title
    vector<string>& getAuthors(); // Return the documentOBJ's author list
    friend std::ostream& operator<<(std::ostream&, const DocumentOBJ&); // Print out the documentOBJ's information
    friend std::ofstream& operator<<(std::ofstream&, const DocumentOBJ&); // Print out the documentOBJ's information to a file
};


#endif //FINALPROJECT_DOCUMENTOBJ_H
