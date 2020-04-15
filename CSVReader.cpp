//
// Created by jonas on 4/14/2020.
//

#include "CSVReader.h"

CSVReader::CSVReader(){}



void CSVReader::getData() {
    ifstream file(fileName);
    string buffer;
    string shaa;
    string bool_has_pdf_parse;
    getline(file,buffer,'\n');
    int count = 0;
    while(!file.eof()){
        getline(file,buffer,',');
        getline(file,shaa,',');
        if(!shaa.empty() && shaa.find(';') == string::npos) {
            sha.push_back(shaa);
            getline(file,bool_has_pdf_parse,',');
            has_pdf_parse.push_back(bool_has_pdf_parse);
            getline(file,buffer,'\n');
        }else{
//            sha.push_back("DNE");
            getline(file,buffer,'\n');
        }
//        getline(file,bool_has_pdf_parse,',');
//        has_pdf_parse.push_back(bool_has_pdf_parse);
//        getline(file,buffer,'\n');
        count++;
    }
    file.close();

}


void CSVReader::printVector() {
    for(int i = 0; i < sha.size(); i++){
        cout << sha[i] << "   " << has_pdf_parse[i] << endl;
    }
}

void CSVReader::putInHashTable() {
    for(int i = 0; i < sha.size(); i++){
        hash.addNewKey(sha[i],has_pdf_parse[i]);
    }
}

string CSVReader::getHashValue(string & arg) {
    string temp = hash.getData(arg);
    return temp;
}

bool CSVReader::ifExists(string &data) {
    return hash.findKey(data);
}

