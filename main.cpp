#include <iostream>
#include "QueryEngine.h"
#include "chrono"
using namespace std;
using namespace std::chrono;


int main(int argc, char* argv[]) {
    auto start = high_resolution_clock::now();
    QueryEngine engine;
    engine.getDirectoryandParse(argv[1]);
    string choice;
    string searchTerm;
    while(true) {
        cout << "Welcome to Gribble! " << endl;
        cout << "What can I do for you today? (Press 1 to Search, Press 2 to Show Statistics, Press 3 to Exit) ";
        cin >> choice;
        cout << endl;
        if(choice == "1") {
            cin.ignore();
            cout << "Search For: ";
            getline(cin, searchTerm);
            engine.searchQuery(searchTerm);
            cout << endl;
        }
        else if(choice == "2"){
            engine.printStatistics();
            cout << endl;
            cin.ignore();
        }
        else{
            cout << "Thank you for Coming!" << endl;
            break;
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop-start);
    cout << "Time Take For Program: " << duration.count() << " seconds " << endl;
}
