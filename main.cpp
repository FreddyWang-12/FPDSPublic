#include <iostream>
#include <string>
#include "DocumentParser.h"
#include "QueryEngine.h"
#include "dirent.h"
#include "AVLTree.h"
#include "Word.h"
#include "chrono"
using namespace std;
using namespace std::chrono;


int main(int argc, char* argv[]) {
//    CSVReader reader(R"(C:\Users\jonas\Desktop\DataStructures\FinalProject\Data\metadata-cs2341)");
//    reader.getData();
//    reader.putInHashTable();
//    reader.printVector();
    auto start = high_resolution_clock::now();
    AVLTree<Word> tree;
    QueryEngine engine;
//    Word words;
    DocumentParser d;
    ofstream out;
    string filepath;
    DIR *dp;
    struct dirent *dirp;
    struct stat filestat;
    dp = opendir(argv[1]);
    if(dp == NULL){
        cout << "Error("<< errno <<") opening " << argv[1] << endl;
    }
    string directory = argv[1];
    string search_word = argv[2];
//    int count = 0;
    dirp = readdir(dp);
    while(dirp){
//    while(count != 1000){
//        dirp = readdir(dp);
        filepath = directory + "/" + dirp->d_name;
        string sha = dirp->d_name;
        string extension;
        if(strlen(sha.c_str()) > 4) {
            extension = sha.substr(sha.length()-5);
        }
        if(extension == ".json") {
        if(stat(filepath.c_str(), &filestat)) continue;
        if(S_ISDIR(filestat.st_mode)) continue;
            d.parseDocument(filepath);
            d.addStrings();
            d.trimTokens();
            d.tokenization();
            d.deleteAllDocText();
            d.tokenToWords();
            d.clearTokenVec();

            if (tree.isEmpty()) {
                d.initialAdditonToAVLTree(tree);
            } else {
                d.insertIntoAVLTree(tree);
            }

            d.clearVector();
            d.freeMem();
//            count++;
        }
        dirp = readdir(dp);
    }
    closedir(dp);
    engine.trimandstemSearchWord(search_word);
    cout << "Total AVL Tree Nodes = " << tree.getSize() << endl;
    Word& find = tree.getContent(search_word);
    cout << argv[2] << " Documents Amount: " << find.getDocSize() << endl;
    cout << "Commands Line Words Associative Documents: " << endl;
    find.printDocs();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop-start);
    cout << "Time Take For Program: " << duration.count() << " seconds " << endl;
}
