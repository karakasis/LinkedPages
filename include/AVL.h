#ifndef AVL_H
#define AVL_H


class AVL
{
    public:
        AVL();
        virtual ~AVL();

    protected:

    private:
        class AVLTreeNode {

            public:
                AVLTreeNode(){
                    leftChild = rightChild = 0;
                }
                AVLTreeNode(const int d){
                    data = d; leftChild = rightChild = 0;
                }
                AVLTreeNode(const int d, AVLTreeNode *l, AVLTreeNode *r){
                    data = d; leftChild = l; rightChild = r;
                }
                int data;
                AVLTreeNode *leftChild; // left subtree
                AVLTreeNode *rightChild; // right subtree
                virtual ~AVLTreeNode();
            private:

        };
        AVLTreeNode *root;
        bool search(const int e) const;
};

#endif // AVL_H
