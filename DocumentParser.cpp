//
// Created by jonas on 4/14/2020.
//

#include "DocumentParser.h"

void DocumentParser::parseDocument(string& file) {
    FILE* fp = fopen(file.c_str(),"rb");
    char readingBuffer[3000];
    FileReadStream is(fp,readingBuffer, sizeof(readingBuffer));
    Document d;
    d.ParseStream(is);
    string text,bodytext,lastname,title;
    vector<string> formattedAutors;
    assert(d.IsObject());
    assert(d.HasMember("paper_id"));
    assert(d["paper_id"].IsString());
//    assert(d.IsObject());
    assert(d.HasMember("metadata"));
    assert(d["metadata"]["title"].IsString());
     paperid = d["paper_id"].GetString();
     title = d["metadata"]["title"].GetString();
    if(d.HasMember("abstract")){
        const Value& paper_abstract_array = d["abstract"];
        assert(d["abstract"].IsArray());
        for(SizeType i = 0; i < paper_abstract_array.Size(); i++){
            const Value& textObj = paper_abstract_array[i];

            if(textObj.HasMember("text")){
                const Value& testString = textObj["text"];
                text = text + testString.GetString();
            }

        }
    }
//    cout << text;
    if(d.HasMember("body_text")){
        const Value& body_text_array = d["body_text"];
        assert(d["body_text"].IsArray());
        for(SizeType j = 0; j < body_text_array.Size(); j++){
            const Value& body_text_OBJ = body_text_array[j];
            if(body_text_OBJ.HasMember("text")){
                const Value& body_text_String = body_text_OBJ["text"];
                bodytext = bodytext + body_text_String.GetString();
            }
        }
    }
    const Value& authors_array = d["metadata"]["authors"];
    assert(authors_array.IsArray());
    for(SizeType t = 0; t < authors_array.Size(); t++){
        const Value& authors_array_OBJ = authors_array[t];
        if(authors_array_OBJ.HasMember("last")){
            const Value& authors_last = authors_array_OBJ["last"];
            lastname = authors_last.GetString();
            if(!lastname.empty() ){
                Porter2Stemmer::trim(lastname);
                string temp = lastname;
                temp[0] = toupper(temp[0]);
                formattedAutors.push_back(temp);
                Porter2Stemmer::stem(lastname);
                lastname_author.push_back(lastname);
            }
            }
        }

    fclose(fp);
//    allDocText = title + text + bodytext;
//    Porter2Stemmer::trim(allDocText);
    createDocOBJ(formattedAutors,title);
    addStrings(title,text,bodytext);
}



void DocumentParser::getDocumentsinDirectory(string& directory) {
    ifstream fin;
    string filepath;
    DIR *dp;
    struct dirent *dirp;
    struct stat filestat;
    dp = opendir(directory.c_str());
    if(dp == NULL){
        cout << "Error("<< errno <<") opening " << directory << endl;
    }

//    while(dirp = readdir(dp)){
int count = 0;
    while(count != 1){
        dirp = readdir(dp);
        filepath = directory + "/" + dirp->d_name;
        if(stat(filepath.c_str(), &filestat)) continue;
        if(S_ISDIR(filestat.st_mode)) continue;
        string sha = dirp->d_name;
//        string get = sha.erase(sha.find("."));
//        string get = sha.erase(sha.find('.')-4);
//        if(csvreader.ifExists(get)){
            parseDocument(filepath);
//        }
        count++;
    }

    closedir(dp);
}


void DocumentParser::tokenization() {
    stringstream check(allDocText);
    string temp;
    while(!check.eof()){
        getline(check,temp,' ');
        if(findInStopWord(temp) || temp.empty() || temp.size() > 20){
            continue;
        }else{
                Porter2Stemmer::stem(temp);
                if(temp.size() > 1) {
                    ++frequency[temp];
                }
        }
    }

}

void DocumentParser::setupVecofWords() {
    map<string,int>::iterator itter;
    for(itter = frequency.begin(); itter != frequency.end(); itter++) {
        vecOfWords.emplace_back(itter->first, paperid,itter->second);
    }

}

void DocumentParser::trimTokens() {
    Porter2Stemmer::trim(allDocText);

}

void DocumentParser::clearVector() {
    vecOfWords.clear();
    lastname_author.clear();
    frequency.clear();
}

