#include "QueryEngine.h"


QueryEngine::QueryEngine() {}

QueryEngine::QueryEngine(QueryEngine &data) {
    userSearch = data.userSearch;
    totalUniqueWords = 0;
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
    allArticlesIndexed = 12000;
    while(count != 12000){
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
            d.addUniqueWords(totalUniqueWords);
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
    d.sortWordFreq();
    wordFreq = d.getSortFreqWords();
    closedir(dp);

}

void QueryEngine::searchQuery(string &query) {
    finalVec.clear();
    Porter2Stemmer::trim(query);
    stringstream parse(query);
    string temp;
    getline(parse, temp, ' ');
    if(temp == "and"){
        vector<string> tempFinal;
        while(getline(parse, temp, ' ') && temp != "author" && temp != "not"){
            Porter2Stemmer::stem(temp);
            Word& find = tree.getContent(temp);
            vector<string>& tempVec = find.getDocs();
            Porter2Stemmer::stem(temp);
            sort(tempVec.begin(),tempVec.end());
            if(tempFinal.empty()){
                tempFinal = tempVec;
            }
            else{
                sort(tempFinal.begin(), tempFinal.end());
                set_intersection(tempFinal.begin(),tempFinal.end(),tempVec.begin(),tempVec.end(),back_inserter(finalVec));
            }
        }
    }
    else if(temp == "or"){
        vector<string> tempFinal;
        while(getline(parse, temp, ' ') && temp != "author" && temp != "not") {
            Porter2Stemmer::stem(temp);
            Word &find = tree.getContent(temp);
            vector<string> &tempVec = find.getDocs();
            sort(tempVec.begin(), tempVec.end());
            if(tempFinal.empty()){
                tempFinal = tempVec;
            }
            else{
                sort(tempFinal.begin(), tempFinal.end());
                set_union(tempVec.begin(),tempVec.end(),tempFinal.begin(),tempFinal.end(),back_inserter(finalVec));
            }
        }
    }
    else{
        Porter2Stemmer::stem(temp);
        Word& find = tree.getContent(temp);
        finalVec = find.getDocs();
        getline(parse, temp, ' ');
    }

    if(temp == "not"){
        vector<string> tempFinal;
        while(getline(parse, temp, ' ') && temp != "author") {
            Porter2Stemmer::stem(temp);
            Word &look = tree.getContent(temp);
            vector<string> &tempVec = look.getDocs();
            sort(tempVec.begin(), tempVec.end());
            sort(finalVec.begin(), finalVec.end());
            set_difference(finalVec.begin(), finalVec.end(), tempVec.begin(), tempVec.end(),back_inserter(tempFinal));
            finalVec = tempFinal;
            tempFinal.clear();
        }
    }

    if(temp == "author"){
        getline(parse, temp, ' ');
        Porter2Stemmer::stem(temp);
        if(!tableofHash.emptyAt(temp)) {
            vector<string> tempVec;
            LinkedList<string>& docs = tableofHash.getDataList(temp);
            for (int i = 0; i < finalVec.size(); i++) {
                if (docs.findValue(finalVec.at(i))) {
                    tempVec.push_back(finalVec.at(i));
                }
            }
            finalVec = tempVec;
        }
    }

    cout << "All Documents Found with Search: " << query << endl;
    cout << "Total Documents: " << finalVec.size() << endl;
    for(int i = 0; i < 15; i++){
        cout << finalVec.at(i) << endl;
    }
}

void QueryEngine::printStatistics() {
    cout << "Total Number of Individual Articles Indexed: " << allArticlesIndexed << endl;
    cout << "Average Number of Words Indexed Per Article: " << (totalUniqueWords/allArticlesIndexed) << endl;
    cout << "Total Number of Unique Words Indexed: " << tree.getSize() << endl;
    cout << "Total Number of Unique Authors: " << tableofHash.getSize() << endl;
    cout << "Top 50 Most Frequent Words: " << endl;
    for(int i = 0; i < 50; i++){
        cout << wordFreq[i].first << endl;
    }
    //Top 50 most frequent words (after removal of stop words);
}