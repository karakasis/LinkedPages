#ifndef AVL_H
#define AVL_H

#include <string.h>
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include<cstdio>
#include<sstream>
#include<math.h>
#include<iostream>

using namespace std;

/*
 * Class Declaration
 */
template <class T>
class AVL
{
    public:
        struct node
        {
            int page_id;
            node *left;
            node *right;
            T *self;
        };

        //struct page;
        T* insert_link(int page_id);
        bool delete_link(int page_id);
        T* get(int page_id);
        node* root;

        AVL()
        {
            root = NULL;
        }
        void printTree(ofstream& output);

        //======
        /*
        *MAIN FUNCTIONS
        */

    private:
        //Internal_AVL functions////
        T* insert_link(node<T>* ,int );
        node<T>* delete_link(node<T>* ,int );
        node<T>* balance(node<T> * );
        int diff(node<T> *);
        int height(node<T> *);
        node<T> *r_rotation(node<T> *);
        node<T> *l_rotation(node<T> *);
        node<T> *lr_rotation(node<T> *);
        node<T> *rl_rotation(node<T> *);

        node<T>* minValue(node<T> *);
        bool isBalanced(node<T>* root);
        int MBbinarytree_count_recursive(node<T> *);
        //void inorder(ofstream& output,node *);
        void internal_inorder(ofstream& output,node<T> *);
        node<T>* search(node<T>*,int );

};

#endif // INVERTEDINDEX_H
