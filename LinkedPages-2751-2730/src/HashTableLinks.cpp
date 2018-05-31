#include "HashTableLinks.h"
#include <iostream>

using namespace std;

HashTableLinks::HashTableLinks()
{
    threshold = 0.75f;
    maxSize = 36;
    tableSize = 48;
    size = 0;
    table = new LinkedHashEntry*[tableSize];
    for (int i = 0; i < tableSize; i++)
        table[i] = NULL;
}

HashTableLinks::~HashTableLinks()
{/*
    for (int i = 0; i < tableSize; i++)
      if (table[i] != NULL) {
            LinkedHashEntry *temp = NULL;
            LinkedHashEntry *entry = table[i];
            while (entry != NULL)
            {
                temp = entry->getNext();
                delete entry;
                entry = temp;
            }
      }
     delete[] table;*/
}

void HashTableLinks::setThreshold(float threshold)
{
    this->threshold = threshold;
    maxSize = (int) (tableSize * threshold);
}

int HashTableLinks::get(int key)
{
    int hash = (key % tableSize);
    if (table[hash] == NULL)
        return -1;
    else
    {
        LinkedHashEntry *entry = table[hash];
        while (entry != NULL && entry->getKey() != key)
            entry = entry->getNext();
        if (entry == NULL)
            return -1;
        else
            return entry->getValue();

    }

}

//key=page=value
void HashTableLinks::put(int key, int value)
{
    int hash = (key % tableSize);
    //cout<<"hash of key "<<key<<" is " << hash<<endl;
    if (table[hash] == NULL)
    {
        //cout<<"found empty"<<endl;
        table[hash] = new LinkedHashEntry(key, value);
        size++;
    }
    else
    {
        //cout<<"occupied"<<endl;
        LinkedHashEntry *entry = table[hash];
        while (entry->getNext() != NULL){
            entry = entry->getNext();
            if (entry->getKey() == key){
                entry->setValue(value);
                break;
            }

        }
        if (entry->getKey() != key){
            entry->setNext(new LinkedHashEntry(key, value));
            size++;
        }
    }
    if (size >= maxSize)
        resize();
}



void HashTableLinks::resize()
{
    int oldTableSize = tableSize;
    tableSize *= 2;
    maxSize = (int) (tableSize * threshold);
    LinkedHashEntry **oldTable = table;
    table = new LinkedHashEntry*[tableSize];
    for (int i = 0; i < tableSize; i++)
        table[i] = NULL;
    size = 0;
    for (int hash = 0; hash < oldTableSize; hash++)
        if (oldTable[hash] != NULL)
        {
            LinkedHashEntry *oldEntry;
            LinkedHashEntry *entry = oldTable[hash];
            while (entry != NULL)
            {
                put(entry->getKey(), entry->getValue());
                oldEntry = entry;
                entry = entry->getNext();
                delete oldEntry;
            }
        }
    delete[] oldTable;
}


void HashTableLinks::remove(int key)
{
    int hash = (key % tableSize);
    if (table[hash] != NULL)
    {
        LinkedHashEntry *prevEntry = NULL;
        LinkedHashEntry *entry = table[hash];
        while (entry->getNext() != NULL && entry->getKey() != key)
        {
            prevEntry = entry;
            entry = entry->getNext();
        }
        if (entry->getKey() == key)
        {
            if (prevEntry == NULL)
            {
                LinkedHashEntry *nextEntry = entry->getNext();
                delete entry;
                table[hash] = nextEntry;
            }
            else
            {
                LinkedHashEntry *next = entry->getNext();
                delete entry;
                prevEntry->setNext(next);

            }
            size--;
        }
    }
}

int HashTableLinks::getTableSize(){return tableSize;}


LinkedHashEntry ** HashTableLinks::getAllLinks(){return table;}


