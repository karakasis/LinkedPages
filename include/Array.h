//Stores links as an array.

#ifndef ARRAY_H
#define ARRAY_H

#include <vector>
#include <memory>
#include <iostream>

class Array
{
    Array *cloned;
    std::vector<std::vector<int>> insertions;
    std::vector<std::vector<int>> deletions;

    void duplicateInstructions(){

        for(std::vector<int> pairs : insertions){
            cloned->makePair(pairs[0],pairs[1]);
            cloned->makePair(pairs[1],pairs[0]);
        }
        for(std::vector<int> pairs : deletions){
            cloned->deleteLink(pairs[0],pairs[1]);
            cloned->deleteLink(pairs[1],pairs[0]);
        }
        insertions.clear();
        deletions.clear();
    }

    //this will only get called during cloning and only from the clone object
    void duplicateLinks(){
        std::vector<std::vector<int>> clonePairs(pairs);
        for(std::vector<int> row : clonePairs){
            if(row.size()!=0){ //< is this correct?
                for(int i=1; i<row.size(); i++){
                    makePair(row[i],row[0]);
                }
            }
        }
        clonePairs.clear();
    }


    public:

        ~Array() noexcept
        {
            //delete instructor->cloned; seg fault
        }

        Array(unsigned char mem = 1) {
            allocationStep = mem;
            reAllocVector();
        }

        //-> ref to: https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom/3279550#3279550 : for copy-swap idiom
        //copy constructor
        Array(const Array& other)
        : pairs{other.pairs}, allocationStep{other.allocationStep}
            {duplicateLinks(); }

        //move constructor c++11
         Array(Array&& other) noexcept
        : Array(other.allocationStep) // initialize via default constructor, C++11 only
            { swap(*this,other); }

        Array& operator=(Array operand)
        {
            swap(*this,operand);
            return *this;
        }

        friend void swap(Array& src, Array& oper) // nothrow
        {
            using std::swap;

            swap(src.pairs, oper.pairs);
            swap(src.allocationStep, oper.allocationStep);
            swap(src.cloned, oper.cloned);
            swap(src.insertions, oper.insertions);
            swap(src.deletions, oper.deletions);
        }

        int allocationStep;
        void deleteLink(int page, int link);
        void insertLink(int page, int link);
        void findNeighbors(int page);
        void findNumConnectedComponents();

        void makePair(int linkPage, int link);
        void show(std::vector<std::vector<int>> vec);
        void printer();
        void sortLinks();
        void sortConnectedLinks();

        //put those in private b4 sending
        std::vector< std::vector<int> > pairs;

    protected:

    private:
        std::vector<int> findNeighbors(std::vector<int> linkedPages);
        void reAllocVector();

        void bubbleSort(std::vector<int> &arr, int n);
        int binarySearch(std::vector<int> arr, int l, int r, int x);
        void swapCells(int *xp, int *yp);
        int DFS();
        void DFSvisit(int u);
        int *color;

};

#endif // ARRAY_H
