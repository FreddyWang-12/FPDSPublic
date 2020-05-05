#include "QueryEngine.h"
// Takes in a query string, parses it, and
// Finds results of documents based on it. Stores
// all words and documents on AVL Trees and all
// author info on a hash table

// Default constructor
QueryEngine::QueryEngine() {}
//Copy Constructor
QueryEngine::QueryEngine(QueryEngine &data) {
    userSearch = data.userSearch;
}
//Grabs an author and his/her info from the author hash table
void QueryEngine::getAuthorsQuick(char* dir){
    DocumentParser d;
    ofstream out;
    string filepath = dir;
    string directory = dir;
    DIR *dp;
    struct dirent *dirp;
    struct stat filestat;
    dp = opendir(dir);
    if(dp == NULL){
        cout << "Error("<< errno <<") opening " << dir << endl;
    }
    int count = 0;
    dirp = readdir(dp);
    while(dirp) {
        filepath = directory + "/" + dirp->d_name;
        string sha = dirp->d_name;
        string extension;
        if (strlen(sha.c_str()) > 4) {
            extension = sha.substr(sha.length() - 5);
        }
        if (extension == ".json") {
            if (stat(filepath.c_str(), &filestat)) continue;
            if (S_ISDIR(filestat.st_mode)) continue;
            d.getAuthorQuickey(filepath);
            d.authorIntoHashReParse(tableofHash);
        }
        dirp = readdir(dp);
    }
    closedir(dp);
}

// Takes a directory of json files, parses them, and then stores their info on the AVL Trees and hahs tables
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
//    while(count != 100){
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
            d.createDocOBJ(docTree);
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

//Takes a query search and finds all documents associated with that search
void QueryEngine::searchQuery(string &query) {
    map<string,int> bigboy;
    multimap<int,string,greater<int>> holder;
    vector<vector<string>> doubleVeccy;
    vector<string> interSectVec;
    finalVec.clear();
    vector<string> finalVecTemper;
    Porter2Stemmer::trim(query);
    stringstream parse(query);
    string temp;
    int count = 0;
    getline(parse, temp, ' ');
    if(temp == "and"){
        vector<string> tempFinal;
        while(getline(parse, temp, ' ') && temp != "author" && temp != "not"){
            Porter2Stemmer::stem(temp);
            Word& find = tree.getContent(temp);
            vector<string>& tempVecIDs = find.getDocs();
            vector<int> tempVecFreq = calculateIDF(find);
            for(int i = 0; i < tempVecIDs.size(); i++){
                if(bigboy.find(tempVecIDs[i].c_str()) != bigboy.end()){
                    bigboy[tempVecIDs[i]] += tempVecFreq[i];
                }else{
                    bigboy[tempVecIDs[i]] = tempVecFreq[i];
                }
            }
            doubleVeccy.push_back(tempVecIDs);
            interSectVec = getIntersection(doubleVeccy);
                for(int i= 0; i< interSectVec.size(); i++){
                    string tempid = bigboy.find(interSectVec[i])->first;
                    int tempFre = bigboy.find(interSectVec[i])->second;
                    holder.insert(make_pair(tempFre,tempid));
            }
        }
    }
    else if(temp == "or"){
        vector<string> tempFinal;
        while(getline(parse, temp, ' ') && temp != "author" && temp != "not") {
            Porter2Stemmer::stem(temp);
            Word &find = tree.getContent(temp);
            vector<string> &tempVecIDs = find.getDocs();
            vector<int> tempVecFreq = calculateIDF(find);
            for(int i = 0; i < tempVecIDs.size(); i++){
                if(bigboy.find(tempVecIDs[i].c_str()) != bigboy.end()){
                    bigboy[tempVecIDs[i]] += tempVecFreq[i];
                }else{
                    bigboy[tempVecIDs[i]] = tempVecFreq[i];
                }
            }
            doubleVeccy.push_back(tempVecIDs);
            for (int i = 1 ; i < doubleVeccy.size() ; i++)
            {
                sort(doubleVeccy[i].begin(), doubleVeccy[i].end());
            }
            map<string,int>::iterator itter;
            for(itter = bigboy.begin(); itter != bigboy.end(); itter++){
                holder.insert(make_pair(itter->second,itter->first));
            }
        }
    }
    else{
        Porter2Stemmer::stem(temp);
        Word& find = tree.getContent(temp);
        vector<string>& tempVecIDs = find.getDocs();
        vector<int> tempVecFreq = calculateIDF(find);
        for(int i = 0; i < tempVecIDs.size(); i++){
            holder.insert(make_pair(tempVecFreq[i],tempVecIDs[i]));
        }
        getline(parse, temp, ' ');
        if(temp == "author"){
            for(int i =0; i < tempVecIDs.size(); i++){
                bigboy.insert(make_pair(tempVecIDs[i],tempVecFreq[i]));
            }
        }
    }
    if(temp == "not"){
        holder.clear();
        vector<string> tempFinal;
        while(getline(parse, temp, ' ') && temp != "author") {
            Porter2Stemmer::stem(temp);
            Word &find = tree.getContent(temp);
            vector<string> &tempVec = find.getDocs();
            for(int i = 0; i < tempVec.size(); i++){
                if(bigboy.find(tempVec[i]) != bigboy.end()) {
                    map<string, int>::iterator itter;
                    itter = bigboy.find(tempVec.at(i));
                    bigboy.erase(itter);
                }else{
                    continue;
                }
            }
            map<string,int>::iterator itter;
            for(itter = bigboy.begin(); itter != bigboy.end(); itter++){
                holder.insert(make_pair(itter->second,itter->first));
            }
        }
    }
    if(temp == "author"){
        getline(parse, temp, ' ');
        multimap<int,string,greater<int>> forAuthor;
        Porter2Stemmer::stem(temp);
        if(!tableofHash.emptyAt(temp)) {
            vector<string> tempVec;
            Linkedlist<string>& docs = tableofHash.getDataList(temp);
            for(int i = 0; i < docs.size(); i++){
                tempVec.push_back(docs[i]);
            }
            for(int j = 0; j < tempVec.size(); j++){
                if(bigboy.find(tempVec[j]) != bigboy.end()) {
                    map<string,int >::iterator itter;
                    itter = bigboy.find(tempVec.at(j));
                    forAuthor.insert(make_pair(itter->second,itter->first));
                }else{
                    continue;
                }
            }
        }
        holder = forAuthor;
    }
    auto iter = holder.begin();
    int counter = 0;
    cout << "You search for: " << query << endl;
    while(counter != 15) {
            DocumentOBJ temp = docTree.getDocContent(iter->second);

            for (int i = 0; i < 20; i++) {
                cout << "-";
            }
            cout << endl;
            cout << "[" << counter+1 << "]" << endl;
            cout << "Title: " << temp.getTitle() << endl;
            cout << "Authors: ";
            temp.printAuthors();
            cout << "Doc-ID: " << temp.getID() << endl;
            for (int i = 0; i < 20; i++) {
                cout << "-";
            }
            cout << endl;
//        cout << (*iter).first << "," << (*iter).second << endl;
            counter++;
            iter++;
    }
    parse.clear();
    bigboy.clear();
    holder.clear();
}

