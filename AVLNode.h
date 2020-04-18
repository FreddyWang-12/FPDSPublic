//
// Created by jonas on 4/18/2020.
//

#ifndef FINALPROJECT_AVLNODE_H
#define FINALPROJECT_AVLNODE_H
using namespace std;
template <typename T>
class AVLNode {
    template <class U> friend class AVLTree;
private:
    T data;
    AVLNode<T> *left;
    AVLNode<T> *right;
    int height;
public:
    AVLNode(): right(nullptr),left(nullptr),height(0){}
    AVLNode(T arg) : data(arg), right(nullptr),left(nullptr),height(0){}
    AVLNode(T& arg,AVLNode<T>* r, AVLNode<T>* l,int high = 0) : data(arg), right(r),left(l),height(high){}
    AVLNode(const AVLNode<T> &r):right(r.left),left(r.right),data(r.data),height(r.height){}

};


#endif //FINALPROJECT_AVLNODE_H
