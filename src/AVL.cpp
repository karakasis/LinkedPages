#include "AVL.h"
#include <iostream>

#include <string.h>
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <cstdio>
#include <sstream>
#include <math.h>

using namespace std;

template<class T>
bool AVL<T>::delete_link(int page_id)
{
    bool deleted = false;
    //node* temp = search(root,page_id); //search searches for a number,if found returns address of node(is overloaded for both internal_avl and avl_node).
    node<T>* temp = delete_link(root,page_id); //search searches for a number,if found returns address of node(is overloaded for both internal_avl and avl_node).
    if(temp!=NULL) deleted = true;
    temp == NULL;
    return deleted;
}


/*
* Delete link recursion
*/

template <class T>
node<T>* AVL<T>::delete_link(node<T>* node, int key)//Deletion for internal avl type of struct.
{
    // STEP 1: PERFORM STANDARD BST DELETE

    if (node == NULL)
        return node;

    // If the key to be deleted is smaller than the node's key,
    // then it lies in left subtree
    if ( key < node->page_id )
        node->left = delete_link(node->left, key);

    // If the key to be deleted is greater than the node's key,
    // then it lies in right subtree
    else if( key > node->page_id )
        node->right = delete_link(node->right, key);

    // if key is same as node's key, then This is the node
    // to be deleted
    else//IF NODE IS FOUND
    {
        // node with only one child or no child
        if( (node->left == NULL) || (node->right == NULL) )
        {
             T* temp ;
             if(node->left != NULL){
                temp = node->left;
             }else{
                 temp = node->right;//temp is whatever is not NULL.
             }

            // No child case
            if(temp == NULL)
            {
                temp = node;
                node = NULL;
            }
            else // One child case
             *node = *temp; // Copy the contents of the non-empty child

            //delete temp;
        }
        else
        {
            // node with two children: Get the inorder successor (smallest
            // in the right subtree)
            T* temp = minValue(node->right);

            // Copy the inorder successor's data to this node
            node->page_id = temp->page_id;

            // Copy the inorder successor's Link address to this node.
            node->self = temp->self; //***watch

            // Delete the inorder successor
            node->right = delete_link(node->right, temp->data);


        }
    }

    // If the tree had only one node then return
    if (node == NULL)
      return node;
    else
    {
       node = balance(node);
       return node;
    }


}


template<class T>
T* AVL<T>::get(int page_id)
{
    return search(root,page_id);
}

/*
 * Insert Element into the tree
 */
template <class T>
T* AVL<T>::insert_link(int page_id)//Search F() for a value is not used.Just Insert is called and if the value already exists it does nothing.
{
    if (root == NULL)
    {
        //root = new node;//Elements tree
        root->page_id = page_id;//   *|*
        root->left = NULL;//   **|**
        root->right = NULL;// ***|***
        root->self = NULL;//Pointer to INTERNAL AVL tree with LINKS
        //node->Link = AVL<link>::insert_link(node->Link,LinkID);//Insert Link to Internal tree.If already exists it does nothing.
    }
    else if (page_id < root->page_id)//In this case the element was not in the tree already.So when the node is NULL it will create space for internal_AVL;.
    {
        root->left.self = insert_link(root->left, page_id);
        root = balance (root);
        return root -> left.self;
    }
    else if (page_id > root->page_id)//In this case the element was not in the tree already.So when the node is NULL it will create space for internal_AVL;.
    {
       root->right.self = insert_link(root->right, page_id);
       root = balance (root);
       return root -> right.self;
    }
    return root -> self;
}

/*
*Insert Link recursion
*/
template <class T>
T* AVL<T>::insert_link(node<T>* node,int page_id)
{
    if(node == NULL)
    {
        //node = new node;//Declaration of New Internal Tree.
        node->page_id = page_id;
        node->left = NULL;
        node->right= NULL;
        node->self = NULL;
        //return node->self;
    }
    else if(page_id < node->page_id)
    {
        node->left = insert_link(node->left,page_id);
        node = balance(node);
    }
    else if(page_id > node->page_id)
    {
        node->right = insert_link(node->right,page_id);
        node = balance(node);
    }
    return node->self;
}

/*
*Counting The nodes of tree  (FOR AVL_NODE ).
*/
template <class T>
int AVL<T>::MBbinarytree_count_recursive(node<T> *node)
{
    int count = 0;
    if (node != NULL)
    {
        count = 1 + MBbinarytree_count_recursive(node->left) + MBbinarytree_count_recursive(node->right);
    }
    return count;
}

/*
*returns Minimum Node address of an AVL tree(avl_node*).
*/
template <class T>
node<T>* AVL<T>::minValue(node<T>* noded)
{
    node<T>* Current = noded;
    while(Current->left != NULL)
    {
        Current = Current->left;
    }
    return Current;
}

template <class T>
node<T>* AVL<T>::search(node<T>* node,int page_id)//searches for the Node in the Tree via its data.
{                               //Returns the address(avl_node*).
    if(page_id > node->page_id)
    {
        return search(node->right,page_id);
    }
    else if(page_id < node->page_id)
    {
        return search(node->left,page_id);
    }
    return node;

}

/*
*Returns true if AVL tree with node as node is height-balanced
*/
template <class T>
bool AVL<T>::isBalanced(node<T>* node)
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
 * Height of AVL Tree
 */
template <class T>
int AVL<T>::height(node<T> *temp)
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
template <class T>
int AVL<T>::diff(node<T> *temp)
{
    int l_height = height (temp->left);
    int r_height = height (temp->right);
    int b_factor= l_height - r_height;
    return b_factor;
}

/*
 * Right Rotation
 */
template <class T>
node<T>* AVL<T>::r_rotation(node<T> *parent)
{
    node<T> *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}
/*
 * Left Rotation
 */
template <class T>
node<T> *AVL<T>::l_rotation(node<T> *parent)
{
    node<T> *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}
/*
 * Left - Right Rotation
 */
template <class T>
node<T> *AVL<T>::lr_rotation(node<T> *parent)
{
    node<T> *temp;
    temp = parent->left;
    parent->left = r_rotation (temp);
    return l_rotation (parent);
}
/*
 * Right- Left Rotation
 */
template <class T>
node<T> *AVL<T>::rl_rotation(node<T> *parent)
{
    node<T> *temp;
    temp = parent->right;
    parent->right = l_rotation (temp);
    return r_rotation (parent);
}
/*
 * Balancing AVL Tree
 */
template <class T>
node<T> *AVL<T>::balance(node<T> *temp)
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
*Inorder Traversal of Internal AVL tree
*/
template <class T>
void AVL<T>::internal_inorder(ofstream& output,node<T>* node)
{
   if(node != NULL)
   {
     internal_inorder(output,node->left);
     output<<node->page_id<<",";
     internal_inorder(output,node->right);
   }
   return;
}

/*
 * Inorder Traversal of AVL Tree //
 */
 /*
template <class T>
void AVL<T>::inorder(ofstream& output,page *node )
{

    if (node != NULL)
    {
        inorder(output,node->left);
        output<<node->data<<","<<"number of links: "<<MBbinarytree_count_recursive(node->Link)<<",links:";
        internal_inorder(output,node->Link);
        output<<endl;
        inorder(output,node->right);
    }

}
*/
template <class T>
void AVL<T>::printTree(ofstream& output){
    internal_inorder(output,root);
    std::cout<<output.rdbuf();
}
