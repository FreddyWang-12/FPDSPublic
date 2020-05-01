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
    string title,text,bodytext;
    string lastname{};
    assert(d.IsObject());
    assert(d.HasMember("paper_id"));
    assert(d["paper_id"].IsString());
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
            lastname_author.push_back(lastname);
        }
    }

    fclose(fp);
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
    while(count != 100){
        dirp = readdir(dp);
        filepath = directory + "/" + dirp->d_name;
        if(stat(filepath.c_str(), &filestat)) continue;
        if(S_ISDIR(filestat.st_mode)) continue;
        string sha = dirp->d_name;
        parseDocument(filepath);
        count++;
    }
    closedir(dp);
}


void DocumentParser::tokenization() {
    stringstream check(allDocText);
    string temp;
    while(!check.eof()){
        getline(check,temp,' ');
        if(findInStopWord(temp) || temp.empty()){
            continue;
        }else{
            ++wordFreq[temp];
            Porter2Stemmer::stem(temp);
            vecOfWords.emplace_back(temp,paperid);
        }
    }
}

void DocumentParser::trimTokens() {
    Porter2Stemmer::trim(allDocText);

}

void DocumentParser::clearVector() {
    vecOfWords.clear();
    lastname_author.clear();
}


void DocumentParser::insertIntoAVLTree(AVLTree<Word>& avl) {
    for(auto & vecOfWord : vecOfWords){
        if(avl.ifExists(vecOfWord)){
            if(!avl.getContent(vecOfWord).findDoc(paperid)){
                avl.getContent(vecOfWord).addDoc(paperid);
            }
        }else{
            avl.addNode(vecOfWord);
        }
    }
}



void DocumentParser::initialAdditonToAVLTree(AVLTree<Word> & obj) {
    for (auto & vecOfWord : vecOfWords) {
        obj.addNode(vecOfWord);
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

void DocumentParser::addUniqueWords(int &unique) {
    unique += vecOfWords.size();
}

void DocumentParser::sortWordFreq() {
    copy(wordFreq.begin(), wordFreq.end(), back_inserter(sortedWordFreq));
    sort(sortedWordFreq.begin(), sortedWordFreq.end(), sorter);
}

void DocumentParser::printMostFreqWords(){
    for(int i = 0; i < 50; i++){
        cout << sortedWordFreq[i].first << endl;
    }
}

vector<pair<string, int>>& DocumentParser::getSortFreqWords(){
    return sortedWordFreq;
}