int DocumentParser::gettheFrequency(){
    int count = 0;
    for(int i = 0; i < vecOfWords.size(); i++){
        string temp = vecOfWords[i].getWord();
        stringstream get(allDocText);
        while(!get.eof()){
            if(allDocText == temp){
                count++;
            }
        }
        if(count >= 1){
            vecOfWords[i].addFrequency(count);
            count = 0;
        }
    }
}

void DocumentParser::insertIntoAVLTree(AVLTree<Word>& avl) {
    for(auto & vecOfWord : vecOfWords){
        if(avl.ifExists(vecOfWord)){
            if(!avl.getContent(vecOfWord).findDoc(paperid)){
                avl.getContent(vecOfWord).addDoc(paperid);
                map<string,int>::iterator itter;
                itter = frequency.find(vecOfWord.getWord());
                avl.getContent(vecOfWord).addFrequency(itter->second);
            }
        }else{
            avl.addNode(vecOfWord);
        }
    }
}



void DocumentParser::initialAdditonToAVLTree(AVLTree<Word> & obj) {
        for (int i = 0; i < vecOfWords.size(); i++) {
            obj.addNode(vecOfWords[i]);
        }
}


void DocumentParser::addStrings(string&a,string&b,string&c) {
    allDocText = a + b + c;
}

bool DocumentParser::findInStopWord(string& x){
    return binary_search(stopword.begin(), stopword.end(), x);
}
void DocumentParser::freeMem(){
    paperid.clear();
}

void DocumentParser::deleteAllDocText() {
    allDocText.clear();
}

void DocumentParser::initialAuthorInserttoHashTable(hashTable<string,string>& hash) {
    for(int i = 0; i < lastname_author.size(); i++){
        hash.addNewKey(lastname_author[i],paperid);
    }
}

void DocumentParser::stemtrimAuthorNames() {
    for(int i = 0; i < lastname_author.size(); i++){
        Porter2Stemmer::trim(lastname_author[i]);
        Porter2Stemmer::stem(lastname_author[i]);
    }
}

void DocumentParser::trim(std::string& word)
{
    if (word == "<s>" || word == "</s>")
        return;

    auto it
            = std::remove_if(word.begin(), word.end(), [](char ch)
            {
                return !((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == ' ');
            });

    word.erase(it, word.end());
}

void DocumentParser::createDocOBJ(vector<string>& data,string& title) {
    if(title.empty()){
        title = "NO TITLE";
    }
    if(data.empty()){
        string temp = "NO AUTHOR";
        data.push_back(temp);
    }
            trim(title);
            DocumentOBJ *tempDocOBJ = new DocumentOBJ(paperid, title, data);
            docOBJ = *tempDocOBJ;
            delete tempDocOBJ;
}

void DocumentParser::addDocOBJtoTree(AVLTree<DocumentOBJ> & docTree) {
        docTree.addNode(docOBJ);
}

void DocumentParser::addFreqToWord(AVLTree<Word>& wordTree) {
    map<string,int>::iterator itter;
    for(itter = frequency.begin(); itter != frequency.end(); itter++){
        wordTree.getContent((Word &) itter->first).addFrequency(itter->second);
    }
}

//void DocumentParser::insertIntoAVLTreeFromFile(AVLTree<Word> &avl) {
//    ifstream into;
//    into.open("output.txt");
//    if(!into){
//        cout << "Could not Inserte information into AVLTree from output.txt file!" << endl;
//    }
//
//
//    while(!into.eof()){
//        vector<string> tempVec;
//        char* word = new char[50];
//        char* buffer = new char[50];
//        into.getline(word,50,'[');
//        into.getline(word,50,']');
////        while(strcmp(buffer,"|") != 0){
//            into.getline(buffer,50,',');
//            if(strcmp(buffer,"|") != 0) {
//                tempVec.push_back(buffer);
//            }else{
//                break;
//            }
////        }
//        Word* temp = new Word(word,tempVec,tempVec);
////        vecOfWords.emplace_back(word,tempVec);
//        avl.addNode(*temp);
//        delete temp;
//        delete[] word;
//        delete[] buffer;
////        tempVec.clear();
////        vecOfWords.clear();
//    }
//    into.close();
//}

