#include <iostream>
#include <string>
#include "fstream"
#include "QueryEngine.h"
#include "DocumentParser.h"
#include "CSVReader.h"
#include "vector"
using namespace std;


int main() {
//    CSVReader reader(R"(C:\Users\jonas\Desktop\DataStructures\FinalProject\Data\metadata-cs2341)");
//    reader.getData();
//    reader.putInHashTable();
//    reader.printVector();
    DocumentParser d;
    string directory = "C:/Users/jonas/Desktop/DataStructures/FinalProject/Data/cs2341_data";
    d.getDocumentsinDirectory(directory);
    d.printToken();



//QueryEngine a;
//string search = "virus AND jonas NOT ezra";
//a.prefixIndentifier(search);
}
