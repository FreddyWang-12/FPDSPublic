//
// Created by jonas on 4/14/2020.
//

#include "DocumentParser.h"


void DocumentParser::parseDocument(string& file) {
    FILE* fp = fopen(file.c_str(),"rb");
    char readingBuffer[3000];
    FileReadStream is(fp,readingBuffer, sizeof(readingBuffer));
    Document d;
    d.ParseStream(is);
    assert(d.IsObject());
//    assert(d.HasMember("paper_id"));
//    assert(d["paper_id"].IsString());
//    assert(d.IsObject());
    assert(d.HasMember("metadata"));
    assert(d["metadata"]["title"].IsString());
//    cout << d["metadata"]["title"].GetString() << endl;
//    this->printDocument(d);
    fclose(fp);
}


void DocumentParser::printDocument(Document& data) {
    StringBuffer bufStream;
    Writer<StringBuffer> writer(bufStream);
    data.Accept(writer);
//    cout << bufStream.GetString() << endl;
}


void DocumentParser::getDocumentsinDirectory(string& directory) {
    CSVReader obj;
    ifstream fin;
    string filepath;
    DIR *dp;
    struct dirent *dirp;
    struct stat filestat;
    dp = opendir(directory.c_str());
    if(dp == NULL){
        cout << "Error("<< errno <<") opening " << directory << endl;
    }

//    while(dirp = readdir(dp)){
int count = 0;
    while(count != 100){
        dirp = readdir(dp);
        filepath = directory + "/" + dirp->d_name;
        if(stat(filepath.c_str(), &filestat)) continue;
        if(S_ISDIR(filestat.st_mode)) continue;
        string sha = dirp->d_name;
        string get = sha.erase(sha.find('.')-4);
//        if(obj.ifExists(get)){
            this->parseDocument(filepath);
//        }
        count++;
    }

    closedir(dp);
}



void DocumentParser::csvParse() {

}