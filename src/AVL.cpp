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
page* AVL<T>::DELETE_LINK(page* node,int x,int y)
{

    page* temp;
    link* InternalTemp;
    temp = search(node,x); //search searches for a number,if found returns address of node(is overloaded for both internal_avl and avl_node).

    if(temp == NULL)
    {
        return node;//does nothing because node does not exist.
    }
    else
    {

         InternalTemp = search(temp->Link,y); //searches for y in the internal tree.if found return address of node , else returns NULL.

         if(InternalTemp == NULL)
         {
            return node;//does nothing because internal node(link) does not exist.
         }
         else
         {
            temp->Link = delete_link(temp->Link,y);
            /* OR use above to also delete page
            int NumberOfLinks = MBbinarytree_count_recursive(temp->Link);

            if(NumberOfLinks == 1)//if number of links is 1 delete the link and the website that contained the link as well.
            {
              temp->Link = Delete(temp->Link,y);// if y exists in internal tree delete it,else do nothing.
              node = DELETE_TREE(node,x);// delete x as well.
              return node;
            }*/
         }
    }
}

/*
 * Insert Element into the tree
 */
template <class T>
void AVL<T>::insert_link(int page_id,int link_id)//Search F() for a value is not used.Just Insert is called and if the value already exists it does nothing.
{
    if (node == NULL)
    {
        node = new page;//Elements tree
        node->data = value;//   *|*
        node->left = NULL;//   **|**
        node->right = NULL;// ***|***
        node->Link = NULL;//Pointer to INTERNAL AVL tree with LINKS


        node->Link = AVL<link>::insert_link(node->Link,LinkID);//Insert Link to Internal tree.If already exists it does nothing.


        return node;
    }
    else if (value < node->data)//In this case the element was not in the tree already.So when the node is NULL it will create space for internal_AVL;.
    {
        node->left = INSERT_LINK(node->left, value,LinkID);
        node = balance (node);
    }
    else if (value > node->data)//In this case the element was not in the tree already.So when the node is NULL it will create space for internal_AVL;.
     {
       node->right = INSERT_LINK(node->right, value,LinkID);
       node = balance (node);
     }
    else if (value == node->data)//if the value already exists in the tree, Gain access to its INTERNAL TREE and insert the LinkID.If LinkID already exists it does NOTHING.
    {
       node->Link = insert_link(node->Link,LinkID);
    }
    return node;
}

/*
*Insert Link into the INTERNAL tree
*/
template <class T>
T* AVL<T>::insert_link(T* node,int LinkID)
{
    if(node == NULL)
    {
        node = new link;//Declaration of New Internal Tree.
        node->data = LinkID;
        node->left = NULL;
        node->right= NULL;
        return node;
    }
    else if(LinkID < node->data)
    {
        node->left = insert_link(node->left,LinkID);
        node = balance(node);
    }
    else if(LinkID > node->data)
    {
        node->right = insert_link(node->right,LinkID);
        node = balance(node);
    }
    return node;
}

/*
* Internal Tree Deletion.
*/

template <>
link* AVL<link>::delete_link(link* node, int key)//Deletion for internal avl type of struct.
{
    // STEP 1: PERFORM STANDARD BST DELETE

    if (node == NULL)
        return node;

    // If the key to be deleted is smaller than the node's key,
    // then it lies in left subtree
    if ( key < node->data )
        node->left = delete_link(node->left, key);

    // If the key to be deleted is greater than the node's key,
    // then it lies in right subtree
    else if( key > node->data )
        node->right = delete_link(node->right, key);

    // if key is same as node's key, then This is the node
    // to be deleted
    else//IF NODE IS FOUND
    {
        // node with only one child or no child
        if( (node->left == NULL) || (node->right == NULL) )
        {
            link *temp = node->left ? node->left : node->right;//temp is whatever is not NULL.

            // No child case
            if(temp == NULL)
            {
                temp = node;
                node = NULL;
            }
            else // One child case
             *node = *temp; // Copy the contents of the non-empty child

            delete temp;


        }
        else
        {
            // node with two children: Get the inorder successor (smallest
            // in the right subtree)
            link* temp = minValue(node->right);

            // Copy the inorder successor's data to this node
            node->data = temp->data;

            // Copy the inorder successor's Link address to this node.
            //node->Link = temp->Link; //***watch

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

/*
*Counting The nodes of tree  (FOR AVL_NODE ).
*/
template <class T>
int AVL<T>::MBbinarytree_count_recursive(T *node)
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
T* AVL<T>::minValue(T* node)
{
    T* Current = node;
    while(Current->left != NULL)
    {
        Current = Current->left;
    }
    return Current;
}

template <class T>
T* AVL<T>::search(T* node,int data)//searches for the Node in the Tree via its data.
{                               //Returns the address(avl_node*).
    if(node == NULL)//if not found.
    {
        return node;
    }
    if(data == node->data)
    {
        return node;
    }
    else if(data > node->data)
    {
        return search(node->right,data);
    }
    else if(data < node->data)
    {
        return search(node->left,data);
    }
     return NULL;

}

/*
*Returns true if AVL tree with node as node is height-balanced
*/
template <class T>
bool AVL<T>::isBalanced(T* node)
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
int AVL<T>::height(T *temp)
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
int AVL<T>::diff(T *temp)
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
T *AVL<T>::r_rotation(T *parent)
{
    T *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}
/*
 * Left Rotation
 */
template <class T>
T *AVL<T>::l_rotation(T *parent)
{
    T *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}
/*
 * Left - Right Rotation
 */
template <class T>
T *AVL<T>::lr_rotation(T *parent)
{
    T *temp;
    temp = parent->left;
    parent->left = r_rotation (temp);
    return l_rotation (parent);
}
/*
 * Right- Left Rotation
 */
template <class T>
T *AVL<T>::rl_rotation(T *parent)
{
    T *temp;
    temp = parent->right;
    parent->right = l_rotation (temp);
    return r_rotation (parent);
}
/*
 * Balancing AVL Tree
 */
template <class T>
T *AVL<T>::balance(T *temp)
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
void AVL<T>::internal_inorder(ofstream& output,link* node)
{
   if(node != NULL)
   {
     internal_inorder(output,node->left);
     output<<node->data<<",";
     internal_inorder(output,node->right);
   }
   return;
}

/*
 * Inorder Traversal of AVL Tree //
 */
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

template <class T>
void AVL<T>::printTree(ofstream& output){
    inorder(output,root);
    std::cout<<output.rdbuf();
}
