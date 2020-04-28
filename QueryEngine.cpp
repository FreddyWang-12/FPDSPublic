#include "QueryEngine.h"


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

void QueryEngine::trimandstemSearchWord(string& searchWord) {
    Porter2Stemmer::trim(searchWord);
    Porter2Stemmer::stem(searchWord);
    Word& find = tree.getContent(searchWord);
    cout << searchWord << " Documents Amount: " << find.getDocSize() << endl;
    cout << "Commands Line Words Associative Documents: " << endl;
    find.printDocs();
}


void QueryEngine::getDirectoryandParse(char* fileDirectory) {
    DocumentParser d;
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
//    dirp = readdir(dp);
//    while(dirp){
    while(count != 100){
        dirp = readdir(dp);
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
            d.stemtrimAuthorNames();
            d.initialAuthorInserttoHashTable(tableofHash);

            d.clearVector();
            count++;
        }
        dirp = readdir(dp);
    }
    closedir(dp);

}

void QueryEngine::wordanAuthorSearchWord(string &searchWord) {
    vector<string> finalVec;
    Porter2Stemmer::trim(searchWord);
    stringstream check(searchWord);
    string temp;
    getline(check,temp,' ');
    Porter2Stemmer::stem(temp);
    Word& find = tree.getContent(temp);
    getline(check,temp,' ');
    getline(check,temp,' ');
    Porter2Stemmer::stem(temp);
    vector<string>& tempVec = find.getDocs();
    for(const auto & i : tempVec){
        if(temp == tableofHash.findGivenData(temp,i)){
            finalVec.push_back(i);
        }
    }

    cout << searchWord << " Documents Amount: " << finalVec.size() << endl;
    cout << "Documents Relevent to Author and Search Only: " << endl;
    for(const auto & t : finalVec){
        cout << t << endl;
    }
}
