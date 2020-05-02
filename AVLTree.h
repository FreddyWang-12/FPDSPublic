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
    T& getContent(T&,AVLNode<T>*);
    bool ifExists(T&,AVLNode<T>*);
    int size = 0;
    void printCOUTree(AVLNode<T>*);
    void printToFile(ofstream&, AVLNode<T>*);
    void printtoFileLEVEL(ofstream&,AVLNode<T>*,int);
public:
    AVLTree();
    AVLTree(AVLNode<T>&);
    AVLTree(AVLTree<T>&);
    ~AVLTree();
    void dump();
    Word & getContent(Word &);
    Word& getContent(string&);
    void addNode(T&);
    void addFirstNodes(T&);
    int height(AVLNode<T>*);
    bool isEmpty();
    bool ifExists(T&);
    int getSize();
    void getTreeSize();
    void printerFunc();
    void printtoFileFunc(ofstream&);
    int height2(AVLNode<T>*);
    void printtofileLVLFUNC(ofstream&);


};
template <typename T>
void AVLTree<T>::printtoFileFunc(ofstream & output) {
    if(cur == nullptr){
        cout << "There is nothing in your tree!" << endl;
    }else{
        printToFile(output,cur);
    }
}


template <typename T>
void AVLTree<T>::printToFile(ofstream & output, AVLNode<T> *nodey) {
    if(nodey != nullptr){
        printToFile(output,nodey->left);
        output << nodey->data;
        printToFile(output,nodey->right);
    }
}
template <typename T>
void AVLTree<T>::printtofileLVLFUNC(ofstream &output) {
    int h = height2(cur);
    int i;
    for(i = 1; i <= h; i++){
        printtoFileLEVEL(output,cur,i);
    }
}

template <typename T>
void AVLTree<T>::printtoFileLEVEL(ofstream &output, AVLNode<T> *nodey, int lvl) {
    if(nodey == nullptr){
        return;
    }
    if(lvl == 1){
        output << nodey->data;
    }else if(lvl >1){
        printtoFileLEVEL(output,nodey->left, lvl-1);
        printtoFileLEVEL(output,nodey->right, lvl-1);
    }
}

template <typename T>
int AVLTree<T>::height2(AVLNode<T> *nodey) {
    if(nodey == nullptr){
        return 0;
    }else{
        int lheight = height2(nodey->left);
        int rheight = height2(nodey->right);
        if(lheight>rheight){
            return (lheight+1);
        }else{
            return (rheight+1);
        }
    }
}



template <typename T>
void AVLTree<T>::printerFunc() {
    if(cur == nullptr){
       cout << "There is nothing in your tree!" << endl;
    }else{
        printCOUTree(cur);
    }
}


template <typename T>
void AVLTree<T>::printCOUTree(AVLNode<T> *nodey) {
    ofstream out;
    out.open("output.txt");
    if(!out){
        cout << "Was not able to open output.txt file to insert elements in AVL Word Tree" << endl;
    }
    if(nodey != nullptr){
        printCOUTree(nodey->left);
        cout << nodey->data << endl;
        printCOUTree(nodey->right);
    }
}



template <typename T>
bool AVLTree<T>::isEmpty() {
    if(cur == nullptr){
        return true;
    }else{
        return false;
    }
}

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
    size++;
}

template <typename T>
T& AVLTree<T>::getContent(T& x, AVLNode<T> * curNode) {
    while(curNode != nullptr){
        if( x < curNode->data){
            curNode = curNode->left;
        }else if(curNode->data < x){
            curNode = curNode->right;
        }else{
            return curNode->data;
        }
    }
}

template <typename T>
Word& AVLTree<T>::getContent(Word& x) {
    return getContent(x, cur);
}
template <typename T>
Word& AVLTree<T>::getContent(string& x) {
    Word words(x);
    return getContent(words, cur);
}

template <typename T>
bool AVLTree<T>::ifExists(T& x, AVLNode<T>* nody){
    if(nody == nullptr){
        return false;
    }else if (x < nody->data){
        return ifExists(x,nody->left);
    }else if(nody->data < x){
        return ifExists(x,nody->right);
    }else{
        return true;
    }
}

template <typename T>
bool AVLTree<T>::ifExists(T &x) {
    return ifExists(x,cur);
}

template <typename T>
int AVLTree<T>::getSize() {
    return size;
}

template <typename T>
void AVLTree<T>::getTreeSize() {
    cout << "Total AVL Tree Nodes = " << getSize() << endl;
}





#endif //FINALPROJECT_AVLTREE_H
