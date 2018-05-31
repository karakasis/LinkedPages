//Support struct for HashTable
//contains the pair of a page and a HashTableLinks of its linked pages.
#ifndef HASHENTRY_H
#define HASHENTRY_H

#include "HashTableLinks.h"


class HashEntry
{
    public:
        //Constructor for hashtable
        HashEntry(int page,HashTableLinks& table);
        HashEntry(int page,int link);
        HashEntry(int deleted);

        int getPage();
        int getKey();
        HashTableLinks reseatLinks();
        HashTableLinks& getLinks();
        void setLinks(HashTableLinks links);

    protected:

    private:
        int page;
        int key;
        HashTableLinks links;
};

#endif // HASHENTRY_H
