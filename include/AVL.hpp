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
#include <memory>
#include <tuple>
#include <type_traits>

using namespace std;

/*
 * Class Declaration
 */
 //https://stackoverflow.com/questions/25187323/how-can-i-get-the-innermost-template-parameter-type?rq=1
template <class K>
struct innermost_impl
{
    using type = K;
};

template<template<typename> class E, typename K>
struct innermost_impl<E<K>>
{
    using type = typename innermost_impl<K>::type;
};

template<template<typename...> class E, typename... Ks>
struct innermost_impl<E<Ks...>>
{
    using type = std::tuple<typename innermost_impl<Ks>::type...>;
};

template<typename K>
using var = typename innermost_impl<K>::type;

template<class>
struct X;

static_assert(std::is_same<var<X<X<X<int>>>>, int>::value, "");


template <class T>
class AVL
{
    struct node;
    typedef std::unique_ptr<node> Node;
    //typedef std::unique_ptr<T> Data;

    struct node
        {
            Node left;
            Node right;
            T self; // actual container of an AVL. for a simple AVL<int> that would store the unique_id
                        //in case of AVL<T> self would store the T object f.e an inner AVL.
            var<T> unique_id; // defines the comparable variable of an AVL.
            unsigned char height;

            node(const var<T> id, unsigned char h = 1)
                : self{},
                  left{std::move(nullptr)},
                  right{std::move(nullptr)},
                  height{h}, unique_id{id}
                  {
                      //unique_id = id;
                      //height = h;
                  }

        };

    Node root;
    // Number of elements
    std::size_t size;
    bool lockBalance;
    node* saved;
    bool data_found;
    T dummy;

    public:

        AVL() : root(nullptr),lockBalance(false),dummy{-1} { size = 0; }

        AVL(int size_dum) : root(nullptr),lockBalance(false),dummy{-1} { size = size_dum; }

        //template<typename X = T>
        T& add(var<T> data)//Search F() for a value is not used.Just Insert is called and if the value already exists it does nothing.
        {
            //size++ will happen inside inner function
            lockBalance = false;
            insert_inner(root,data);
            return saved->self;
        }

        void remove(var<T> unique_id)
        {
            //bool deleted = false;
            //node* temp = find(root,unique_id); //find findes for a number,if found returns address of node(is overloaded for both internal_avl and avl_node).
            //node* temp =
            data_found = true;
            delete_inner(root,unique_id); //find findes for a number,if found returns address of node(is overloaded for both internal_avl and avl_node).
            if(data_found){
                size--;
            }
            //if(temp!=NULL) deleted = true;
            //temp == NULL;
            //return deleted;
        }

        T& get(var<T> key)
        {
            data_found = false;
            find(root,key);
            return data_found  ? saved->self : dummy;
        }


        void print(ofstream& output){
            if (size == 0) output<< "{ }";
            else if(size == -1) return;
            else{
                output<< "{ ";
                internal_inorder(output,root);
                output<<"}"<<std::endl;
                //std::cout<<output.rdbuf();
            }

        }

        void print_cmd() const noexcept
        {
            if (size == 0) std::cout << "{}\n";
            else if(size == -1) return;
            else {
                std::cout << "{";
                internal_inorder_cmd(root);
                std::cout << "\b\b}\n";
            }
        }

        Node& getRoot(){
            return this -> root;
        }

