#include "AVL.h"

AVL::AVL()
{
    //ctor
}

AVL::~AVL()
{
    //dtor
}

template <typename K, typename T>
bool AVL::search(const K& k, T &e) const
{   // Search for element that matches k.
    // pointer p starts at the root and moves through
    // the tree looking for an element with key k
    AVLTreeNode<T> *p = root;
    while (p){ // examine p->data
        if (k < p -> data)
            p = p ->leftChild;
        else if (k > p->data) p = p->RightChild;
        else { // found element
            e = p->data;
            return true;
        }
    }
    return false;
}
