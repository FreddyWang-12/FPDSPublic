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
    while(count != 1000){
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
    finalVec.clear();
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
    if(!tableofHash.emptyAt(temp)) {
        LinkedList<string>& docs = tableofHash.getDataList(temp);
        for (int i = 0; i < tempVec.size(); i++) {
            if (docs.findValue(tempVec.at(i))) {
                finalVec.push_back(tempVec[i]);
            }
        }
    }
    cout << searchWord << " Documents Amount: " << finalVec.size() << endl;
    cout << "Documents Relevent to Author and Search Only: " << endl;
    for(const auto t : finalVec){
        cout << t << endl;
    }
}

void QueryEngine::andSearch(string &searchword) {
    finalVec.clear();
    Porter2Stemmer::trim(searchword);
    stringstream check(searchword);
    string temp;
    getline(check,temp,' ');
    getline(check,temp,' ');
    Porter2Stemmer::stem(temp);
    Word& find1 = tree.getContent(temp);
    vector<string>& tempVec1 = find1.getDocs();
    getline(check,temp,' ');
    Porter2Stemmer::stem(temp);
    Word& find2 = tree.getContent(temp);
    vector<string>& tempVec2 = find2.getDocs();
    sort(tempVec1.begin(),tempVec1.end());
    sort(tempVec2.begin(),tempVec2.end());
    set_intersection(tempVec1.begin(),tempVec1.end(),tempVec2.begin(),tempVec2.end(),back_inserter(finalVec));
//    if(tempVec1.size() > tempVec2.size()){
//        for(int i =0; i < tempVec1.size(); i++){
//            for(int j = 0; j < tempVec2.size(); j++){
//                if(tempVec1[i] == tempVec2[j]){
//                    finalVec.push_back(tempVec1[i]);
//                }
//            }
//        }
//    }else{
//        for(int i =0; i < tempVec2.size(); i++){
//            for(int j = 0; j < tempVec1.size(); j++){
//                if(tempVec2[i] == tempVec1[j]){
//                    finalVec.push_back(tempVec2[i]);
//                }
//            }
//        }
//    }
    cout << searchword << " Documents Amount: " << finalVec.size() << endl;
    cout << "All Documents That Contain Both Search Words" << endl;
    for(int i =0; i < finalVec.size(); i++){
        cout << finalVec.at(i) << endl;
    }

}

void QueryEngine::orSearch(string & searchTer) {
    Porter2Stemmer::trim(searchTer);
    stringstream check(searchTer);
    string temp;
    getline(check,temp,' ');
    getline(check,temp,' ');
    Porter2Stemmer::stem(temp);
    Word& find1 = tree.getContent(temp);
    vector<string>& tempVec1 = find1.getDocs();
    getline(check,temp,' ');
    Porter2Stemmer::stem(temp);
    Word& find2 = tree.getContent(temp);
    vector<string>& tempVec2 = find2.getDocs();
    sort(tempVec1.begin(),tempVec1.end());
    sort(tempVec2.begin(),tempVec2.end());
    set_union(tempVec1.begin(),tempVec1.end(),tempVec2.begin(),tempVec2.end(),back_inserter(finalVec));
    int bigBoy = tempVec1.size() + tempVec2.size();
    cout << searchTer << " Documents Amount: " << bigBoy << endl;
    cout << "All Documents That Contain Both Search Words" << endl;
    for(int i = 0; i < finalVec.size(); i++){
        cout << finalVec.at(i) << endl;
    }


}

void QueryEngine::andNotSearch(string & termSearchy) {
    finalVec.clear();
    vector<string> wordHolder;
    Porter2Stemmer::trim(termSearchy);
    stringstream check(termSearchy);
    string temp;
    getline(check,temp,' ');
    getline(check,temp,' ');
    Porter2Stemmer::stem(temp);
    Word& find1 = tree.getContent(temp);
    vector<string>& tempVec1 = find1.getDocs();
    getline(check,temp,' ');
    Porter2Stemmer::stem(temp);
    Word& find2 = tree.getContent(temp);
    vector<string>& tempVec2 = find2.getDocs();
    getline(check,temp,' ');
    getline(check,temp,' ');
    Word& find3 = tree.getContent(temp);
    vector<string>& tempVec3 = find2.getDocs();
    sort(tempVec1.begin(),tempVec1.end());
    sort(tempVec2.begin(),tempVec2.end());
    sort(tempVec3.begin(),tempVec3.end());
    set_intersection(tempVec1.begin(),tempVec1.end(),tempVec2.begin(),tempVec2.end(),back_inserter(wordHolder));
    set_difference(wordHolder.begin(),wordHolder.end(),tempVec3.begin(),tempVec3.end(),back_inserter(finalVec));
    cout << termSearchy << " Documents Amount: " << finalVec.size() << endl;
    cout << "All Documents That Contain Both Search Words and Not the others" << endl;
    for(int i = 0; i < finalVec.size(); i++){
        cout << finalVec.at(i) << endl;
    }

}

string QueryEngine::searchPhrase(string & x) {
   if(binary_search(searchPrases.begin(),searchPrases.end(),x)){
       return x;
   }else {
       return "NULL";
   }
}

