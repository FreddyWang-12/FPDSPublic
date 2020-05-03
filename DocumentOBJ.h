//
// Created by jonas on 5/2/2020.
//

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
    string id;
    string title;
    vector<string> authors;
public:
    DocumentOBJ();
    DocumentOBJ(string);
    DocumentOBJ(string id, string title, vector<string> authors);
    DocumentOBJ(string id, string title);
    DocumentOBJ(const DocumentOBJ& other);
    DocumentOBJ& operator = (const DocumentOBJ& other);
    ~DocumentOBJ();
    int operator < (const DocumentOBJ& other);
    int operator > (const DocumentOBJ& other);
    void setID(string newID);
    void setTitle(string newTitle);
    void setAuthors(vector<string> newAuthors);
    void addAuthor(string& newAuth);
    void printAuthors();
    string& getID();
    string& getTitle();
    bool iftitleExists(string&);
    vector<string>& getAuthors();
    friend std::ostream& operator<<(std::ostream&, const DocumentOBJ&);
    friend std::ofstream& operator<<(std::ofstream&, const DocumentOBJ&);
};


#endif //FINALPROJECT_DOCUMENTOBJ_H
