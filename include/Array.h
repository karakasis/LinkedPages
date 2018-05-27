//Stores links as an array.

#ifndef ARRAY_H
#define ARRAY_H

#include <vector>
#include <memory>
#include <iostream>

class Array
{
    //this will only get called during cloning
    void duplicateLinks(Array& cloned){
        for(std::vector<int> row : pairs){
            if(row.size()!=0){ //< is this correct?
                for(int i=1; i<row.size(); i++){
                    cloned.makePair(row[i],row[0]);
                }
            }
        }
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
            {}

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
            //swap(src.cloned, oper.cloned);
            //swap(src.insertions, oper.insertions);
            //swap(src.deletions, oper.deletions);
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
        void quickSort(std::vector<int> &arr,int left, int right);
        int binarySearch(std::vector<int> arr, int l, int r, int x);
        void swapCells(int *xp, int *yp);
        int DFS(Array& cloned);
        void DFSvisit(int u, Array& cloned);
        int *color;

};

#endif // ARRAY_H
