#include <iostream>
#include <string>
#include "fstream"
#include "QueryEngine.h"
#include "DocumentParser.h"
#include "CSVReader.h"
#include "vector"
using namespace std;



using namespace std;

int main() {
    CSVReader reader(R"(C:\Users\jonas\Desktop\DataStructures\FinalProject\Data\metadata.csv)");
    reader.getData();
    reader.putInHashTable();
//    reader.printVector();
    DocumentParser d;
    string directory = "C:/Users/jonas/Desktop/DataStructures/FinalProject/Data/biorxiv_medrxiv/biorxiv_medrxiv/pdf_json";
    d.getDocumentsinDirectory(directory);




//QueryEngine a;
//string search = "virus AND jonas NOT ezra";
//a.prefixIndentifier(search);
}
