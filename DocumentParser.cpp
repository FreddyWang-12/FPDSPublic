//
// Created by jonas on 4/14/2020.
//

#include "DocumentParser.h"
// Takes a document from the directory, creates word objects and
// documentOBJs from it, and stores them into the inverted indexes
// in the query engine


// Opens up a file with a given name (string&) and parses all of its information
void DocumentParser::parseDocument(string& file) {
    FILE* fp = fopen(file.c_str(),"rb");
    char readingBuffer[3000];
    FileReadStream is(fp,readingBuffer, sizeof(readingBuffer));
    Document d;
    d.ParseStream(is);
    string text,bodytext,lastname;
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
                allAuthors[lastname]++;
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
//    createDocOBJ(formattedAutors,title);
    addStrings(title,text,bodytext);
}
//Find an author in the document
void DocumentParser::getAuthorQuickey(string& file) {
    FILE* fp = fopen(file.c_str(),"rb");
    char readingBuffer[3000];
    FileReadStream is(fp,readingBuffer, sizeof(readingBuffer));
    Document d;
    d.ParseStream(is);
    vector<string> lastnameVec;
    string lastname;
    assert(d.IsObject());
    assert(d.HasMember("paper_id"));
    assert(d["paper_id"].IsString());
    paperid = d["paper_id"].GetString();
    const Value& authors_array = d["metadata"]["authors"];
    assert(authors_array.IsArray());
    for(SizeType t = 0; t < authors_array.Size(); t++){
        const Value& authors_array_OBJ = authors_array[t];
        if(authors_array_OBJ.HasMember("last")){
            const Value& authors_last = authors_array_OBJ["last"];
            lastname = authors_last.GetString();
            if(!lastname.empty() ){
                Porter2Stemmer::trim(lastname);
                Porter2Stemmer::stem(lastname);
                lastname_author.push_back(lastname);
            }
        }
    }
    fclose(fp);

}
// Stores all author information into the AVL Tree
void DocumentParser::authorIntoHashReParse(hashTable<string,string>& hasheyTable){
    for(int i = 0; i < lastname_author.size(); i++){
        hasheyTable.addNewKey(lastname_author[i],paperid);
    }
    lastname_author.clear();
}

// Trims and stems all unique words with a parsed document
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
                    if(frequency.find(temp) != frequency.end()){
                        ++frequency[temp];
                    }else{
                        frequency[temp] = 1;
                    }

                }
        }
    }

}
// Creates a series of word objects and places them in vecOfWords
void DocumentParser::setupVecofWords() {
    map<string,int>::iterator itter;
    for(itter = frequency.begin(); itter != frequency.end(); itter++) {
        vecOfWords.emplace_back(itter->first, paperid,itter->second);
    }

}
// Trims all unique words
void DocumentParser::trimTokens() {
    Porter2Stemmer::trim(allDocText);

}
// Clears all paper ids from "paperid"
void DocumentParser::clearVector() {
    vecOfWords.clear();
    lastname_author.clear();
    frequency.clear();
    formattedAutors.clear();
}
// Grabs the frequency of a given word inside the document
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
// Inserts a new word object into the word AVL Tree
void DocumentParser::insertIntoAVLTree(AVLTree<Word>& avl) {
    for(auto & vecOfWord : vecOfWords){
        if(avl.ifExists(vecOfWord)){
            if(!avl.getContent(vecOfWord).findDoc(paperid)){
                avl.getContent(vecOfWord).addDoc(paperid);
                map<string,int>::iterator itter;
                itter = frequency.find(vecOfWord.getWord());
//                int feq = itter->second;
                avl.getContent(vecOfWord).addFrequency(itter->second);
            }
        }else{
            avl.addNode(vecOfWord);
        }
    }
}


// Initial insertion of word objects into the word AVL Tree
void DocumentParser::initialAdditonToAVLTree(AVLTree<Word> & obj) {
        for (int i = 0; i < vecOfWords.size(); i++) {
            obj.addNode(vecOfWords[i]);
        }
}

// Combines all of the text within a document and stores them in "allDocText"
void DocumentParser::addStrings(string&a,string&b,string&c) {
    allDocText = a + b + c;
}
// Determines if a word is a given stop word
bool DocumentParser::findInStopWord(string& x){
    return binary_search(stopword.begin(), stopword.end(), x);
}
// Frees all memory from all containers
void DocumentParser::freeMem(){
    paperid.clear();
}
// Deletes all document text for later usage
void DocumentParser::deleteAllDocText() {
    allDocText.clear();
}
// Adds authors to the hash table
void DocumentParser::initialAuthorInserttoHashTable(hashTable<string,string>& hash) {
    for(int i = 0; i < lastname_author.size(); i++){
        hash.addNewKey(lastname_author[i],paperid);
    }
}

// Trims and stems all authors' name in a given document
void DocumentParser::stemtrimAuthorNames() {
    for(int i = 0; i < lastname_author.size(); i++){
        Porter2Stemmer::trim(lastname_author[i]);
        Porter2Stemmer::stem(lastname_author[i]);
    }
}
//Trim a given term
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
// Creates a documentOBJ out of a given document
void DocumentParser::createDocOBJ(AVLTree<DocumentOBJ>& yep) {
    if(title.empty()){
        title = "NO TITLE";
    }
    if(formattedAutors.empty()){
        string temp = "NO AUTHOR";
        formattedAutors.push_back(temp);
    }
            trim(title);
            auto *tempDocOBJ = new DocumentOBJ(paperid, title, formattedAutors);
            yep.addNode(*tempDocOBJ);
            delete tempDocOBJ;
}

//void DocumentParser::addDocOBJtoTree(AVLTree<DocumentOBJ> & docTree) {
//        docTree.addNode(docOBJ);
//}

// Adds a frequency to a given word in the word AVL Tree
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

