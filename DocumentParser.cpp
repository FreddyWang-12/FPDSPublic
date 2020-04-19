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
//                removeNONLettersandLowercase(text);
//                tokenization(text);
//                cout << text << endl;
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
    while(getline(check,temp,' ')){
        if(findInStopWord(temp) || temp.empty()){
            continue;
        }else{
            stemTokens();
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
        Porter2Stemmer::trim(title);

        Porter2Stemmer::trim(text);

        Porter2Stemmer::trim(bodytext);

}

void DocumentParser::stemTokens() {
            Porter2Stemmer::stem(temp);
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
    token.clear();
    vecOfWords.clear();
}


void DocumentParser::insertIntoAVLTree(AVLTree<Word>& avl, Word& obj) {
    for(int i = 0; i < token.size(); i++){
        if(avl.ifExists(obj = Word(token[i],paperid))){
            if(avl.getContent(obj).findDoc(paperid) != paperid){
                avl.getContent(obj).addDoc(paperid);
            }
        }else{
            avl.addNode(obj);
        }
    }
}


void DocumentParser::tokenToWords(Word& obj) {
    for(int i = 0; i < token.size(); i++){
        obj = Word(token[i],paperid);
        vecOfWords.push_back(obj);
    }
}


void DocumentParser::initialAdditonToAVLTree(AVLTree<Word> & obj, Word & words) {
    if(obj.isEmpty()) {
        for (int i = 0; i < token.size(); i++) {
            obj.addNode(words = Word(token[i],paperid));
        }
    }else{
        insertIntoAVLTree(obj,words);
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
    for(int i = 0; i < 1160; i++){
        if(x == stopword[i]){
            return true;
        }
    }
    return false;
}
void DocumentParser::freeMem(){
    allDocText.clear();
    text.clear();
    bodytext.clear();
    title.clear();
    paperid.clear();
}