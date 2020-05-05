//
// Created by jonas on 4/27/2020.
//

// This object was originally going to be used as a means of storing the
// authors' information, but has since then been scrapped as an idea. We
// do not use this class in the final project.
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
