//HashTable with the linked page of the page/key
//Using chaining.

#ifndef HASHTABLELINKS_H
#define HASHTABLELINKS_H

#include "LinkedHashEntry.h"


class HashTableLinks
{
    public:
        HashTableLinks();
        ~HashTableLinks();
        int get(int key);
        void put(int key, int value);
        void remove(int key);
        void setThreshold(float threshold);
        int getTableSize();
        int size;
        LinkedHashEntry ** getAllLinks();

    protected:

    private:
        float threshold;
        int maxSize;
        int tableSize;
        LinkedHashEntry **table;
        void resize();
};

#endif // HASHTABLELINKS_H
