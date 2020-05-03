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
    dirp = readdir(dp);
    while(dirp){
//    while(count != 2000){
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
            d.addDocOBJtoTree(docTree);
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
    map<string,int> bigboy;
    multimap<int,string,greater<>> holder;
    finalVec.clear();
    vector<string> finalVecTemper;
    Porter2Stemmer::trim(query);
    stringstream parse(query);
    string temp;
    getline(parse, temp, ' ');
    if(temp == "and"){
        vector<string> tempFinal;
        while(getline(parse, temp, ' ') && temp != "author" && temp != "not"){
            Porter2Stemmer::stem(temp);
            Word& find = tree.getContent(temp);
            vector<string>& tempVecIDs = find.getDocs();
            vector<int>& tempVecFreq = find.getFrequency();
            for(int i = 0; i<tempVecIDs.size(); i++){
//                bigboy[tempVecIDs[i]] = tempVecFreq[i]++;
                bigboy[tempVecIDs[i]] += tempVecFreq[i];
            }
            sort(tempVecIDs.begin(),tempVecIDs.end());
            if(tempFinal.empty()){
                tempFinal = tempVecIDs;
            }
            else{
                sort(tempFinal.begin(), tempFinal.end());
                set_intersection(tempFinal.begin(),tempFinal.end(),tempVecIDs.begin(),tempVecIDs.end(),back_inserter(finalVecTemper));

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
        finalVecTemper = find.getDocs();
        vector<int> tempVecFreq = calculateIDF(find);
        for(int i = 0; i < finalVecTemper.size(); i++){
            holder.insert(make_pair(tempVecFreq[i],finalVecTemper[i]));
        }
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

    for(auto iter = holder.begin(); iter != holder.end(); iter++){
        cout << (*iter).first << "," << (*iter).second << endl;

    }
}


void QueryEngine::outputTree() {
    tree.printerFunc();
}

void QueryEngine::outputTreetoFile() {
    ofstream out,docout;
    docout.open("outputDoc.txt");
    out.open("output.txt");
//    hashout.open("hashtable.txt");
    if(!docout){
        cout << "outputDoc.txt could not open." << endl;
    }else{
        docTree.printtofileLVLFUNC(docout);
    }
    if(!out){
        cout << "Output.txt could not open." << endl;
    }else{
        tree.printtofileLVLFUNC(out);
    }

//    if(!hashout){
//        cout << "hashtable.txt could not open." << endl;
//    }else{
//        tableofHash.printToFile(hashout);
//    }

    docout.close();
    out.close();
//    hashout.close();
}

void QueryEngine::getTreeFromFile() {
    ifstream into;
    into.open("output.txt");
    if(!into){
        cout << "Could not Insert information into AVLTree from output.txt file!" << endl;
    }
    vector<string> tempVec;
    vector<int> tempVecFreq;
//    char buffer[60];
//    char word[50];
    while(!into.eof()){
        char* word = new char[50];
        char* buffer = new char[60];
        into.getline(word,50,'[');
        into.getline(word,50,']');
        into.getline(buffer,50,',');
        if(strlen(buffer) <= 1){
            delete[] word;
            delete[] buffer;
            break;
        }
        bool haspip = false;
        bool getFreq = false;
            while(haspip == false){
                for(int i =0; i < 6; i++) {
                    if (buffer[i] == '|') {
                        haspip = true;
                        break;
                    }
                }
                if(haspip == false) {
                    tempVec.push_back(buffer);
                    into.getline(buffer, 50, ',');
//                    cout <<  "Working";
                }
            }
            while(haspip == true){
//                into.getline(buffer,50,',');
                for(int i = 0; i < 6; i++) {
                    if (buffer[i] == '|' && buffer[i + 1] == '|') {
                        getFreq = true;
                        haspip = false;
                        break;
                    }
                }
                if(getFreq == false){
                    int x = atoi(buffer);
                    tempVecFreq.push_back(x);
                    into.getline(buffer, 50, ',');
                }
            }
        Word* temp = new Word(word,tempVec,tempVecFreq);
        tree.addNode(*temp);
        tempVec.clear();
        tempVecFreq.clear();
        delete temp;
        delete[] word;
        delete[] buffer;
    }

    into.close();
}

void QueryEngine::getDocTreeFromFile() {
    ifstream into;
    into.open("outputDoc.txt");
    if(!into){
        cout << "Could not open up outputDoc.txt to insert back into avl tree!" << endl;
    }
    vector<string> tempVec;
    while(!into.eof()){
        char* id = new char[50];
        char* title = new char[5000];
        char* buffer = new char[1000];
        into.getline(id,50,'~');
        into.getline(id,50,'~');
        into.getline(title,5000,'~');
        into.getline(title,5000,'~');
        into.getline(buffer,1000,',');
        if(strlen(buffer) == 0){
            delete[] id;
            delete[] title;
            delete[] buffer;
            break;
        }
        bool haspipes = false;
        while(haspipes == false){
            for(int i = 0; i < 4; i++){
                if(buffer[i] == '~' && buffer[i+1] == '~' && buffer[i+2] == '~'){
                    haspipes = true;
                    break;
                }
            }
            if(haspipes == false){
                tempVec.push_back(buffer);
                into.getline(buffer,1000,',');
            }
        }
        DocumentOBJ* docOb = new DocumentOBJ(id,title,tempVec);
        docTree.addNode(*docOb);
        tempVec.clear();
        delete docOb;
        delete[] id;
        delete[] title;
        delete[] buffer;
    }
    into.close();
}

multimap<int,string,greater<int>> QueryEngine::getWhatMatters(map<string, int> &mappy, vector<string> &veccey) {
        multimap<int,string,greater<int>> newMap;
        for(int i = 0; i < veccey.size(); i++){
            string id = mappy.find(veccey[i])->first;
            int freq = mappy.find(veccey[i])->second;
            newMap.insert(make_pair(freq,id));
        }
        return newMap;
}

vector<int> QueryEngine::calculateIDF(Word& searchWord) {
    int amountofDocs = 12000;
    int docwithTerm = searchWord.getDocSize();
    vector<int> tempFreq = searchWord.getFrequency();
    vector<int> idfVec;
    for(int i = 0; i < tempFreq.size(); i++){
        int tf = tempFreq.at(i);
        int idf = tf*log(amountofDocs/docwithTerm);
        idfVec.push_back(idf);
    }
    return idfVec;
}



