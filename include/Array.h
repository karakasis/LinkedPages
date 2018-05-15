//Stores links as an array.

#ifndef ARRAY_H
#define ARRAY_H

#include <vector>

class Array
{
    public:
        Array();
        virtual ~Array();
        void deleteLink(int page, int link);
        void insertLink(int page, int link);
        std::vector<int> findNeighbors(std::vector<int> linkedPages);
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
        void makeConnectedPair(int linkPage, int link);
        void deleteConnectedLink(int page, int link);
        void insertConnectedLink(int page, int link);
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
