#include <iostream>
#include <string>
#include "fstream"
#include "QueryEngine.h"
#include "DocumentParser.h"
#include "CSVReader.h"
#include "vector"
#include "dirent.h"
#include "AVLTree.h"
#include "Word.h"
#include "unistd.h"
using namespace std;


int main(int argc, char* argv[]) {
//    CSVReader reader(R"(C:\Users\jonas\Desktop\DataStructures\FinalProject\Data\metadata-cs2341)");
//    reader.getData();
//    reader.putInHashTable();
//    reader.printVector();
    AVLTree<Word> tree;
    Word words;
    DocumentParser d;
    ofstream out;
    ifstream fin;
    string filepath;
    DIR *dp;
    struct dirent *dirp;
    struct stat filestat;
    dp = opendir(argv[1]);
    if(dp == NULL){
        cout << "Error("<< errno <<") opening " << argv[1] << endl;
    }
    string directory = argv[1];
//    while(dirp = readdir(dp)){
    int count = 0;
    d.stemStopWords();
    while(count != 100){
        dirp = readdir(dp);
        filepath = directory + "/" + dirp->d_name;
        if(stat(filepath.c_str(), &filestat)) continue;
        if(S_ISDIR(filestat.st_mode)) continue;
        string sha = dirp->d_name;
//        string get = sha.erase(sha.find("."));
//        string get = sha.erase(sha.find('.')-4);
//        if(csvreader.ifExists(get)){
        d.parseDocument(filepath);
        d.stemTokens();
        //d.getStopWords();
        d.removeStopWords();
        d.cleanVector();
        d.tokenToWords(words);
        int first = 0;
        while(first != 1){
            d.initialAdditonToAVLTree(tree);
            first++;
        }
        
        d.insertIntoAVLTree(tree);
//        d.printToken();
        d.clearVector();
//        }
        count++;
    }






//QueryEngine a;
//string search = "virus AND jonas NOT ezra";
//a.prefixIndentifier(search);
}
