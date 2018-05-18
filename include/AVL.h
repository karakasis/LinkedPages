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
            int init;
        };
        node* root = NULL;
        AVL()
        {
            //node* root = new node;
        }


        node* insert_link(int page_id)//Search F() for a value is not used.Just Insert is called and if the value already exists it does nothing.
        {
            if (root == NULL)
            {
                root = new node;//Elements tree
                //root->init = 1;
                root->page_id = page_id;//   *|*
                root->left = NULL;//   **|**
                root->right = NULL;// ***|***
                root->self = new T;//Pointer to INTERNAL AVL<T> tree with LINKS
                //node->Link = AVL<T><link>::insert_link(node->Link,LinkID);//Insert Link to Internal tree.If already exists it does nothing.
            }
            else if (page_id < root->page_id)//In this case the element was not in the tree already.So when the node is NULL it will create space for internal_AVL<T>;.
            {
                root->left = insert_inner(root->left, page_id);
                root = balance (root);
                return root->left;
            }
            else if (page_id > root->page_id)//In this case the element was not in the tree already.So when the node is NULL it will create space for internal_AVL<T>;.
            {
               root->right = insert_inner(root->right, page_id);
               root = balance (root);
               return root->right;
            }
            return root;
        }

        bool delete_link(int page_id)
        {
            bool deleted = false;
            //node* temp = search(root,page_id); //search searches for a number,if found returns address of node(is overloaded for both internal_avl and avl_node).
            node* temp = delete_inner(root,page_id); //search searches for a number,if found returns address of node(is overloaded for both internal_avl and avl_node).
            if(temp!=NULL) deleted = true;
            temp == NULL;
            return deleted;
        }

        node* get(int page_id)
        {
            return search(root,page_id);
        }

        void printTree(ofstream& output){
            internal_inorder(output,root);
            output<<std::endl;
            std::cout<<output.rdbuf();
        }

    private:
        //Internal_AVL functions////
        /*
        * Delete link recursion
        */
        node* delete_inner(node* nod, int key)//Deletion for internal avl type of struct.
        {
            // STEP 1: PERFORM STANDARD BST DELETE

            if (nod == NULL)
                return nod;

            // If the key to be deleted is smaller than the node's key,
            // then it lies in left subtree
            if ( key < nod->page_id )
                nod->left = delete_inner(nod->left, key);

            // If the key to be deleted is greater than the node's key,
            // then it lies in right subtree
            else if( key > nod->page_id )
                nod->right = delete_inner(nod->right, key);

            // if key is same as node's key, then This is the node
            // to be deleted
            else//IF NODE IS FOUND
            {
                // node with only one child or no child
                if( (nod->left == NULL) || (nod->right == NULL) )
                {
                    //node *temp = nod->left ? nod->left : nod->right;//temp is whatever is not NULL.

                     node *temp;
                     if(nod->left != NULL){
                        temp = nod->left;
                     }else{
                         temp = nod->right;//temp is whatever is not NULL.
                     }

                    // No child case
                    if(temp == NULL)
                    {
                        temp = nod;
                        nod = NULL;
                    }
                    else // One child case
                     *nod = *temp; // Copy the contents of the non-empty child

                    //delete temp;
                }
                else
                {
                    // node with two children: Get the inorder successor (smallest
                    // in the right subtree)
                    node* temp = minValue(nod->right);

                    // Copy the inorder successor's data to this node
                    nod->page_id = temp->page_id;

                    // Copy the inorder successor's Link address to this node.
                    nod->self = temp->self; //***watch

                    // Delete the inorder successor
                    nod->right = delete_inner(nod->right, temp->page_id);


                }
            }

            // If the tree had only one node then return
            if (nod == NULL)
              return nod;
            else
            {
               nod = balance(nod);
               return nod;
            }


        }

        /*
         * Insert Element into the tree
         */


        /*
        *Insert Link recursion
        */
        node* insert_inner(node* nod,int page_id)
        {
            if (nod == NULL)
            {
                nod = new node;//Elements tree
                //root->init = 1;
                nod->page_id = page_id;//   *|*
                nod->left = NULL;//   **|**
                nod->right = NULL;// ***|***
                nod->self = new T;//Pointer to INTERNAL AVL<T> tree with LINKS
                //node->Link = AVL<T><link>::insert_link(node->Link,LinkID);//Insert Link to Internal tree.If already exists it does nothing.
            }
            else if(page_id < nod->page_id)
            {
                nod->left = insert_inner(nod->left,page_id);
                nod = balance(nod);
            }
            else if(page_id > nod->page_id)
            {
                nod->right = insert_inner(nod->right,page_id);
                nod = balance(nod);
            }
            return nod;
        }

        /*
        *Counting The nodes of tree  (FOR AVL<T>_NODE ).
        */
        int MBbinarytree_count_recursive(node *node)
        {
            int count = 0;
            if (node != NULL)
            {
                count = 1 + MBbinarytree_count_recursive(node->left) + MBbinarytree_count_recursive(node->right);
            }
            return count;
        }

        /*
        *returns Minimum Node address of an AVL<T> tree(avl_node*).
        */
        node* minValue(node* noded)
        {
            node* Current = noded;
            while(Current->left != NULL)
            {
                Current = Current->left;
            }
            return Current;
        }

        node* search(node* nod,int page_id)//searches for the Node in the Tree via its data.
        {                               //Returns the address(avl_node*).
            if(nod == NULL){
                node* dum = new node;
                dum-> self = NULL;
                return dum;
            }else if( page_id == nod->page_id){
                return nod;
            }
            if(page_id > nod->page_id)
            {
                return search(nod->right,page_id);
            }
            else if(page_id < nod->page_id)
            {
                return search(nod->left,page_id);
            }
        }

        /*
        *Returns true if AVL<T> tree with node as node is height-balanced
        */
        bool isBalanced(node* node)
        {
           int lh; /* for height of left subtree */
           int rh; /* for height of right subtree */

           /* If tree is empty then return true */
           if(node == NULL)
            return true;

           /* Get the height of left and right sub trees */
           lh = height(node->left);
           rh = height(node->right);

           if( abs(lh-rh) <= 1 && isBalanced(node->left) && isBalanced(node->right))
             return true;

           /* If we reach here then tree is not height-balanced */
           return false;
        }

        /*
         * Height of AVL<T> Tree
         */
        int height(node *temp)
        {
            int h = 0;
            if (temp != NULL)
            {
                int l_height = height (temp->left);
                int r_height = height (temp->right);
                int max_height = std::max(l_height, r_height);
                h = max_height + 1;
            }
            return h;
        }

        /*
         * Height Difference
         */
        int diff(node *temp)
        {
            int l_height = height (temp->left);
            int r_height = height (temp->right);
            int b_factor= l_height - r_height;
            return b_factor;
        }

        /*
         * Right Rotation
         */
        node* r_rotation(node *parent)
        {
            node *temp;
            temp = parent->right;
            parent->right = temp->left;
            temp->left = parent;
            return temp;
        }
        /*
         * Left Rotation
         */
        node *l_rotation(node *parent)
        {
            node *temp;
            temp = parent->left;
            parent->left = temp->right;
            temp->right = parent;
            return temp;
        }
        /*
         * Left - Right Rotation
         */
        node *lr_rotation(node *parent)
        {
            node *temp;
            temp = parent->left;
            parent->left = r_rotation (temp);
            return l_rotation (parent);
        }
        /*
         * Right- Left Rotation
         */
        node *rl_rotation(node *parent)
        {
            node *temp;
            temp = parent->right;
            parent->right = l_rotation (temp);
            return r_rotation (parent);
        }
        /*
         * Balancing AVL<T> Tree
         */
        node *balance(node *temp)
        {
            if(temp == NULL)
            {
                return temp;
            }
            int bal_factor = diff (temp);
            if (bal_factor > 1)
            {
                if (diff (temp->left) > 0)
                    temp = l_rotation (temp);
                else
                    temp = lr_rotation (temp);
            }
            else if (bal_factor < -1)
            {
                if (diff (temp->right) > 0)
                    temp = rl_rotation (temp);
                else
                    temp = r_rotation (temp);
            }
            return temp;
        }

        /*
        *Inorder Traversal of Internal AVL<T> tree
        */
        void internal_inorder(ofstream& output,node* node)
        {
           if(node != NULL)
           {
             internal_inorder(output,node->left);
             output<<node->page_id<<" ";
             internal_inorder(output,node->right);
           }
           return;
        }


};

#endif // INVERTEDINDEX_H
