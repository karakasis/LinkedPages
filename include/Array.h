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


    protected:

    private:
        std::vector< int > pages;
        std::vector< int > links;
        std::vector< std::pair< int, std::vector<int> > > pairs;

        std::vector<int> initVector(int link);

};

#endif // ARRAY_H
