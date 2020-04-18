//
// Created by jonas on 4/18/2020.
//

#ifndef FINALPROJECT_AVLTREE_H
#define FINALPROJECT_AVLTREE_H

#include <iostream>
#include "AVLNode.h"

using namespace std;

template <typename T>
class AVLTree{
private:
    AVLNode<T>* cur;
    void dump(AVLNode<T>*&);
    void r1LeftChild(AVLNode<T>*&);
    void r2LeftChild(AVLNode<T>*&);
    void r1RightChild(AVLNode<T>*&);
    void r2RightChild(AVLNode<T>*&);
    void insertNode(T&,AVLNode<T> *&);

public:
    AVLTree();
    AVLTree(AVLNode<T>&);
    AVLTree(AVLTree<T>&);
    ~AVLTree();
    void dump();
};


template <typename T>
AVLTree<T>::AVLTree() {
    cur = nullptr;
}


template <typename T>
AVLTree<T>::AVLTree(AVLNode<T> &x) {
    cur = x;
}


template <typename T>
AVLTree<T>::AVLTree(AVLTree<T> &x) {
    *this = x;
}


template <typename T>
AVLTree<T>::~AVLTree() {
    dump();
}


template <typename T>
void AVLTree<T>::dump(AVLNode<T> *&x) {
    if(x != nullptr){
        dump(x->left);
        dump(x->right);
        delete x;
    }
    x = nullptr;
}



template <typename T>
void AVLTree<T>::dump() {
    dump(cur);
}


template <typename T>
void AVLTree<T>::r1LeftChild(AVLNode<T> *&b) {
    AVLNode<T>* a = b->left;
    b->left = a->right;
    a->right = b;
    b->height = max(height(b->left),height(b->right))+1;
    a->height = max(height(a->left), b->height)+1;
    b = a;
}


#endif //FINALPROJECT_AVLTREE_H
