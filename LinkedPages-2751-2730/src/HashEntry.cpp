//Supportive class for HashTable(pages)
//Contains a page as an integer and a hashTable(links) of all the linked pages to the page.


#include "HashEntry.h"
#include <iostream>

using namespace std;

HashEntry::HashEntry(int page,HashTableLinks& links)
{
    this->page=page;
    key = page;
    LinkedHashEntry *entry;
    for(int j=0; j<links.getTableSize();j++){
        if(links.getAllLinks()[j] != NULL){
            LinkedHashEntry *entry = links.getAllLinks()[j];
            while (entry != NULL){
                this->links.put(entry->getKey(),entry->getValue());
                entry = entry->getNext();
            }
        }
    }
}

HashEntry::HashEntry(int page,int link)
{
    this->page=page;
    key = page;
    links.put(link,link);
}

HashEntry::HashEntry(int deleted)
{
    this->page = deleted; //deleted entry constructor
    HashTableLinks deleted_links;
    links = deleted_links; //?_?
}

int HashEntry::getPage(){
    return page;
}

int HashEntry::getKey(){
    return key;
}

HashTableLinks HashEntry::reseatLinks(){
    return links;
}

HashTableLinks& HashEntry::getLinks(){
    return links;
}

void HashEntry::setLinks(HashTableLinks links){
    this->links=links;
}
