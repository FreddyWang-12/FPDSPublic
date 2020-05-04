#ifndef S20_PA04_FLIGHTPLANNER_LINKEDLIST_H
#define S20_PA04_FLIGHTPLANNER_LINKEDLIST_H

#include "Node.h"
#include <iostream>
using namespace std;
template <typename T>
class Linkedlist{
private:
    ///private member variables
    Node<T>* head;
    Node<T>* tail;
    Node<T>* iterator = nullptr;
    int elementsInLL;
///public member variables
public:
    Linkedlist();
    Linkedlist(const Linkedlist<T>&);
    ~Linkedlist();
    void push_back(T);
    void addFront(T);
    bool isEmpty();
    T&operator[] (int);
    void remove(int);
    void insert(int,T);
    Node<T>* getHead();
    Node<T>* getTail();
    Node<T>* getIterator();
    void resetIterorator();
    int size();
    Linkedlist<T>&operator=(Linkedlist<T>&);
    bool checkNext();
    void moveToNext();
    void setiteratBegining();


    //Object
    //Source and Destination Class
    //Adjacency Class
    //Stack Class



};

///adds a node to the linklist at a certain index
template <typename T>
void Linkedlist<T>::insert(int index, T type) {
    Node<T>* tempNode = new Node<T>(type);
    if(index == 0) {
        ///check if the legth is 0
        if (elementsInLL == 0) {
            head = tempNode;
            tail = tempNode;
            elementsInLL++;
        } else {
            ///arrange pointers to add new Node to the list
            Node<T> *temp = head;
            temp->setprevNode(tempNode);
            tempNode->setprevNode(nullptr);
            tempNode->setnextNode(temp);
            head = tempNode;
            elementsInLL++;
        }
        ///looks to see if the index is at the end of the list
    }else if(index == elementsInLL){
        Node<T>* temp3 = tail;
        tail = tempNode;
        tempNode->setnextNode(nullptr);
        tempNode->setprevNode(temp3);
        temp3->setnextNode(tempNode);
        elementsInLL++;
        ///looks to see if the index is bewtween first and last elements of the linked list
    }else if(index > 0 && index < elementsInLL){
        Node<T>* c = head;
        for(int i = 1; i <index; i++){
            c = c->getnextNode();
        }
        ///rearanges nodes so that the previous and next nodes point to the correct other nodes
        ///this part was terrible
        tempNode->setnextNode(c->getnextNode());
        tempNode->setprevNode(c);
        c->setnextNode(tempNode);
        tempNode->getnextNode()->setprevNode(tempNode);
        elementsInLL++;
    }else{
        cout << "Insert Function for LL is out of Bounds!" << endl;
    }
}

///constructor
template <typename T>
Linkedlist<T>::Linkedlist(){
    head = nullptr;
    tail = nullptr;
    elementsInLL = 0;
}

///copy constrctor
template <typename T>
Linkedlist<T>::Linkedlist(const Linkedlist<T> &data){
    elementsInLL = data.elementsInLL;
    Node<T>* temp = data.head;
    while(temp != nullptr){
        push_back(temp->getdata());
        temp = temp->next;
    }
}
///de-constructor
template <typename T>
Linkedlist<T>::~Linkedlist() {
    if(head != nullptr){
        while(tail != nullptr){
            Node<T>* temp = tail->prev;
            delete tail;
            tail = temp;
        }
    }
}


///push back leverages the functionality of insert
template <typename T>///pushed back T at last index;
void Linkedlist<T>::push_back(T x) {
    insert(elementsInLL,x);

}

template <typename T>
///adds an element to the front of the LL
void Linkedlist<T>::addFront(T x) {
    Node<T>* temp = new Node<T>(x);
    if(tail == nullptr){
        tail = temp;
        head = temp;
        temp->next = nullptr;
        temp->prev = nullptr;
    }else{
        head->prev = temp;
        temp->next = head;
        temp = head;
    }
}
///checks to see if LL is empty
template <typename T>
bool Linkedlist<T>::isEmpty() {
    if(head == nullptr){
        return true;
    }else{
        return false;
    }
}

template <typename T> ///returns an elements at a index that is passed
T& Linkedlist<T>::operator[](int index) {
    if(index < elementsInLL && index >= 0){
        Node<T>* temp = head;
        if(temp != nullptr){
            for(int i = 0; i < index; i++){
                temp = temp->getnextNode();
            }
            return temp->getdata();
        }else{
            cout << "Out of bounds!" << endl;
        }
    }
}

///removes a element at a certain index
template <typename T>
void Linkedlist<T>::remove(int index) {
    //first sees if index is 0
    if (index == 0) {
        if (elementsInLL == 0) {
            //then checks to see number of elements in list are 0
            cout << "Nothing to remove!" << endl;
        } else {
            //removes the head and replaces it with the next node
            head = head->getnextNode();
            head->next = nullptr;
            --elementsInLL;
        }
    } else if (index == (elementsInLL - 1)) {
        tail = tail->getprevNode();
        tail->next = nullptr;
        --elementsInLL;
    } else if (index > 0 && index < elementsInLL - 1) {
        Node<T> *holder = head;
        for (int i = 1; i <= index; i++) {
            holder = holder->getnextNode();
        }
        Node<T> *replacer = holder->getprevNode();
        holder->getprevNode() == holder->getnextNode();
        holder->getnextNode() == replacer->getprevNode();
        --elementsInLL;
    }else{
        cout << "Removing this node is not possible. It is not in bounds." << endl;
    }
}
///return head of LL
template <typename T>
Node<T>* Linkedlist<T>::getHead() {
    return head;
}
///retuns tail of the LL
template <typename T>
Node<T>* Linkedlist<T>::getTail() {
    return tail;
}
///return the size by returning the number of elements
template <typename T>
int Linkedlist<T>::size() {
    return elementsInLL;
}
///Assignment Operator
template <typename T>
Linkedlist<T>& Linkedlist<T>::operator=(Linkedlist<T>& arg){
//    if(this == &arg)
//        return *this;
    if(arg.elementsInLL == 0){
        Node<T>* temp = head;
        while(temp!= nullptr){
            Node<T>* temp2 = temp->getprevNode();
            delete temp;
            temp = temp2;
        }
        elementsInLL = 0;
        head = nullptr;
        tail = nullptr;
    }
    else{
        Node<T>* temp = head;
        while(temp != nullptr){
            Node<T>* next = temp->getnextNode();
            delete temp;
            temp = next;
        }
        elementsInLL = 0;
        Node<T>* newArg = arg.head;
        while(newArg != nullptr){
            push_back(newArg->getdata());
            newArg = newArg->getnextNode();
        }
    }
}

///Checks next interator if it is nullptr then it is set to nullptr and returns false
template <typename T>
bool Linkedlist<T>::checkNext() {
    if(iterator->getnextNode() == nullptr){
        iterator = nullptr;
        return false;
    }
    return true;
}

///moves iterator to the next Node
template  <typename T>
void Linkedlist<T>::moveToNext() {
    iterator = iterator->getnextNode();
}
///sets iterator to the head AKA the begining
template <typename T>
void Linkedlist<T>::setiteratBegining() {
    iterator = head;
}
///returns itorator
template <typename  T>
Node<T>* Linkedlist<T>::getIterator() {
    return iterator;
}
///resets the iterator back to nullptr
template <typename  T>
void Linkedlist<T>::resetIterorator() {
    iterator = nullptr;
}

#endif //S20_PA04_FLIGHTPLANNER_LINKEDLIST_H