// Outputs the word AVL Tree
void QueryEngine::outputTree() {
    tree.printerFunc();
}
//Puts all of the word AVL Tree's data into an output file
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
//Grabs that output file and repopulates the word AVL Tree
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
                    if(buffer[0] != '|') {
                        int x = atoi(buffer);
                        tempVecFreq.push_back(x);
                        into.getline(buffer, 50, ',');
                    }else{
                        into.getline(buffer, 50, ',');
                    }
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
//Grabs that output file and repopulates the documentOBJ AVL Tree
void QueryEngine::getDocTreeFromFile() {
    ifstream into;
    into.open("outputDoc.txt");
    if(!into){
        cout << "Could not open up outputDoc.txt to insert back into avl tree!" << endl;
    }
    vector<string> tempV;
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
                tempV.push_back(buffer);
                into.getline(buffer,1000,',');
            }
        }
        DocumentOBJ* docOb = new DocumentOBJ(id,title,tempV);
//        cout << docOb->getID() << endl;
//        cout << docOb->getTitle();
//        docOb->printAuthors();
        docTree.addNode(*docOb);
        tempV.clear();
        delete docOb;
        delete[] id;
        delete[] title;
        delete[] buffer;
    }
    into.close();
}
// Grabs the most revalent documentOBJs
multimap<int,string,greater<int>> QueryEngine::getWhatMatters(map<string, int> &mappy, vector<string> &veccey) {
        multimap<int,string,greater<int>> newMap;
        for(int i = 0; i < veccey.size(); i++){
            string id = mappy.find(veccey[i])->first;
            int freq = mappy.find(veccey[i])->second;
            newMap.insert(make_pair(freq,id));
        }
        return newMap;
}
// Calculates the frequencies for a given document and its words
vector<int> QueryEngine::calculateIDF(Word& searchWord) {
    int amountofDocs = docTree.getSize();
    int docwithTerm = searchWord.getDocSize();
    vector<int> tempFreq = searchWord.getFrequency();
    vector<int> idfVec;
    for(int i = 0; i < tempFreq.size(); i++){
        int tf = tempFreq[i];
        idfVec.push_back(tf);
    }
    return idfVec;
}

