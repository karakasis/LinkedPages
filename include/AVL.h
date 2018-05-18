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

template <class T>
struct page
{
    int page_id;
    T *left;
    T *right;
};

/*
 * Class Declaration
 */
template <class T>
class AVL
{
    public:
        //struct page;
        void insert_link(int page_id);
        void delete_link(int page_id);
        T* root;

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
        T* insert_link(T* root,int LinkID);
        T* delete_link(T *,int );
        T* balance(T * );
        int diff(T *);
        int height(T *);
        T *r_rotation(T *);
        T *l_rotation(T *);
        T *lr_rotation(T *);
        T *rl_rotation(T *);

        T* minValue(T *);
        bool isBalanced(T* root);
        int MBbinarytree_count_recursive(T *);
        void inorder(ofstream& output,page *);
        void internal_inorder(ofstream& output,link *);
        T* search(T*,int );

};

#endif // INVERTEDINDEX_H
