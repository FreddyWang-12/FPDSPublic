//
// Created by jonas on 5/2/2020.
//

#ifndef FINALPROJECT_DOCUMENTOBJ_H
#define FINALPROJECT_DOCUMENTOBJ_H

#include <string>
#include <cstring>
#include <vector>
using namespace std;
class DocumentOBJ{
private:
    string id;
    string title;
    vector<string> authors;
public:
    DocumentOBJ();
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
    string& getID();
    string& getTitle();
    vector<string>& getAuthors();
};


#endif //FINALPROJECT_DOCUMENTOBJ_H
