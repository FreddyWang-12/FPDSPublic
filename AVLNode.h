//
// Created by jonas on 4/18/2020.
//

// This object acts as the primary node container for an AVL Tree.
// It stores the data of a given object of class <T>.
#ifndef FINALPROJECT_AVLNODE_H
#define FINALPROJECT_AVLNODE_H
using namespace std;
template <typename T>
class AVLNode {
    template <class U> friend class AVLTree; //This class is friends with the AVL Tree class.
private:
    T data; // Contains the data of an object<T> for the AVL node
    AVLNode<T> *left; // Pointer to the bottom left AVL Node
    AVLNode<T> *right; // Pointer to the bottom right AVL Node
    int height; // The height of the AVL
public:
    AVLNode(): right(nullptr),left(nullptr),height(0){} // Default Constructor of the AVL Node
    AVLNode(T arg) : data(arg), right(nullptr),left(nullptr),height(0){} // Constructor that creates an AVL Node with object<T> "arg"
    AVLNode(T& arg,AVLNode<T>* r, AVLNode<T>* l,int high = 0) : data(arg), right(r),left(l),height(high){} // Constructor that creates the first node with object<T> "arg", its first left node, and its first right node
    AVLNode(const AVLNode<T> &r):right(r.left),left(r.right),data(r.data),height(r.height){} // Copy constructor for the AVL Node

};


#endif //FINALPROJECT_AVLNODE_H
