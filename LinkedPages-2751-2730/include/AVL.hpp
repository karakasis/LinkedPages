#ifndef AVL_H
#define AVL_H

#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>
#include <math.h>
#include <tuple>
#include <type_traits>

//using namespace std;

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
    Node root;

    // Helper variables
    std::size_t size;
    bool lockBalance;
    node* saved;
    bool data_found;
    T dummy;

    //this will only get called during cloning
    void duplicateLinks(Node& _node , AVL<T>& avl){ // _node is root of normal tree, avl is cloned tree
        if(_node!=nullptr){
            duplicateLinks(_node -> left, avl); //traverse left tree of 1st avl (normal)
            duplicateInnerLinks((_node->self).getRoot(), _node->unique_id, avl); // 1st argument node of 1st avl = page_node , 2nd arg. = page_id
            duplicateLinks(_node -> right, avl);//traverse right tree of 1st avl (normal)
        }
    }
    //this will only get called during cloning
    void duplicateInnerLinks(auto& _node, var<T> parent_id, AVL<T>& avl){ //(parent node, page_id, cloned avl)
        if(_node!=nullptr){
            duplicateInnerLinks(_node->left,parent_id, avl); // traverse links of normal tree - left
            avl.createLink(_node->unique_id,parent_id); // find link_id and create link insertLink(link,page) in cloned avl.
            duplicateInnerLinks(_node->right,parent_id, avl); // traverse links of normal tree - right
        }
    }

    struct node
        {
            Node left;
            Node right;
            T self; // actual container of an AVL. for a simple AVL<int> that would store the unique_id
                        //in case of AVL<T> self would store the T object f.e an inner AVL.
            var<T> unique_id; // defines the comparable variable of an AVL.
            unsigned char height;
            //basic insertion make_unique
            node(const var<T> id, unsigned char h = 1)
                : self{},
                  left{std::move(nullptr)},
                  right{std::move(nullptr)},
                  height{h}, unique_id{id}
                  {
                      //unique_id = id;
                      //height = h;
                  }

            //clone make_unique
            node(const var<T> id,
             T&& _self,
             Node&& _left,
             Node&& _right,
             unsigned char h)
                : left{std::move(_left)},
                  right{std::move(_right)},
                  self{std::forward<T>(T(_self))}, // notice that T has to support cloning for AVL to retain T for itself
                  height{h}, unique_id{id} {}

                  //replace return with custom implementation. remember var<T> is the innermost type.
                  //f.e if u do AVL<vector<CUSTOM_CLASS>> THEN manage how to compare ur custom classes to balance your AVL.
                  //if ur innermost type is a base type f.e float double int string etc..
                  //then the overload is invalid , since operator overloading is allowed only for user-defined types
                  //and the operation will be handled from c++.
            bool operator< (const var<T> &rhs) { return unique_id<rhs;}
            bool operator> (const var<T> &rhs) { return unique_id>rhs;}
            bool operator== (const var<T> &rhs) { return unique_id == rhs;}
            bool operator!= (const var<T> &rhs) { return unique_id != rhs;}

        };

    public:

        ~AVL() noexcept = default;

        AVL()
        : root(nullptr),lockBalance(false),dummy{-1}
            { size = 0; }

        AVL(int size_dum)
        : root(nullptr),lockBalance(false),dummy{-1}
            { size = size_dum; }

        //-> ref to: https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom/3279550#3279550 : for copy-swap idiom
        //copy constructor
        AVL(const AVL& other)
        : root{clone(other.root)}, size{other.size}, lockBalance(false), dummy{-1}
            { }

        //move constructor c++11
         AVL(AVL&& other) noexcept
        : AVL() // initialize via default constructor, C++11 only
            { swap(*this,other); }

        AVL& operator=(AVL operand)
        {
            swap(*this,operand);
            return *this;
        }

        friend void swap(AVL& src, AVL& oper) // nothrow
        {
            using std::swap;

            swap(src.root, oper.root);
            swap(src.size, oper.size);
        }

        void insertLink(var<T> in, var<T> that)
        {
            std::ofstream out("output.txt", std::ofstream::out | std::ofstream::app);
            out<<"running: insertLink("<<in<<","<<that<<");"<<std::endl;
            out<<std::endl;
            //this is missing the ability to insert a page if it doesnt exist.
            get(in).add(that);
        }

        void createLink(var<T> in, var<T> that)
        {
            //this HAS the ability to insert a page if it doesnt exist.
            add(in).add(that);
        }

        void deleteLink(var<T> from, var<T> that)
        {
            std::ofstream out("output.txt", std::ofstream::out | std::ofstream::app);
            out<<"running: deleteLink("<<from<<","<<that<<");"<<std::endl;
            out<<std::endl;
            get(from).remove(that);
        }

        T& add(var<T> data)
        {
            //size++ will happen inside inner function
            lockBalance = false;
            insert_inner(root,data);
            return saved->self;
        }

        void remove(var<T> unique_id)
        {
            data_found = true;
            delete_inner(root,unique_id);
            if(data_found){
                size--;
            }
        }

        T& get(var<T> key)
        {
            data_found = false;
            find(root,key);
            return data_found  ? saved->self : dummy;
        }

        bool contains(var<T> key)
        {
            data_found = false;
            find(root,key);
            return data_found;
        }

        Node& getRoot(){
            return this -> root;
        }

        std::vector<var<T>> getNodes(){
            std::vector<var<T>> nodes;
            getNodes_inorder(nodes,root);
            return nodes;
        }

        std::size_t getSize(){
            return size;
        }

        /**
        Find amount of connected components of a 2-dimensional bi-directional graph

        @param AVL must be a nested structure of type AVL < AVL < type > >.
        */
        std::vector<std::vector<var<T>>> connected(){
            std::ofstream out("output.txt", std::ofstream::out | std::ofstream::app);
            out<<"running: findNumConnectedComponents();"<<std::endl;
            std::cout<<"Cloning ..."<<std::endl;
            AVL<T> clone(*this);
            duplicateLinks(root, clone);
            std::cout<<"Finding connected components ... "<<std::endl;
            //duplicateInstructions(clone);

            AVL<var<T>> memory; //memory inside an AVL to skip traversed nodes
            std::vector<std::vector<var<T>>> connected_components; //will keep component's ids
            connected_inner(clone.root, memory,connected_components,clone);//start
            return connected_components;
        }

        /**
        Find neighbors of node of a 2-dimensional bi-directional graph
        where node consists of its inner avl.

        @param AVL must be a nested structure of type AVL < AVL < type > >.
        @return a vector of var<T> with all neighbor-nodes.
        */
        std::vector<var<T>>& findNeighbors(var<T> id){
            std::ofstream out("output.txt", std::ofstream::out | std::ofstream::app);
            out<<"running: findNeighbors("<<id<<");"<<std::endl;
            std::vector<var<T>> neig;
            T found = get(id);
            if(found.getSize() == -1){
                out<<"page "<<id<<" doesn't exist."<<std::endl;
            }else{
                findNeighbors(neig, found.getRoot());
            }
            out<<"[ ";
            for(var<T> sibl : neig){
                out<<sibl<<" ";
            }
            out<<"]"<<std::endl;
            out<<std::endl;
            return neig;
        }

        void findNeighbors(std::vector<var<T>>& vec, auto& _node){
            if(_node!=nullptr){
                findNeighbors(vec, _node->left);
                vec.push_back(_node->unique_id);
                findNeighbors(vec, _node->right);
            }
        }

        //PRINTER functions////

        void connected(AVL<T>& avl){
            std::ofstream out("output.txt", std::ofstream::out | std::ofstream::app);
            std::vector<std::vector<var<T>>> connected_components = connected();
            int size_con_comp = connected_components.size();
            out<<"Connected Components: "<<size_con_comp<<std::endl;
            for(int i=0; i<size_con_comp; i++){
                out<<"cmp.["<<i<<"]"<<std::endl;
                if(connected_components.at(i).size()<=100){
                    out<<"\t[ ";
                    for(int id : connected_components.at(i)){
                        out<<id<<" ";
                    }
                    out<<"]";
                }
                else
                    out<<"\t Component's size is bigger than 100. Print skipped."<<std::endl;
                out<<std::endl;
            }
        }

        void print(std::ostream& out){
            if (size == 0) out<< "{ }";
            else if(size == -1) return;
            else{
                out<< "{ ";
                internal_inorder(out,root);
                out << "}"<<std::endl;
            }

        }

        void print_all_tree(std::ostream& out, AVL<T>& avl){
            std::cout<<"Trees printed in outputstream"<<std::endl;
            out<<"-->Parent tree<--"<<std::endl;
            avl.print_level(out,1,1,3);
            out<<std::endl;
            out<<std::endl;
            for(var<T> page : avl.getNodes()){
                out<<"-->"<<page<<"<--"<<std::endl;
                avl.get(page).print_level(out,1,1,3);
                out<<std::endl;
                out<<std::endl;
                out<<"-->"<<page<<"<--"<<std::endl;
                avl.get(page).print(out);
                out<<std::endl;
                out<<std::endl;
                out<<std::endl;
            }
        }

        /* Function to print level order traversal a tree*/
        void print_level(std::ostream& output,int v_scale, int h_scale, int max_num_length)
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

            std::string stand_in = "[";
            for(int i=0; i<max_num_len-2; i++){
                stand_in += " ";
            }
            stand_in += "]";

            std::string min_whites;// std::setw(min_whitespace);
            for(int i=0; i<min_whitespace; i++){
                min_whites += " ";
            }

            std::string max_whites;
            for(int i=0; i<max_whitespace; i++){
                max_whites += " ";
            }

            std::string index_padding = "\t\t\t\t";

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
                    output<<std::endl;
            }
        }

    private:

        //PRINTER functions////

        /*
        *Inorder Traversal of Internal AVL<T> tree
        */
        void internal_inorder(std::ostream& output,Node& _node)
        {
           if(_node != nullptr)
           {
             internal_inorder(output,_node->left);
             output<<_node->unique_id<<" ";
             internal_inorder(output,_node->right);
           }
        }

        //not working i think and if it does its against implementations logic
        //the user must stand responsible for his iterations on combined trees.
        void print_inner(std::ostream& output, const Node& _node) const noexcept
        {
            if (_node != nullptr) {
                *(_node->self).print();
                print(_node->left);
                output << _node->unique_id << " ";
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

        void getNodes_inorder(std::vector<var<T>>& nodes, Node& _node){
            if (_node != nullptr) {
             getNodes_inorder(nodes,_node->left);
             nodes.push_back(_node->unique_id);
             getNodes_inorder(nodes,_node->right);
            }
        }

        void connected_inner(Node& _node, AVL<var<T>>& memory
               , std::vector<std::vector<var<T>>>& connected_components, AVL<T>& avl)
       {

            if(_node != nullptr){
            //std::cout<<"here"<<std::endl;
                connected_inner(_node->left, memory, connected_components, avl); //traverse to left of 1st avl
                if(!memory.contains(_node->unique_id)){ //if node hasnt been assigned to a component

                    std::vector<var<T>> comp; //start a new component
                    comp.push_back(_node->unique_id); //store component's id
                    memory.add(_node->unique_id); //write node to memory avl
                    int vec_size = comp.size();//save prev size
                    int cur_node_id = _node->unique_id;
                    do{ //repeat
                        connected_links(avl.get(cur_node_id).getRoot(),memory,comp); //traverse links of 2nd avl
                        cur_node_id = comp[vec_size-1]; //refresh new size of component
                        vec_size++; //check next element in component
                    }while(comp.size() > vec_size); //until no new nodes have not been traversed

                    connected_components.push_back(comp); // finally store component
                }
                connected_inner(_node->right,memory, connected_components, avl); // traverse to right of 1st avl;
            }
        }

        void connected_links(auto& _node, AVL<var<T>>& memory , std::vector<var<T>>& comp){
            if(_node != nullptr){
                connected_links(_node->left, memory, comp); //traverse to left of 2nd avl

                if(!memory.contains(_node->unique_id)){ //if node hasnt been assigned to a component
                    comp.push_back(_node->unique_id);//store component's id to current component
                    memory.add(_node->unique_id);//write node to memory avl
                }

                connected_links(_node->right,memory, comp); // traverse to right of 2nd avl;
            }
        }

        //Cloning////
        Node clone(const Node& _node) const
        {
            if (_node == nullptr) return nullptr;
            else
                return std::make_unique<node>(
                          std::forward<var<T>>(_node->unique_id),
                          std::forward<T>(_node->self),
                          clone(_node->left),
                          clone(_node->right),
                          _node->height
                          );
        }

        //AVL private functions////
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
        }

        void rotateright(Node& _node)
        {
            auto temp = std::move(_node -> left);
            _node -> left = std::move(temp -> right);

            fixheight(_node);
            fixheight(temp);

            temp -> right = std::move(_node);
            _node = std::move(temp);
        }

        void rotateleft(Node& _node)
        {
            auto temp = std::move(_node->right);
            _node->right = std::move(temp->left);

            fixheight(_node);
            fixheight(temp);

            temp->left = std::move(_node);
            _node = std::move(temp);
        }


        void find(Node& _node,var<T> key)
        {
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
