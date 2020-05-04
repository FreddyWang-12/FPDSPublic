//
// Created by jonas on 5/2/2020.
//

#include "DocumentOBJ.h"
DocumentOBJ::DocumentOBJ(){
    id = "";
    title = "";
}
DocumentOBJ::DocumentOBJ(string x){
    id = x;
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

std::ofstream &operator<<(std::ofstream &output, const DocumentOBJ &obj) {
    if(obj.id.empty()){
        output << "~" << "NO ID" << "~" << endl;
    }else{
        output << "~" << obj.id << "~";
    }

    output << "~" << obj.title << "~";
    for(int i = 0; i < obj.authors.size(); i++){
        if(i == obj.authors.size()-1){
            output << obj.authors[i].c_str() << ",~~~,";
        }else{
            if(obj.authors[i].empty()){
                output << "DNE" << ',';
            }else {
                output << obj.authors[i].c_str() << ',';
            }
        }
    }
    return output;
}

std::ostream &operator<<(std::ostream &output, const DocumentOBJ &obj) {
    output << '[' << obj.id << ']';
    output << '[' << obj.title << ']';
    for(int i = 0; i < obj.authors.size(); i++){
        if(i == obj.authors.size()-1){
            output << obj.authors[i] << ",||,";
        }else{
            if(obj.authors.at(i).empty()){
                i++;
            }else {
                output << obj.authors[i] << ',';
            }
        }

    }
    return output;
}

void DocumentOBJ::printAuthors() {
    for(int i = 0; i < authors.size(); i++){
        cout << authors[i] << ',';
    }
    cout << endl;
}

bool DocumentOBJ::iftitleExists(string&x) {
    if(x.empty()){
        return false;
    }else{
        return true;
    }
}


