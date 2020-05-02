#include <iostream>
#include "QueryEngine.h"
#include "chrono"
using namespace std;
using namespace std::chrono;


int main(int argc, char* argv[]) {
    auto start = high_resolution_clock::now();
    QueryEngine engine;
//    engine.getDirectoryandParse(argv[1]);
//    engine.outputTreetoFile();
    engine.getTreeFromFile();
    int choice;
    cout << "Welcome to the Covid-19 Search Engine!" << endl;
    string searchTerm = argv[2];
//    engine.searchQuery(searchTerm);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop-start);
    cout << "Time Take For Program: " << duration.count() << " seconds " << endl;
}