        /* Function to print level order traversal a tree*/
        void printLevelOrder(ofstream& output,int v_scale, int h_scale, int max_num_length)
        {
            std::vector<std::vector<var<T>>> memory;
            int h = height_helper(root);
            int i;
            for(int i = 0; i< h; i++){
                memory.insert(memory.begin() +i,std::vector<var<T>>(0));
            }
            for (i=0; i<h; i++){
                //std::vector<var<T>> dum;
                printGivenLevel(root, i, memory.at(i));
            }

            int tree_height = h;
            int h_tree_scale = h_scale;
            int v_tree_scale = v_scale;
            int max_num_len = max_num_length; // _______
            int max_base_len = pow(2,tree_height); // 2^h
            int min_whitespace = 1*h_tree_scale;// "   "
            int max_whitespace = 2*h_tree_scale;// "      "
            int max_base_size = max_base_len*max_num_len
                                + ((int)(max_base_len/2) * max_whitespace) //inner spaces
                                + ((int)((max_base_len/2))-1 * min_whitespace); //outer spaces
            int prefix_padding;
            int suffix_padding;
            int level_whitespace = 2*max_num_len + min_whitespace + max_whitespace;
            int level_padding = max_num_len + max_whitespace/2;//+ min_whitespace*0/2

            string stand_in = "[";
            for(int i=0; i<max_num_len-2; i++){
                stand_in += " ";
            }
            stand_in += "]";

            string min_whites;
            for(int i=0; i<min_whitespace; i++){
                min_whites += " ";
            }

            string max_whites;
            for(int i=0; i<max_whitespace; i++){
                max_whites += " ";
            }

            string index_padding = "\t\t\t\t";

            std::vector<var<T>> level;
            int level_len;
            int record_len;
            int record;
            int lvl_whitespace;
            int lvl_padding;
            //                          for each level
            for (int cur_level=1;cur_level<=tree_height;cur_level++)
            {
                //                      reset variables
                lvl_whitespace = level_whitespace;
                lvl_whitespace = lvl_whitespace*(pow(2,tree_height - cur_level-1)) - max_num_len;
                lvl_padding = level_padding;
                lvl_padding = (int) ( ( lvl_padding*pow(2,tree_height - cur_level - 1) )
                                               + min_whitespace*( pow(2,tree_height - cur_level - 1) -1 )/2
                                               - max_num_len/2 );
                level = memory.at(cur_level-1);
                level_len = level.size();

                //                leave spaces until first write
                output<<index_padding;
                for (int j=0;j<lvl_padding;j++)
                    output<<" ";
                //                 for each record in the  level
                for(int i=0; i<level_len; i++){

                    //            center the record horizontally
                    record_len = 1;
                    record = level.at(i);
                    //         find the prefix and suffix of the record
                    if (record > 0) for (record_len = 0; record > 0; record_len++) record = record / 10;
                    prefix_padding = (int) (max_num_len - record_len) / 2;
                    suffix_padding = max_num_len - record_len - prefix_padding;

                    //                  output the record
                    if(level.at(i)==-1) output<<stand_in;
                    else{
                        for(int i=0; i<prefix_padding; i++) output<<" ";
                        output<<level.at(i);
                        for(int i=0; i<suffix_padding; i++) output<<" ";
                    }
                    //                output the whitespaces
                    if(tree_height - cur_level == 0){
                        if( i % 2 == 0) output<<min_whites;
                        else output<<max_whites;
                    }else{
                        for(int k=0; k<lvl_whitespace; k++){
                            output<<" ";
                        }
                    }
                }
                //              leave new lines based on vertical scale
                for(int i=0; i<v_tree_scale;i++)
                    output<<endl;
            }
        }

    private:

        //PRINTER functions////

        /*
        *Inorder Traversal of Internal AVL<T> tree
        */
        void internal_inorder(ofstream& output,Node& _node)
        {
           if(_node != nullptr)
           {
             internal_inorder(output,_node->left);
             output<<_node->unique_id<<" ";
             internal_inorder(output,_node->right);
           }
        }

        void internal_inorder_cmd(const Node& _node) const noexcept
        {
            if (_node != nullptr) {
                internal_inorder_cmd(_node->left);
                std::cout << _node->unique_id << ", ";
                internal_inorder_cmd(_node->right);
            }
        }
        //not working i think
        void print_inner(const Node& _node) const noexcept
        {
            if (_node != nullptr) {
                *(_node->self).print();
                print(_node->left);
                std::cout << _node->unique_id << ", ";
                print(_node->right);
            }
        }

        /* Print nodes at a given level */
        void printGivenLevel(Node& _node, int level,std::vector<var<T>>& memory)
        {
            //bool stop = false;
            if (_node == nullptr){
                memory.push_back(-1);//this is for int or define ur own for var<T>
                return;
            }
            if (level == 0){
                memory.push_back(_node->unique_id);
                //cout<<_node->unique_id;
            }
            else if (level > 0)
            {
                printGivenLevel(_node->left, level-1,memory);
                printGivenLevel(_node->right, level-1,memory);
            }
        }

