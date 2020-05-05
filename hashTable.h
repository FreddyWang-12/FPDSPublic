#ifndef UNTITLED_HASHTABLE_H
#define UNTITLED_HASHTABLE_H
#include <iostream>
#include <functional>
#include <cstring>
#include <fstream>
#include <vector>
#include "LinkedList.h"
using namespace std;

// Uses an array that creates a hash code from a given V value,
// associates it with a given K value, and uses the given V's hashcode
// to store the given K value. Used in the query engine to store all
// authors and their associated documents.
template <class V, class K>
class hashTable {
private:
    vector<V> values; // Not used
    int size; // Size of the hash table
    int capacity; // Capacity of the hash table's array
    Linkedlist<K>* table; // Array of linked lists that use separate chaining to store K values with their associated V values
public:
    hashTable<V, K>(); // Default constructor
    ~hashTable(); // Destructor
    hashTable<V, K> (const hashTable<V, K> &copy); // Copy Constructor
    hashTable<V, K>& operator = (const hashTable<V,K> &copy); // Copy assignment operator
    void addNewKey(V val, K data); // Adds a new K value to the hashCode of a given V value
    bool emptyAt(V val); // Determines if a given place of the array is blank
    Linkedlist<K>& getDataList(V val); // Returns all K values of a given V value
    void clear(); // Clears all info from the array
    int getPositionOf(V val); // Returns the hashCode position for a given V value
    int getSize(); // Returns the hash table's size
    int getCapacity(); // Returns the array's capacity
    void printToFile(ofstream& output); // Takes all of the hash table's info and puts it onto a file
    void printToTerminal();
};
// Default constructor
template <class V, class K>
hashTable<V, K>::hashTable(){
    size = 0;
    capacity = 30000;
    table = new Linkedlist<K>[capacity];
}
// Destructor
template <class V, class K>
hashTable<V,K>::~hashTable(){
    if(table != nullptr){
        delete[] table;
    }
}
// Copy Constructor
template <class V, class K>
hashTable<V, K>::hashTable (const hashTable<V, K> &copy){
    size = copy.size;
    capacity = copy.capacity;
    table = new Linkedlist<K>[capacity];
    for(int i = 0; i < capacity; i++){
        table[i] = copy.table[i];
    }
}
// Copy assignment operator
template <class V, class K>
hashTable<V, K>& hashTable<V, K>:: operator = (const hashTable<V,K> &copy){
    size = copy.size;
    capacity = copy.capacity;
    if(table != nullptr){
        delete[] table;
    }
    table = new Linkedlist<K>[capacity];
    for(int i = 0; i < capacity; i++){
        table[i] = copy.table[i];
    }
    return *this;
}
// Adds a new K value to the hashCode of a given V value
// Thank you Eli for your advice. It really helped.
template <class V, class K>
void hashTable<V,K>::addNewKey(V val, K data){
//    if(values.empty()){
//        values.push_back(val);
//    }
//    else {
//        typename std::vector<V>::iterator ptr = find(values.begin(), values.end(), val);
//        if (*ptr != val) {
//            values.push_back(val);
//        }
//    }
    int hashCode = getPositionOf(val);
    table[hashCode].push_back(data);
    size++;
}
// Determines if a given place of the array is blank
template <class V, class K>
bool hashTable<V, K>::emptyAt(V val) {
    int hashCode = getPositionOf(val);
    if(table[hashCode].isEmpty()){
        return true;
    }
    return false;
}
// Returns all K values of a given V value
template <class V, class K>
Linkedlist<K>& hashTable<V,K>:: getDataList(V val){
    int hashCode = getPositionOf(val);
    return table[hashCode];
}
// Returns the hashCode position for a given V value
template <class V, class K>
int hashTable<V,K>::getPositionOf(V val){
    hash<V> hashValue;
    int hashCode = hashValue(val)%capacity;
    return hashCode;
}
// Clears all info from the array
template <class V, class K>
void hashTable<V,K>::clear(){
    if(table != nullptr){
        delete[] table;
    }
    table = new Linkedlist<K>[capacity];
}
// Returns the hash table's size
template <class V, class K>
int hashTable<V,K>::getSize() {
    return size;
}
// Returns the array's capacity
template <class V, class K>
int hashTable<V,K>::getCapacity() {
    return capacity;
}
// Takes all of the hash table's info and puts it onto a file
// Source: https://docs.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=vs-2019
template <class V, class K>
void hashTable<V,K>::printToFile(ofstream& output){
    for(int i = 0; i < values.size(); i++) {
        output << '[' << values[i] << ']';
        Linkedlist<K>& ids = getDataList(values[i]);
        if(!ids.isEmpty()){
            ids.resetIter();
            output << ids.currIterValue() << ',';
            if(!ids.hasNext()){
                output << "|,";
            }
            else {
                while (ids.hasNext()) {
                    ids.nextValue();
                    if (!ids.hasNext()) {
                        output << ids.currIterValue() << ",|,";
                    } else {
                        output << ids.currIterValue() << ',';
                    }
                }
            }
        }
        output << endl;
    }
}
//template <class V, class K>
//void hashTable<V,K>::printToTerminal(){
//    for(int i = 0; i < values.size(); i++) {
//        cout << '[' << values[i] << ']';
//        LinkedList<K>& ids = getDataList(values[i]);
//        if(!ids.isEmpty()){
//            for (int i = 0; i < ids.getSize(); i++) {
//                if (!ids.hasNext()) {
//                    cout << ids.currIterValue() << ",|,";
//                } else {
//                    cout << ids.currIterValue() << ',';
//                    ids.nextValue();
//                }
//            }
//        }
//    }
//}
#endif //UNTITLED_HASHTABLE_H