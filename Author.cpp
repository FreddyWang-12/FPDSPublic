//
// Created by jonas on 4/27/2020.
//

#include "Author.h"

//Author::Author(std::string name, std::vector<std::string> docIDS) {
//        firstname
//}
Author::Author() {
    lastname = "";
}
Author::Author(std::string ln, std::string documentID) {
    lastname = ln;
    this->addDocument(documentID);
}

Author::Author(const Author & auth) {
    lastname = auth.lastname;
    document_IDS = auth.document_IDS;
}

Author::~Author() {}


void Author::addDocument(std::string & doc) {
    document_IDS.push_back(doc);
}