//Finds intersecting values in the "AND" part of searchQuery
///Source: https://www.geeksforgeeks.org/intersection-of-n-sets/
vector <string> QueryEngine::getIntersection(vector < vector <string> > &sets)
{
    vector <string> result;  // To store the reaultant set
    int smallSetInd = 0;  // Initialize index of smallest set
    int minSize = sets[0].size(); // Initialize size of smallest set

    // sort all the sets, and also find the smallest set
    for (int i = 1 ; i < sets.size() ; i++)
    {
        // sort this set
        sort(sets[i].begin(), sets[i].end());

        // update minSize, if needed
        if (minSize > sets[i].size())
        {
            minSize = sets[i].size();
            smallSetInd = i;
        }
    }

    map<string,int> elementsMap;

    // Add all the elements of smallest set to a map, if already present,
    // update the frequency
    for (int i = 0; i < sets[smallSetInd].size(); i++)
    {
        if (elementsMap.find( sets[smallSetInd][i] ) == elementsMap.end())
            elementsMap[ sets[smallSetInd][i] ] = 1;
        else
            elementsMap[ sets[smallSetInd][i] ]++;
    }

    // iterate through the map elements to see if they are present in
    // remaining sets
    map<string,int>::iterator it;
    for (it = elementsMap.begin(); it != elementsMap.end(); ++it)
    {
        string elem = it->first;
        int freq = it->second;

        bool bFound = true;

        // Iterate through all sets
        for (int j = 0 ; j < sets.size() ; j++)
        {
            // If this set is not the smallest set, then do binary search in it
            if (j != smallSetInd)
            {
                // If the element is found in this set, then find its frequency
                if (binary_search( sets[j].begin(), sets[j].end(), elem ))
                {
                    int lInd = lower_bound(sets[j].begin(), sets[j].end(), elem)
                               - sets[j].begin();
                    int rInd = upper_bound(sets[j].begin(), sets[j].end(), elem)
                               - sets[j].begin();

                    // Update the minimum frequency, if needed
                    if ((rInd - lInd) < freq)
                        freq = rInd - lInd;
                }
                    // If the element is not present in any set, then no need
                    // to proceed for this element.
                else
                {
                    bFound = false;
                    break;
                }
            }
        }

        // If element was found in all sets, then add it to result 'freq' times
        if (bFound)
        {
            for (int k = 0; k < freq; k++)
                result.push_back(elem);
        }
    }
    return result;
}
// Menu for the program
void QueryEngine::searchMenue() {
    string searchTerm;
    cout << "If you want to search for a single term. Type in the term you wish to search for." << endl;
    cout << "Example: Virus" << endl;
    cout << endl;
    cout << "To search multiple terms and return all documents those terms are in prefix search with OR" << endl;
    cout << "Example: OR RNA Virus" << endl;
    cout << endl;
    cout << "To search multiple terms and return documents that only contain those terms prefix search with AND" << endl;
    cout << "Example: AND Cell DNA" << endl;
    cout << endl;
    cout << "If you would like to do any of the above but exclude documents with a specific term prefix before that term NOT" << endl;
    cout << "Example: RNA NOT Cell" << endl;
    cout << "Example 2: AND RNA Cell NOT virus" <<  endl;
    cout << "Example 3: OR Cell RNA NOT Mitochondria" << endl;
    cout << endl;
    cout << "To Return documents of a specific author prefix with AUTHOR" << endl;
    cout << "Example: AUTHOR Chen" << endl;
    cout << "Example 2: virus AUTHOR jonas" << endl;
    cout << "Example 3: AUTHOR chen" << endl;
    cout << "Example 4: AND virus rna AUTHOR Freddy" << endl;
    cout << endl;
    cout << "Search:    ";
    cin.ignore();
    getline(cin,searchTerm);
    searchQuery(searchTerm);
    int choice2;
    cout << "Would You like to Search Again? " << endl;
    cout << "Press 1 for Yes or 2 for No" << endl;
    cin >> choice2;
    if(choice2 != 1 && choice2 != 2){
        cout << "Invalid Entry!" << endl;
        cout << "Press 1 to search again." << endl;
        cout << "Press 2 to return to main menu." << endl;
        cin >> choice2;
    }
    if(choice2 == 1){
        searchMenue();
    }
}
// Prints some basic statistics
void QueryEngine::statisticsPrint() {
    cout << "Program Statistics! " << endl;
    cout << "Total Number of Individual numbers indexed: " << docTree.getSize() << endl;
    cout << "Average Number of Words indexed per article: " << (tree.getSize()/docTree.getSize()) << endl;
    cout << "Total Number of unique words indexed: " << tree.getSize() << endl;
}

