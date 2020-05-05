//
// Created by jonas on 4/27/2020.
//

// This object was originally going to be used as a means of storing the
// authors' information, but has since then been scrapped as an idea. We
// do not use this class in the final project.
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
