//
// Created by Frederick Wang on 3/26/20.
//

#ifndef S20_PA04_FLIGHTPLANNER_LINKEDLIST_H
#define S20_PA04_FLIGHTPLANNER_LINKEDLIST_H

#include <iostream>
#include <stdexcept>
using namespace std;

template<class T>
class LinkedList {
    struct node{
        T data;
        node* nextNode;
        node* prevNode;
        node(){
            nextNode = nullptr;
            prevNode = nullptr;
        }
        node(T data){
            this->data = data;
            nextNode = nullptr;
            prevNode = nullptr;
        }
    };
    node* mainNode;
    node* iter;
public:
    LinkedList<T>();
    ~LinkedList<T>();
    LinkedList<T>(const LinkedList<T> &copy);
    LinkedList<T>& operator = (const LinkedList<T> &copy);

    void add(T data);
    void deleteValue(T data);
    void readList();
    void deleteLastValue();
    T& topValue();
    T& firstValue();
    bool isEmpty();
    int getSize();
    T& nextValue();
    T& prevValue();
    T& currIterValue();
    bool hasNext();
    bool hasPrev();
    void resetIter();
    bool findValue(T value);
    bool isNullPtr();
};

template<class T>
LinkedList<T>::LinkedList(){
    mainNode = nullptr;
    iter = mainNode;
}

template<class T>
LinkedList<T>::~LinkedList<T>(){
    if(mainNode != nullptr) {
        while (mainNode->nextNode != nullptr) {
            mainNode = mainNode->nextNode;
            delete mainNode->prevNode;
        }
    }
    if(mainNode != nullptr){
        delete mainNode;
    }
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &copy){
    mainNode = new node(copy.mainNode->data);
    if(copy.mainNode->nextNode != nullptr) {
        node *temp = copy.mainNode->nextNode;
        while (temp->nextNode != nullptr) {
            T dat = temp->data;
            this->add(dat);
            temp = temp->nextNode;
        }
        add(temp->data);
    }
    iter = mainNode;
}

template<class T>
LinkedList<T>& LinkedList<T>::operator = (const LinkedList<T> &copy){
    if(mainNode != nullptr) {
        while (mainNode->nextNode != nullptr) {
            mainNode = mainNode->nextNode;
            delete mainNode->prevNode;
        }
    }
    if(mainNode != nullptr){
        mainNode = nullptr;
    }

    mainNode = new node(copy.mainNode->data);
    if(copy.mainNode->nextNode != nullptr) {
        node *temp = copy.mainNode->nextNode;
        while (temp->nextNode != nullptr) {
            T dat = temp->data;
            this->add(dat);
            temp = temp->nextNode;
        }
        add(temp->data);
    }
    iter = mainNode;

    return *this;
}

template<class T>
void LinkedList<T>:: add(T data) {
    node* newNode = new node();
    newNode->data = data;

    if(mainNode == nullptr){
        mainNode = newNode;
    }
    else{
        if(mainNode->nextNode != nullptr){
            iter = mainNode;
            while(iter->nextNode != nullptr){
                iter = iter->nextNode;
            }
            iter->nextNode = newNode;
            newNode->prevNode = iter;
        }
        else{
            newNode->prevNode = mainNode;
            mainNode->nextNode = newNode;
        }
    }
    iter = mainNode;
}

template<class T>
void LinkedList<T>:: deleteValue(T data) {
    if(mainNode == nullptr){
        return;
    }
    if(mainNode->data == data){
        if(mainNode->nextNode == nullptr){
            mainNode = nullptr;
        }
        else {
            mainNode = mainNode->nextNode;
            mainNode->prevNode = nullptr;
        }
    }

    else {
        iter = mainNode;
        while (iter != nullptr) {
            if (iter->data == data) {
                if(iter->nextNode == nullptr){
                    iter = iter->prevNode;
                    iter->nextNode = nullptr;
                }
                else {
                    iter = iter->prevNode;
                    iter->nextNode = iter->nextNode->nextNode;
                }
                break;
            }
            iter = iter->nextNode;
        }
    }
    iter = mainNode;
}

template<class T>
void LinkedList<T>::readList() {
    iter = mainNode;
    while(iter != nullptr){
        cout << iter->data << " ";
        iter = iter->nextNode;
    }
    cout << endl;
}

template<class T>
void LinkedList<T>::deleteLastValue() {
    if (mainNode == nullptr) {
        return;
    }
    if (mainNode->nextNode == nullptr) {
        mainNode = nullptr;
    }
    else{
        iter = mainNode;
        while (iter->nextNode->nextNode != nullptr) {
            iter = iter->nextNode;
        }
        delete iter->nextNode;
        iter->nextNode = nullptr;
        iter = mainNode;
    }
    iter = mainNode;
}

template<class T>
T& LinkedList<T>::topValue() {
    iter = mainNode;
    while(iter->nextNode != nullptr){
        iter = iter->nextNode;
    }
    return iter->data;
}

template<class T> // Delete function
T& LinkedList<T>::firstValue() {
    return mainNode->data;
}

template<class T>
bool LinkedList<T>::isEmpty() {
    if(mainNode == nullptr){
        return true;
    }
    else{
        return false;
    }
}

template<class T>
int LinkedList<T>::getSize() {
    iter = mainNode;
    int length = 0;
    while(iter != nullptr){
        length++;
        if(iter->nextNode == nullptr){
            break;
        }
        else{
            iter = iter->nextNode;
        }
    }
    iter = mainNode;
    return length;
}

template<class T>
T& LinkedList<T>::nextValue() {
    //if(iter->nextNode == nullptr){
    //    return iter->data;
    //}
    //else {
    iter = iter->nextNode;
    return iter->data;
    //}
}

template<class T>
T& LinkedList<T>::prevValue() {
    //if (iter->prevNode == nullptr) {
    //  return iter->data;
    //}
    //else {
    iter = iter->prevNode;
    return iter->data;
    //}
}

template<class T>
T& LinkedList<T>::currIterValue(){
    if(iter == nullptr){
        iter = mainNode;
    }
    return iter->data;
}

template<class T>
bool LinkedList<T>::hasNext() {
    if(iter->nextNode == nullptr){
        return false;
    }
    else{
        return true;
    }
}

template<class T>
bool LinkedList<T>::hasPrev() {
    if(iter->prevNode == nullptr){
        return false;
    }
    else{
        return true;
    }
}

template<class T>
void LinkedList<T>::resetIter() {
    iter = mainNode;
}

template<class T>
bool LinkedList<T>::findValue(T value) {
    resetIter();
    if(currIterValue() == value){
        return true;
    }
    while(hasNext()){
        nextValue();
        if(currIterValue() == value){
            return true;
        }
    }
    resetIter();
    return false;
}

template<class T>
bool LinkedList<T>::isNullPtr() {
    if(iter == nullptr){
        return true;
    }
    return false;
}

#endif //S20_PA04_FLIGHTPLANNER_LINKEDLIST_H