//
// Created by Frederick Wang on 4/28/20.
//

#ifndef UNTITLED_KEY_H
#define UNTITLED_KEY_H
#include <iostream>
#include <functional>
#include <cstring>
#include "LinkedList.h"
using namespace std;

template <class V, class K>
class key {

    public:
        V value;
        K data;
        key<K, V>(){
            value = V();
            //data = new LinkedList<K>();
        }
        key(V value, K firstData){
            this->value = value;
            data.add(firstData);
        }
        key(const key& other){
            this->value = other.value;
            this->data = other.data;
        }
        key& operator =(const key& other){
            this->value = other.value;
            this->data = other.data;
            return *this;
        }
        bool operator == (const key& other){
            if(value == other.value){
                return true;
            }
            return false;
        }

        void add(K newData){
            data.add(newData);
        }
        V& getValue(){
            return value;
        }
        LinkedList<K>& getData(){
            return data;
        }
        bool empty(){
            if(data.isEmpty()){
                return true;
            }
            return false;
        }
};
#endif //UNTITLED_KEY_H
