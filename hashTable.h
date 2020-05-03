#ifndef UNTITLED_HASHTABLE_H
#define UNTITLED_HASHTABLE_H
#include <iostream>
#include <functional>
#include <cstring>
#include <fstream>
#include <vector>
#include "LinkedList.h"
using namespace std;
template <class V, class K>
class hashTable {
private:
    vector<V> values;
    int size;
    int capacity;
    LinkedList<K>* table;
public:
    hashTable<V, K>();
    ~hashTable();
    hashTable<V, K> (const hashTable<V, K> &copy);
    hashTable<V, K>& operator = (const hashTable<V,K> &copy);
    void addNewKey(V val, K data);
    bool emptyAt(V val);
    LinkedList<K>& getDataList(V val);
    void clear();
    int getPositionOf(V val);
    int getSize();
    int getCapacity();
    void printToFile(ofstream& output);
    void printToTerminal();
};
template <class V, class K>
hashTable<V, K>::hashTable(){
    size = 0;
    capacity = 10000;
    table = new LinkedList<K>[capacity];
}
template <class V, class K>
hashTable<V,K>::~hashTable(){
    if(table != nullptr){
        delete[] table;
    }
}
template <class V, class K>
hashTable<V, K>::hashTable (const hashTable<V, K> &copy){
    size = copy.size;
    capacity = copy.capacity;
    table = new LinkedList<K>[capacity];
    for(int i = 0; i < capacity; i++){
        table[i] = copy.table[i];
    }
}
template <class V, class K>
hashTable<V, K>& hashTable<V, K>:: operator = (const hashTable<V,K> &copy){
    size = copy.size;
    capacity = copy.capacity;
    if(table != nullptr){
        delete[] table;
    }
    table = new LinkedList<K>[capacity];
    for(int i = 0; i < capacity; i++){
        table[i] = copy.table[i];
    }
    return *this;
}
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
    table[hashCode].add(data);
    size++;
}
template <class V, class K>
bool hashTable<V, K>::emptyAt(V val) {
    int hashCode = getPositionOf(val);
    if(table[hashCode].isEmpty()){
        return true;
    }
    return false;
}
template <class V, class K>
LinkedList<K>& hashTable<V,K>:: getDataList(V val){
    int hashCode = getPositionOf(val);
    return table[hashCode];
}
template <class V, class K>
int hashTable<V,K>::getPositionOf(V val){
    hash<V> hashValue;
    int hashCode = hashValue(val)%capacity;
    return hashCode;
}
template <class V, class K>
void hashTable<V,K>::clear(){
    if(table != nullptr){
        delete[] table;
    }
    table = new LinkedList<K>[capacity];
}
template <class V, class K>
int hashTable<V,K>::getSize() {
    return size;
}
template <class V, class K>
int hashTable<V,K>::getCapacity() {
    return capacity;
}


template <class V, class K>
void hashTable<V,K>::printToFile(ofstream& output){
    for(int i = 0; i < values.size(); i++) {
        output << '[' << values[i] << ']';
        LinkedList<K>& ids = getDataList(values[i]);
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