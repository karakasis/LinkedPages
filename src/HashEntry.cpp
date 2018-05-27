//Supportive class for HashTable(pages)
//Contains a page as an integer and a hashTable(links) of all the linked pages to the page.


#include "HashEntry.h"
#include <iostream>

using namespace std;

HashEntry::HashEntry(int page,HashTableLinks table)
{
    this->page=page;
    links = table;
}

/*
HashEntry::HashEntry(int key,int page,int foo)
{
    this->page=page;
    this->key=key;
    links=NULL;
}
*/

HashEntry::~HashEntry()
{
    //dtor
}

int HashEntry::getPage(){
    return page;
}

int HashEntry::getKey(){
    return key;
}

HashTableLinks HashEntry::getLinks(){
    return links;
}

void HashEntry::setLinks(HashTableLinks links){
    this->links=links;
}
