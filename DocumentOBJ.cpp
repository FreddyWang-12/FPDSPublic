//
// Created by jonas on 5/2/2020.
//

#include "DocumentOBJ.h"
DocumentOBJ::DocumentOBJ(){
    id = "";
    title = "";
}
DocumentOBJ::DocumentOBJ(string idd, string titlee, vector<string> authorss){
    id = idd;
    title = titlee;
    authors = authorss;
}
DocumentOBJ::DocumentOBJ(string idd, string titlee){
    id = idd;
    title = titlee;
}
DocumentOBJ::DocumentOBJ(const DocumentOBJ& other){
    id = other.id;
    title = other.title;
    authors = other.authors;
}
DocumentOBJ& DocumentOBJ:: operator = (const DocumentOBJ& other){
    id = other.id;
    title = other.title;
    authors = other.authors;
}

DocumentOBJ::~DocumentOBJ()= default;

void DocumentOBJ::setID(string newID){
    id = newID;
}
void DocumentOBJ::setTitle(string newTitle){
    title = newTitle;
}
void DocumentOBJ::setAuthors(vector<string> newAuthors){
    authors = newAuthors;
}
void DocumentOBJ::addAuthor(string& newAuth){
    authors.push_back(newAuth);
}
string& DocumentOBJ::getID(){
    return id;
}
string& DocumentOBJ::getTitle(){
    return title;
}
vector<string>& DocumentOBJ::getAuthors(){
    return authors;
}

int DocumentOBJ::operator<(const DocumentOBJ &other) {
    return id < other.id;
}

int DocumentOBJ::operator>(const DocumentOBJ &other) {
    return id > other.id;
}
