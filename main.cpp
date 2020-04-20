#include <iostream>
#include <string>
#include "QueryEngine.h"
#include "DocumentParser.h"
#include "CSVReader.h"
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
    int count = 0;
    while(dirp = readdir(dp)){
//    while(count != 1000){
//        dirp = readdir(dp);
        filepath = directory + "/" + dirp->d_name;
        if(stat(filepath.c_str(), &filestat)) continue;
        if(S_ISDIR(filestat.st_mode)) continue;
        d.parseDocument(filepath);
        d.addStrings();
        d.trimTokens();
        d.tokenization();
        d.deleteAllDocText();
        d.tokenToWords();
        d.clearTokenVec();

        if(tree.isEmpty()){
            d.initialAdditonToAVLTree(tree);
        }else {
            d.insertIntoAVLTree(tree);
        }

        d.clearVector();
        d.freeMem();
        count++;
    }
    closedir(dp);
    cout << "Total AVL Tree Nodes = " << tree.getSize() << endl;
    Word& find = tree.getContent(search_word);
    cout << "Command Line Word Doc Amount: " << find.getDocSize();
    cout << "Commands Line Words Associative Documents: " << endl;
    find.printDocs();
    auto stop = high_resolution_clock::now();
auto duration = duration_cast<seconds>(stop-start);
cout << "Time Take For Program: " << duration.count() << " secounds" << endl;
//QueryEngine a;
//string search = "virus AND jonas NOT ezra";
//a.prefixIndentifier(search);
}
