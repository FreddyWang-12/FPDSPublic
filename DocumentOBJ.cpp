//
// Created by jonas on 5/2/2020.
//

#include "DocumentOBJ.h"

// Default constructor
DocumentOBJ::DocumentOBJ(){
    id = "";
    title = "";
}
// Creates a document of a given id code
DocumentOBJ::DocumentOBJ(string x){
    id = x;
}
// Creates a document of a given id code, title, and set of authors
DocumentOBJ::DocumentOBJ(string idd, string titlee, vector<string> authorss){
    id = idd;
    title = titlee;
    authors = authorss;
}
// Creates a document of a given id code and title
DocumentOBJ::DocumentOBJ(string idd, string titlee){
    id = idd;
    title = titlee;
}
// Copy Constructor
DocumentOBJ::DocumentOBJ(const DocumentOBJ& other){
    id = other.id;
    title = other.title;
    authors = other.authors;
}
//Copy Assignment Operator
DocumentOBJ& DocumentOBJ:: operator = (const DocumentOBJ& other){
    id = other.id;
    title = other.title;
    authors = other.authors;
}
//Destructor
DocumentOBJ::~DocumentOBJ()= default;

//Set a specific id for the documentOBJ
void DocumentOBJ::setID(string newID){
    id = newID;
}
//Set a specific title for the documentOBJ
void DocumentOBJ::setTitle(string newTitle){
    title = newTitle;
}
//Set a specific set of authors for the documentOBJ
void DocumentOBJ::setAuthors(vector<string> newAuthors){
    authors = newAuthors;
}
// Add a new author for the documentOBJ
void DocumentOBJ::addAuthor(string& newAuth){
    authors.push_back(newAuth);
}
// Get the id
string& DocumentOBJ::getID(){
    return id;
}
// Get the title
string& DocumentOBJ::getTitle(){
    return title;
}
// Return the documentOBJ's author list
vector<string>& DocumentOBJ::getAuthors(){
    return authors;
}
//Compares the documentOBJ to another to see if its id's ASCII value is lower than the other
int DocumentOBJ::operator<(const DocumentOBJ &other) {
    return id < other.id;
}
//Compares the documentOBJ to another to see if its id's ASCII value is higher than the other
int DocumentOBJ::operator>(const DocumentOBJ &other) {
    return id > other.id;
}
// Print out the documentOBJ's information
// Source: https://docs.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=vs-2019
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
// Print out the documentOBJ's information to a file
// Source: https://docs.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=vs-2019
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
// Print out all authors' names
void DocumentOBJ::printAuthors() {
    for(int i = 0; i < authors.size(); i++){
        cout << authors[i] << ',';
    }
    cout << endl;
}
// Determines whether or not the documentOBJ has a title
bool DocumentOBJ::iftitleExists(string&x) {
    if(x.empty()){
        return false;
    }else{
        return true;
    }
}


