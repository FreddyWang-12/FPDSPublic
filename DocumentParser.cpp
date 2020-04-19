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
    assert(d.IsObject());
    assert(d.HasMember("paper_id"));
    assert(d["paper_id"].IsString());
//    assert(d.IsObject());
    assert(d.HasMember("metadata"));
    assert(d["metadata"]["title"].IsString());
     paperid = d["paper_id"].GetString();
     title = d["metadata"]["title"].GetString();
//    removeNONLettersandLowercase(title);
//    tokenization(title);
//    cout << title << endl;
//    cout << d["paper_id"].GetString() << endl;
//    cout << d["metadata"]["title"].GetString() << endl;
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
//                removeNONLettersandLowercase(bodytext);
//                tokenization(bodytext);
//                cout << bodytext << endl;
            }
        }
    }

//    this->printDocument(d);

    fclose(fp);
}


void DocumentParser::printDocument(Document& data) {
    StringBuffer bufStream;
    Writer<StringBuffer> writer(bufStream);
    data.Accept(writer);
    cout << bufStream.GetString() << endl;
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
    while(count != 3){
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

void DocumentParser::stemDoc() {
    Porter2Stemmer::stem(matterWords);
}
void DocumentParser::removeNONLettersandLowercase(string &data) {
    int tempCount = 0;
        for(int i = 0; i < data.length(); i++) {
            if(isspace(data[i])){
                continue;
            }else if(data[i] < 'A' || data[i] > 'Z' && data[i] < 'a' || data[i] > 'z'){
                data.erase(i,1);
                i--;
            }
        }
        for(char & j : data){
            j = tolower(j);
        }
}


void DocumentParser::tokenization() {
    stringstream check(allDocText);
    while(!check.eof()){
        getline(check,temp,' ');
        if(findInStopWord(temp) || temp.empty()){
            continue;
        }else{
//            matterWords += " " + temp;
            Porter2Stemmer::stem(temp);
            token.push_back(temp);
        }
    }

}



void DocumentParser::printToken() {
    for(int i = 0; i < token.size(); i++){
        cout << token[i] << endl;
    }
}

void DocumentParser::trimTokens() {
        Porter2Stemmer::trim(allDocText);

}




void DocumentParser::printStopWords() {
    for(int i = 0; i < stopwords.size(); i++){
        cout << stopwords[i] << endl;
    }
}

void DocumentParser::removeStopWords(){
    string::iterator it, iter;
for(unsigned int i = 0; i < token.size(); i++){
    for(unsigned int j = 0; j < stopwords.size(); j++){
        if(token.at(i) == stopwords.at(j)){
            token.at(i).erase();
        }else{
            continue;
        }
    }
}
}


void DocumentParser::cleanVector() {
 vector<string> temp;
    for(int i = 0; i < token.size(); i++){
        if(!token[i].empty()){
            temp.push_back(token[i]);
        }
    }
    token = temp;
}

void DocumentParser::clearVector() {
    vecOfWords.clear();
}


void DocumentParser::insertIntoAVLTree(AVLTree<Word>& avl) {
    for(int i = 0; i < vecOfWords.size(); i++){
        if(avl.ifExists(vecOfWords[i])){
            if(avl.getContent(vecOfWords[i]).findDoc(paperid) != paperid){
                avl.getContent(vecOfWords[i]).addDoc(paperid);
            }
        }else{
            avl.addNode(vecOfWords[i]);
        }
    }
}


void DocumentParser::tokenToWords() {
    for(int i = 0; i < token.size(); i++){
        vecOfWords.emplace_back(token[i],paperid);
    }
}


void DocumentParser::initialAdditonToAVLTree(AVLTree<Word> & obj) {
        for (auto & vecOfWord : vecOfWords) {
            obj.addNode(vecOfWord);
        }
}

int DocumentParser::getTokenVecSize() {
    return token.size();
}

void DocumentParser::printallDocText() {
    cout << allDocText << endl;
}


void DocumentParser::addStrings() {
    allDocText = title + text + bodytext;
}

bool DocumentParser::findInStopWord(string& x){
    for(const auto & i : stopword){
        if(x == i){
            return true;
        }
    }
    return false;
}
void DocumentParser::freeMem(){
    paperid.clear();
}

void DocumentParser::deleteAllDocText() {
    allDocText.clear();
    text.clear();
    bodytext.clear();
    title.clear();
}


void DocumentParser::clearTokenVec() {
    token.clear();
}