//Stores links as an array.

#ifndef ARRAY_H
#define ARRAY_H

#include <vector>
#include <memory>
#include <iostream>

class Array
{

    struct instructions;
    typedef std::unique_ptr<instructions> Instructions;

    struct instructions{
        Array *cloned; //= new Array(1);
        //cloned(1);
        std::vector<std::vector<int>> insertions;
        std::vector<std::vector<int>> deletions;

        //basic insertion make_unique
        instructions() {}

        //clone make_unique
        instructions(const Array & _main,
                     std::vector<std::vector<int>> & _insertions,
                     std::vector<std::vector<int>> & _deletions)
            :   cloned{new Array(_main)},
                insertions{_insertions},
                deletions{_deletions}
            {
                //here we duplicate all previous calls and then clear the vectors
                for(std::vector<int> pairs : insertions){
                    cloned->insertLink(pairs[0],pairs[1]);
                    cloned->insertLink(pairs[1],pairs[0]);
                }
                for(std::vector<int> pairs : deletions){
                    cloned->deleteLink(pairs[0],pairs[1]);
                    cloned->deleteLink(pairs[1],pairs[0]);
                }
                insertions.clear();
                deletions.clear();
                _insertions.clear();
                _deletions.clear();
            }
    };

        //Cloning Instructor////
    Instructions clone(const Instructions& instructor) const
    {
        if (instructor == nullptr) return nullptr;
        else
            return std::make_unique<instructions>(
                      *this,
                      instructor->insertions,
                      instructor->deletions
                      );
    }

    Instructions instructor;

    public:

        ~Array() noexcept
        {
            //delete instructor->cloned; seg fault
        }

        Array(unsigned char mem = 1) : instructor{std::make_unique<instructions>()}  {
            allocationStep = mem;
            reAllocVector();
            reAllocConnectedVector();
            };

        //-> ref to: https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom/3279550#3279550 : for copy-swap idiom
        //copy constructor
        Array(const Array& other)
        : pairs{other.pairs}, allocationStep{other.allocationStep} , instructor{clone(other.instructor)}
            {std::cout<<"copy trigger"<<std::endl; }

        //move constructor c++11
         Array(Array&& other) noexcept
        : Array(other.allocationStep) // initialize via default constructor, C++11 only
            { std::cout<<"move trigger"<<std::endl; swap(*this,other); }

        Array& operator=(Array operand)
        {
            std::cout<<"assign trigger"<<std::endl;
            swap(*this,operand);
            return *this;
        }

        friend void swap(Array& src, Array& oper) // nothrow
        {
            using std::swap;

            std::cout<<"swap trigger 1"<<std::endl;
            swap(src.pairs, oper.pairs);
            std::cout<<"swap trigger 2"<<std::endl;
            swap(src.allocationStep, oper.allocationStep);
            std::cout<<"swap trigger 3"<<std::endl;
            swap(src.instructor, oper.instructor);
            std::cout<<"swap trigger 4"<<std::endl;
        }

        int allocationStep;
        void deleteLink(int page, int link);
        void insertLink(int page, int link);
        void findNeighbors(int page);
        int findNumConnectedComponents();

        void makePair(int linkPage, int link);
        void show(std::vector<std::vector<int>> vec);
        void printer();
        void sortLinks();
        void sortConnectedLinks();

        //put those in private b4 sending
        std::vector< std::vector<int> > pairs;
        std::vector< std::vector<int> > connectedPairs;

    protected:

    private:
        void makeConnectedPairStart(int linkPage, int link);
        void makeConnectedPairEnd(int linkPage, int link);
        void deleteConnectedLinkStart(int page, int link);
        void insertConnectedLinkStart(int page, int link);
        void deleteConnectedLinkEnd(int page, int link);
        void insertConnectedLinkEnd(int page, int link);
        std::vector<int> findNeighbors(std::vector<int> linkedPages);
        void reAllocVector();
        void reAllocConnectedVector();

        void bubbleSort(std::vector<int> &arr, int n);
        int binarySearch(std::vector<int> arr, int l, int r, int x);
        void swapCells(int *xp, int *yp);
        int DFS();
        void DFSvisit(int u);
        int *color;

};

#endif // ARRAY_H
