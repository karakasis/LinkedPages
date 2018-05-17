#ifndef AVL_H
#define AVL_H


class AVL
{
    public:
        AVL();
        virtual ~AVL();

    protected:

    private:
        template <class T>
        class AVLTreeNode {

            public:
                AVLTreeNode(){
                    leftChild = rightChild = 0;
                }
                AVLTreeNode(const T& e){
                    data = e; leftChild = rightChild = 0;
                }
                AVLTreeNode(const T& e, AVLTreeNode *l, AVLTreeNode *r){
                    data = e; leftChild = l; rightChild = r;
                }
                virtual ~AVLTreeNode();
            private:
                T data;
                AVLTreeNode<T> *leftChild; // left subtree
                AVLTreeNode<T> *rightChild; // right subtree

        };
        AVLTreeNode<T> *root;
        template <typename K, typename T>
        bool search(const K& k, T &e) const;
};

#endif // AVL_H
