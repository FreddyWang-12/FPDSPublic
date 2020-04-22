#include "QueryEngine.h"
#include "cstring"

QueryEngine::QueryEngine() {}

QueryEngine::QueryEngine(QueryEngine &data) {
    userSearch = data.userSearch;
}

void QueryEngine::prefixIndentifier(string &arg) {
    int found;
    found = arg.find("AUTHOR");
    if(found != string::npos){
        cout << "Contains Author";
    }
    found = arg.find("AND" && "NOT");
    if(found != string::npos){
        cout << "Contains AND-NOT";
    }
    found = arg.find("AND");
    if(found!=string::npos){
        cout << "Contains AND";
    }
    found = arg.find("NOT");
    if(found != string::npos){
        cout << "Countains NOT";
    }
    found = arg.find("OR");
    if(found != string::npos){
        cout << "Contains OR";
    }

}

void QueryEngine::trimandstemSearchWord(char* word) {
    string searchterm = word;
    Porter2Stemmer::trim(searchterm);
    Porter2Stemmer::stem(searchterm);
    Word& find = tree.getContent(searchterm);
    cout << word << " Documents Amount: " << find.getDocSize() << endl;
    cout << "Commands Line Words Associative Documents: " << endl;
    find.printDocs();
}


void QueryEngine::getDirectoryandParse(char* fileDirectory) {
    ofstream out;
    string filepath;
    string directory = fileDirectory;
    DIR *dp;
    struct dirent *dirp;
    struct stat filestat;
    dp = opendir(fileDirectory);
    if(dp == NULL){
        cout << "Error("<< errno <<") opening " << fileDirectory << endl;
    }
    int count = 0;
    dirp = readdir(dp);
    while(dirp){
//    while(count != 10){
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
            d.trimTokens();
            d.tokenization();
            d.deleteAllDocText();

            if (tree.isEmpty()) {
                d.initialAdditonToAVLTree(tree);
            } else {
                d.insertIntoAVLTree(tree);
            }

            d.clearVector();
            count++;
        }
        dirp = readdir(dp);
    }
    closedir(dp);

}