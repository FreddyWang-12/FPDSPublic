//
// Created by Frederick Wang on 4/11/20.
//

#ifndef UNTITLED_HASHTABLE_H
#define UNTITLED_HASHTABLE_H
#include <iostream>
#include <functional>
#include "LinkedList.h"
using namespace std;

template <class V, class K>
class hashTable {
    struct key{
        V value;
        K data;
        key(){
            value = -1;
            data = -1;
        }
        key(V newVal, K newData){
            value = newVal;
            data = newData;
        }
        bool operator == (const key& other){
            if(value == other.value && data == other.data){
                return true;
            }
            return false;
        }
    };

private:
    int size;
    int capacity;
    LinkedList<key>* table;

public:
    hashTable<V, K>();
    ~hashTable();
    hashTable<V, K> (const hashTable<V, K> &copy);
    hashTable<V, K>& operator = (const hashTable<V,K> &copy);

    void addNewKey(V val, K data);
    bool findKey(V val);
    void deleteKey(V val);
    K getData(V val);
    void resize();
    void clear();
    int getPositionOf(V val);
    K findGivenData(V val, K data);
    int getSize();
    int getCapacity();
};

template <class V, class K>
hashTable<V, K>::hashTable(){
    size = 0;
    capacity = 2000;
    table = new LinkedList<key>[capacity];
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
    table = new LinkedList<key>[capacity];
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
    table = new LinkedList<key>[capacity];
    for(int i = 0; i < capacity; i++){
        table[i] = copy.table[i];
    }
    return *this;
}

template <class V, class K>
void hashTable<V,K>::addNewKey(V val, K data){
//    hash<V> newHash;
//    int hasCode = newHash(val)%capacity;
//    table[hasCode].add(key(val,data));
    key newKey(val, data);
    hash<V> newHash;
    int hashCode = newHash(val)%capacity;

    if(table[hashCode].isEmpty()){
        table[hashCode].add(newKey);
    }
    else {
        table[hashCode].add(newKey);
    }
    size++;
//    if(this->findKey(val)){
//        cout << "TRUE";
//    }else{
//        cout << "FALSE";
//    }
}

template <class V, class K>
bool hashTable<V, K>::findKey(V val) {
    hash<V> newHash;
    int hashCode = newHash(val)%capacity;
    if(table[hashCode].isEmpty()){
        return false;
    }
    else{
        if(table[hashCode].firstValue().value == val){
            return true;
        }
        while(table[hashCode].currIterValue().value != val){
            table[hashCode].nextValue();
            if(table[hashCode].firstValue().value == val){
                return true;
            }
        }
    }
    return false;
}

template <class V, class K>
K hashTable<V,K>::getData(V val){
    string noWord = "Negative";
    hash<V> newHash;
    int hashCode = newHash(val)%capacity;
    if(table[hashCode].isEmpty()){
        return noWord;
    }
    else{
        if(table[hashCode].firstValue().value == val){
            return table[hashCode].currIterValue().data;
        }
        while(table[hashCode].currIterValue().value != val){
            table[hashCode].nextValue();
            if(table[hashCode].firstValue().value == val){
                return table[hashCode].currIterValue().data;
            }
        }
    }
    return noWord;
}

template <class V, class K>
void hashTable<V,K>::deleteKey(V val) {
    hash<V> newHash;
    int hashCode = newHash(val)%capacity;
    if(!table[hashCode].isEmpty()){
        if(table[hashCode].firstValue().value == val){
            table[hashCode].deleteValue(table[hashCode].firstValue());
            size--;
        }
        else {
            table[hashCode].resetIter();
            while (table[hashCode].currIterValue().value != val && table[hashCode].hasNext()){
                table[hashCode].nextValue();
                if(table[hashCode].currIterValue().value == val){
                    table[hashCode].deleteValue(table[hashCode].currIterValue());
                    size--;
                    break;
                }
            }
        }
    }
}

template <class V, class K>
int hashTable<V,K>::getPositionOf(V val){
    hash<V> hashValue;
    int hashCode = hashValue(val)%capacity;
    return hashCode;
}

template <class V, class K>
K hashTable<V,K>::findGivenData(V val, K data){
    int hashCode = getPositionOf(val);
    if(table[hashCode].isEmpty()){
        cout << "No Value Here" << endl;
        return -1;
    }
    table[hashCode].resetIter();
    if(table[hashCode].currIterValue().data == data && table[hashCode].currIterValue().value == val){
        return table[hashCode].firstValue().data;
    }
    while(table[hashCode].hasNext()){
        table[hashCode].nextValue();
        if(table[hashCode].currIterValue().data == data && table[hashCode].currIterValue().value == val){
            return table[hashCode].currIterValue().data;
        }
    }
    cout << "Data not found" << endl;
    return -1;
}

template <class V, class K>
void hashTable<V,K>::resize(){
    key* temp = new key[capacity * 2];
    for(int i = 0; i < capacity; i++){
        temp[i] = table[i];
    }

    capacity *= 2;
    delete[] table;
    table = temp;
}

template <class V, class K>
void hashTable<V,K>::clear(){
    if(table != nullptr){
        delete[] table;
    }
    table = new key[capacity];
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