        /* Compute the "height" of a tree -- the number of
            nodes along the longest path from the root node
            down to the farthest leaf node.*/
        int height_helper(Node& _node)
        {
            if (_node==nullptr)
                return 0;
            else
            {
                /* compute the height of each subtree */
                int lheight = height_helper(_node->left);
                int rheight = height_helper(_node->right);

                /* use the larger one */
                if (lheight > rheight)
                    return(lheight+1);
                else return(rheight+1);
            }
        }
        //Internal_AVL functions////
        /*
        * Delete link recursion
        */
        void delete_inner(Node& _node, var<T> key)//Deletion for internal avl type of struct.
        {
            // STEP 1: PERFORM STANDARD BST DELETE

            if (_node == nullptr){
                data_found = false;
               return;
            }

            // If the key to be deleted is smaller than the node's key,
            // then it lies in left subtree
            if ( key < _node -> unique_id )
                delete_inner(_node -> left, key);

            // If the key to be deleted is greater than the node's key,
            // then it lies in right subtree
            else if( key > _node -> unique_id )
                delete_inner(_node -> right, key);
            // if key is same as node's key, then This is the node
            // to be deleted
            else if(_node -> left != nullptr && _node -> right != nullptr)//IF NODE IS FOUND
            { //basically find the smallest element of the right'est tree
               auto temp = findmin(_node->right).get(); //while travesing the left'est trees
               _node -> self = std::move(temp -> self);//fetch inner data
               _node -> unique_id = temp -> unique_id;//and replace id (while keeping siblings)
              //and issue a new delete for that element starting from the right sub-tree
              //of the current node ( the one that we initially want to delete )
              //we also replaced the unique_id of the "deleted" node with that element
              delete_inner(_node -> right, _node -> unique_id);

            }else{//finally arrive in that element that will def not have a left child
                  //considering its the smallest element but might or might not have
                  //a right child. Another case is to land in this else in the 1st issue
                  //of deletion meaning that the node holding the element of deletion had only
                  // 1 child or none. (if leaf) in that case we owe to check for left child.
                  Node temp = std::move(_node); //basically deleted and then
                  _node = (temp -> left != nullptr) ? std::move(temp->left) :
                                                   std::move(temp->right);//null or not
                 //..so if there is a left child(or subtree) move it in place of its parent
                 //which in 1st case would be the node holding the element of deletion.
                 //In the 2nd case however we arrived here because we found the smallest Element
                 //of the right'est subtree and since there is no left child
                 //we move to the parent of the smallest element, its right sub-tree(n or !n)
            }

            balance(_node);
        }

        Node& findmin(Node& _node) // finding the node with the minimal key in p tree
        {
            //auto temp = _node.get(); //raw pointer
            if(_node -> left == nullptr){
              return _node;
            }
            findmin(_node -> left);
            //return p->left?findmin(p->left):p;
        }

        /*
        *Insert Link recursion
        */
        void insert_inner(Node& _node,var<T> data)
        {

          if (_node == nullptr)
          {
              size++;
              _node = std::make_unique<node>(std::forward<var<T>>(data));
              saved = _node.get();
              return;
          }
          else if(data == _node -> unique_id){
              //no new insertion but return inner data
              lockBalance = true;
              saved = _node.get();
              return;
          }
          else if (data < _node -> unique_id)//In this case the element was not in the tree already.So when the node is NULL it will create space for internal_AVL<T>;.
          {
              insert_inner(_node->left, data);
          }
          else if (data > _node -> unique_id)//In this case the element was not in the tree already.So when the node is NULL it will create space for internal_AVL<T>;.
          {
              insert_inner(_node->right, data);
          }
          if(!lockBalance)
            balance(_node);
        }

        unsigned char height(Node& _node)
        {
            if(_node == nullptr) return 0;
            else return _node -> height;
            //return _node ? _node -> height : 0;
        }

        int bfactor(Node& _node)
        {
            return height(_node -> right) - height(_node -> left);
        }

        void fixheight(Node& _node)
        {
            unsigned char hl = height(_node -> left);
            unsigned char hr = height(_node -> right);
            //_node -> height = (hl > hr ? hl : hr) + 1;
            if( hl > hr) _node -> height = hl + 1;
            else _node -> height = hr + 1;
        }

        /*
         * Balancing AVL<T> Tree
         */
        void balance(Node& _node)
        {
            if(_node == nullptr) return;
            fixheight(_node);
            if( bfactor(_node) == 2 )
            {
                if( bfactor(_node->right) < 0 )
                    rotateright(_node->right);
                rotateleft(_node);
            }
            if( bfactor(_node) == -2 )
            {
                if( bfactor(_node->left) > 0  )
                    rotateleft(_node->left);
                rotateright(_node);
            }
            //return _node; // no balance needed
        }

        void rotateright(Node& _node) // the right rotation round p
        {
            auto temp = std::move(_node -> left);
            _node -> left = std::move(temp -> right);

            fixheight(_node);
            fixheight(temp);

            temp -> right = std::move(_node);
            _node = std::move(temp);
        }

        void rotateleft(Node& _node) // the left rotation round q
        {
            auto temp = std::move(_node->right);
            _node->right = std::move(temp->left);

            fixheight(_node);
            fixheight(temp);

            temp->left = std::move(_node);
            _node = std::move(temp);
        }


        void find(Node& _node,var<T> key)//findes for the Node in the Tree via its data.
        {                               //Returns the address(avl_node*).
            if(_node == nullptr) return;
            else if(key == _node -> unique_id){
                data_found = true;
                saved = _node.get();
                return;
            }
            else if(key > _node->unique_id)
            {
                find(_node->right,key);
            }
            else if(key < _node->unique_id)
            {
                find(_node->left,key);
            }
        }

};

#endif // AVL_H
