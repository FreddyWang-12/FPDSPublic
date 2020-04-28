//
// Created by jonas on 4/27/2020.
//

#ifndef FINALPROJECT_AUTHOR_H
#define FINALPROJECT_AUTHOR_H

#include "string"
#include "vector"
class Author {
private:
    std::string lastname;
    std::vector<std::string> document_IDS;
public:
    Author();
//    Author(std::string,std::vector<std::string>);
    Author(std::string,std::string);
    Author(const Author&);
    ~Author();
    void addDocument(std::string& );



};


#endif //FINALPROJECT_AUTHOR_H
