#include <iostream>
#include <vector>
#include "QueryEngine.h"
#include "chrono"
using namespace std;
using namespace std::chrono;
vector<int> checker;
int choice;
int main(int argc, char* argv[]) {
    auto start = high_resolution_clock::now();
    cout << "Welcome to the Covid-19 Search Engine!" << endl;
    bool showMenu = true;
    QueryEngine engine;
//    engine.getDirectoryandParse(argv[1]);
//    engine.getTreeFromFile();
//    engine.getDocTreeFromFile();
//    string search = argv[2];
//    engine.searchQuery(search);
    string searchTerm;
    while(showMenu){
        cout << "Press 1 to Re-parse all files." << endl;
        cout << "Press 2 to Re-Output Data Structures to Files" << endl;
        cout << "Press 3 to read from inverted index. " << endl;
        cout << "Press 4 to search files." << endl;
        cout << "Press 5 to print out statistics." << endl;
        cout << "Press 6 to exit program." << endl;
        cout << "Enter Choice: ";
        cin >> choice;
        checker.push_back(choice);
        if((choice != 1) && (choice != 2) && (choice != 3) && (choice != 4) && (choice != 5) ){
            cout << "Invalid Entry Please Enter a Valid Choice: ";
            cin >> choice;
            checker.push_back(choice);
        }else if(choice == 6){
            showMenu = false;
        }else if (choice == 1){
            cout << "Loading..... Takes about 2 to 4 minutes... Thank you for your patience." << endl;
            engine.getDirectoryandParse(argv[1]);
        }else if(choice == 2){
            std::vector<int>::iterator ittter;
            std::vector<int>::iterator ittterr;
            ittter = find(checker.begin(),checker.end(),1);
            ittterr = find(checker.begin(),checker.end(),2);
            if(ittter != checker.end() || ittterr != checker.end()) {
                engine.outputTreetoFile();
            }else{
                cout << "In Order to output to inverted index file you must parse documents first." << endl;
                checker.clear();
                continue;
            }
        }else if (choice == 3){
            std::vector<int>::iterator ittter;
            ittter = find(checker.begin(),checker.end(),1);
            if(ittter != checker.end()) {
                engine.getTreeFromFile();
                engine.getDocTreeFromFile();
                engine.getAuthorsQuick(argv[1]);
            }else{
                cout << "In Order to get data from inverted index files you must parse document first." << endl;
                checker.clear();
                continue;
            }
        }else if(choice == 4){
            std::vector<int>::iterator it;
            std::vector<int>::iterator itter;
            it = find(checker.begin(),checker.end(),1);
            itter = find(checker.begin(),checker.end(),3);
            if(it != checker.end() || itter != checker.end()){
                engine.searchMenue();
            }else{
                cout << "In order to search you have to parse the documents or read for the inverted index. " << endl;
                checker.clear();
                continue;
            }
        }else if( choice == 5){
            engine.statisticsPrint();
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop-start);
    cout << "Time Take For Program: " << duration.count() << " seconds " << endl;

}
