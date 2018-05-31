#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "HashTableLinks.h"
#include "HashEntry.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;




class HashTable
{
    //this will only get called during cloning
    void duplicateLinks(HashTable& cloned){
        for(int i=0; i<tableSize; i++){
            if(table[i]!=NULL){
                HashTableLinks tl = table[i]->getLinks();
                for(int j=0; j<tl.getTableSize();j++){
                    if(tl.getAllLinks()[j] != NULL){
                        LinkedHashEntry *entry = tl.getAllLinks()[j];
                        cloned.createLink(entry->getKey(),table[i]->getPage());
                        while (entry->getNext() != NULL){
                            entry = entry->getNext();
                            cloned.createLink(entry->getKey(),table[i]->getPage());
                        }
                    }
                }
            }
        }
    }

    public:

        //-> ref to: https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom/3279550#3279550 : for copy-swap idiom
        //copy constructor
        HashTable(const HashTable& other)
        : HashTable() // initialize via default constructor, C++11 only
        {
            for(int i=0; i<other.tableSize; i++){
                if(other.table[i]!=NULL && other.table[i]!=HashTable::getDeletedEntry()){
                    put(other.table[i]->getPage(),other.table[i]->getLinks());
                }
            }
        }

        //move constructor c++11
         HashTable(HashTable&& other) noexcept
        : HashTable() // initialize via default constructor, C++11 only
            { swap(*this,other); }

        HashTable& operator=(HashTable operand)
        {
            swap(*this,operand);
            return *this;
        }

        friend void swap(HashTable& src, HashTable& oper) // nothrow
        {
            using std::swap;

            swap(src.table, oper.table);
            swap(src.size, oper.size);
            swap(src.maxSize, oper.maxSize);
            swap(src.tableSize, oper.tableSize);
            swap(src.threshold, oper.threshold);
        }

        HashTable();
        ~HashTable();
        void createLink(int page,int link);
        void insertLink(int page,int link);
        void deleteLink(int page,int link);
        HashTableLinks findNeighbors(int key);
        void findNumConnectedComponents();
        void remove(int page);

        void setThreshold(float thold);
        HashTableLinks get(int key);

        static HashEntry* getDeletedEntry();

    protected:


    private:
        int tableSize;
        float threshold;
        int maxSize;
        int size;
        HashEntry **table;
        void resize();
        void put(int key,HashTableLinks& links);
        int *color;
        int DFS(HashTable& cloned);
        void DFSvisit(int u, HashTable& cloned);
        void bubbleSort(std::vector<int>& sorted, int sizes);

        static HashEntry *deleted_entry;

};

#endif // HASHTABLE_H
