#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "HashTableLinks.h"
#include "HashEntry.h"
#include <iostream>

using namespace std;


class HashTable
{
    public:
        HashTable();
        ~HashTable();
        void setThreshold(float thold);
        HashTableLinks get(int key);
        void put(int page,HashTableLinks links);
        void remove(int page);

    protected:


    private:
        int tableSize;
        float threshold;
        int maxSize;
        int size;
        HashEntry **table;
        void resize();

};

#endif // HASHTABLE_H
