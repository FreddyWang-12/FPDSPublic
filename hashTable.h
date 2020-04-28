//
// Created by Frederick Wang on 4/11/20.
//

#ifndef UNTITLED_HASHTABLE_H
#define UNTITLED_HASHTABLE_H
#include <iostream>
#include <functional>
#include <cstring>
#include "LinkedList.h"
using namespace std;

template <class V, class K>
class hashTable {
private:
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
};


template <class V, class K>
hashTable<V, K>::hashTable(){
    size = 0;
    capacity = 250000;
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

#endif //UNTITLED_HASHTABLE_H