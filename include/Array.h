//Stores links as an array.

#ifndef ARRAY_H
#define ARRAY_H

#include <vector>

class Array
{
    public:
        Array();
        virtual ~Array();
        void insertPage(int page);
        void insertLink(int link);
        void makePair(int linkPage, int link);
        void show();
        void printer();
        void sortLinks();
        void deleteLink(int page, int link);
        void insertLink(int page, int link);




    protected:

    private:
        std::vector< int > pages;
        std::vector< int > links;
        std::vector< std::vector<int> > pairs;
        //std::vector<int> initVector(int link);
        std::vector<int> getLinkedPages(std::vector<int> linkedPages);
        int binarySearch(std::vector<std::vector<int>> arr, int l, int r, int x);
        void swap1d(int *xp, int *yp);
       // void swap2d(std::vector *xp, std::vector *yp);
        void bubbleSort1d(std::vector<int> &arr, int n);
        void bubbleSort2d(std::vector<std::vector<int>> &arr, int n);
        int binarySearch1D(std::vector<int> arr, int l, int r, int x);
        void reAllocVector();



};

#endif // ARRAY_H
