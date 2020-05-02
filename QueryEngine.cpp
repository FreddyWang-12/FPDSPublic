#include "QueryEngine.h"


QueryEngine::QueryEngine() {}

QueryEngine::QueryEngine(QueryEngine &data) {
    userSearch = data.userSearch;
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
    while(count != 20){
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
            d.setupVecofWords();
            if (tree.isEmpty()) {
                d.initialAdditonToAVLTree(tree);
            } else {
                d.insertIntoAVLTree(tree);
            }
            d.initialAuthorInserttoHashTable(tableofHash);
            d.clearVector();
            count++;
        }
        dirp = readdir(dp);
    }
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
    for(auto it = begin(finalVec); it != end(finalVec); ++it){
        cout << it->data() << endl;
    }
}

void QueryEngine::outputTree() {
    tree.printerFunc();
}

void QueryEngine::outputTreetoFile() {
    ofstream out;
    out.open("output.txt");
    if(!out){
        cout << "Output.txt could not open." << endl;
    }else{
        tree.printtofileLVLFUNC(out);
    }
    out.close();
}

void QueryEngine::getTreeFromFile() {
    ifstream into;
    into.open("output.txt");
    if(!into){
        cout << "Could not Inserte information into AVLTree from output.txt file!" << endl;
    }
    vector<string> tempVec;
//    char buffer[60];
//    char word[50];
    while(!into.eof()){
        char* word = new char[50];
        char* buffer = new char[60];
        into.getline(word,50,'[');
        into.getline(word,50,']');
        into.getline(buffer,50,',');
        bool haspip = false;
            while(haspip == false){
                for(int i =0; i < 50; i++) {
                    if (buffer[i] == '|') {
                        haspip = true;
                        break;
                    }

                }
                if(haspip == false) {
                    tempVec.push_back(buffer);
                    into.getline(buffer, 50, ',');
                }
            }
        Word* temp = new Word(word,tempVec);
        tree.addNode(*temp);
        tempVec.clear();
        delete temp;
        delete[] word;
        delete[] buffer;
    }

    into.close();
}

