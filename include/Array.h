//Stores links as an array.

#ifndef ARRAY_H
#define ARRAY_H

#include <vector>

class Array
{
    public:
        Array();
        virtual ~Array();
        void insertLink(int page1);
        void show();


    protected:

    private:
        std::vector <int> links;

};

#endif // ARRAY_H
