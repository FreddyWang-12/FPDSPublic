//
// Created by jonas on 5/3/2020.
//

#ifndef FINALPROJECT_NODE_H
#define FINALPROJECT_NODE_H
template <typename T>

class Node {
    ///private member variables
private:
    T data;
    Node<T> *next;
    Node<T> *prev;
    template <typename U>
    friend class Linkedlist;
    ///public member variablers
public:
    Node();
    Node(T);
    Node(const Node<T>&);
    void setdata(T);
    T& getdata();
    Node<T>* getnextNode();
    Node<T>* getprevNode();
    void setnextNode(Node<T>*);
    void setprevNode(Node<T>*);
};
///constructor
template <typename T>
Node<T>::Node(){
    next = nullptr;
    prev = nullptr;
}
///copy constructor
template  <typename T>
Node<T>::Node(T x){
    next = nullptr;
    prev = nullptr;
    data = x;
}
///copy constuctor
template <typename T>
Node<T>::Node(const Node<T> &x){
    next = x.next;
    prev = x.prev;
    data = x.data;
}
/// sets data in node
template  <typename T>
void Node<T>::setdata(T x) {
    data = x;
}
///returns data in Node
template <typename T>
T& Node<T>::getdata() {
    return data;
}
template <typename T>
void Node<T>::setprevNode(Node<T> *pre) {
    prev = pre;
}

///sets next to the next Node
template <typename T>
void Node<T>::setnextNode(Node<T> *nx) {
    next = nx;
}
///return next
template <typename T>
Node<T>* Node<T>::getnextNode() {
    return next;
}
///returns previous
template  <typename T>
Node<T>* Node<T>::getprevNode() {
    return prev;
}
#endif //FINALPROJECT_NODE_H
