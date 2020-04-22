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


void DocumentParser::tokenization() {
    stringstream check(allDocText);
    while(!check.eof()){
        getline(check,temp,' ');
        if(findInStopWord(temp) || temp.empty()){
            continue;
        }else{
//            matterWords += " " + temp;
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



