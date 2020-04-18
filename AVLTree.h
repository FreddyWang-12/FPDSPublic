//
// Created by jonas on 4/18/2020.
//

#ifndef FINALPROJECT_AVLTREE_H
#define FINALPROJECT_AVLTREE_H

#include <iostream>
#include "AVLNode.h"
#include "Word.h"
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
    Word & getContent(Word&,AVLNode<Word>*);
public:
    AVLTree();
    AVLTree(AVLNode<T>&);
    AVLTree(AVLTree<T>&);
    ~AVLTree();
    void dump();
    Word & getContent(Word&);
    void addNode(T&);
    int height(AVLNode<T>*);


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
void AVLTree<T>::r1LeftChild(AVLNode<T> *&x) {
    AVLNode<T>* temp = x->left;
    x->left = temp->right;
    temp->right = x;
    x->height = max(height(x->left),height(x->right))+1;
    temp->height = max(height(temp->left), x->height)+1;
    x = temp;
}

template <typename T>
void AVLTree<T>::r1RightChild(AVLNode<T> *&x) {
    AVLNode<T>* temp = x->right;
    x->right = temp->left;
    temp->left = x;
    x->height = max(height(x->left),height(x->right))+1;
    temp->height = max(height(temp->left),x->height)+1;
    x = temp;
}

template <typename T>
void AVLTree<T>::r2LeftChild(AVLNode<T> *&x) {
    r1RightChild(x->left);
    r1LeftChild(x);
}

template <typename T>
void AVLTree<T>::r2RightChild(AVLNode<T> *&x) {
    r1LeftChild(x->right);
    r1RightChild(x);
}

template <typename T>
int AVLTree<T>::height(AVLNode<T>* currentNode) {
    if(currentNode == nullptr){
        return 0;
    }else{
        return currentNode->height;
    }
}

template <typename T>
void AVLTree<T>::insertNode(T & x, AVLNode<T> *& node) {
    if(node == nullptr){
        node = new AVLNode<T>(x, nullptr,nullptr);
    }else if(x < node->data){
        insertNode(x,node->left);
        if(height(node->left)-height(node->right) == 2){
            if(x < node->left->data){
                ///CASE 1
                r1LeftChild(node);
            }else{
                ///CASE 2
                r2LeftChild(node);
            }
        }
    }else if(node->data < x){
        insertNode(x,node->right);
        if(height(node->right)-height(node->left) == 2){
            if(node->right->data < x){
                ///Case 4
                r1RightChild(node);
            }else{
                ///Case 3
                r2RightChild(node);
            }
        }
    }else{};

    node->height = max(height(node->left), height(node->right))+1;
}
template <typename T>
void AVLTree<T>::addNode(T & info) {
    insertNode(info,cur);
}
//
//template <typename T>
//Word & AVLTree<T>::getContent(Word & x, AVLNode<Word> * curNode) {
//    while(curNode != nullptr){
//        if( x < curNode->data){
//            curNode = curNode->left;
//        }else if(curNode->data < curNode){
//            curNode = curNode->right;
//        }else{
//            return curNode->data;
//        }
//    }
//}
//
//template <typename T>
//Word& AVLTree<T>::getContent(Word &x) {
//
//}



#endif //FINALPROJECT_AVLTREE_H
