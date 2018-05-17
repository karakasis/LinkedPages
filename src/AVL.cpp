#include "AVL.h"

AVL::AVL()
{
    //ctor
}

AVL::~AVL()
{
    //dtor
}

bool AVL::search(const int e) const
{   // Search for element that matches k.
    // pointer p starts at the root and moves through
    // the tree looking for an element with key k
    AVLTreeNode *p = root;
    while (p){ // examine p->data
        if (e < p -> data)
            p = p ->leftChild;
        else if (e > p->data) p = p->rightChild;
        else { // found element
            //e = p->data;
            return true;
        }
    }
    return false;
}
