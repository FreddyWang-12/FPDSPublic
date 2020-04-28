#include <iostream>
#include "QueryEngine.h"
#include "chrono"
using namespace std;
using namespace std::chrono;


int main(int argc, char* argv[]) {
    auto start = high_resolution_clock::now();
    QueryEngine engine;
    engine.getDirectoryandParse(argv[1]);
    int choice;
    cout << "Welcome to the Covid-19 Search Engine!" << endl;
//    cout << "Select 1 to Search ";
//    cin >> choice;
//    if(choice == 1){
        string searchTerm;
        cout << "Search For: ";
        getline (cin,searchTerm);
        cout << searchTerm;
        int found;
        found = searchTerm.find("AUTHOR");
        if(found != string::npos){
            engine.wordanAuthorSearchWord(searchTerm);
        }
        found = searchTerm.find("AND" && "NOT");
        if(found != string::npos){
            cout << "Contains AND-NOT";
        }
        found = searchTerm.find("AND");
        if(found!=string::npos){
            cout << "Contains AND";
        }
        found = searchTerm.find("NOT");
        if(found != string::npos){
            cout << "Countains NOT";
        }
        found = searchTerm.find("OR");
        if(found != string::npos){
            cout << "Contains OR";
        }
        if(found == string::npos){
            engine.trimandstemSearchWord(searchTerm);
        }

//    }else{
//        cout << "Select 1 to Search ";
//    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop-start);
    cout << "Time Take For Program: " << duration.count() << " seconds " << endl;
}
