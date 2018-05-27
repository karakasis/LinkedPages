//Parent class of HashTablePage and HashTableLinks

#include "HashTable.h"

HashTable::HashTable(){

    threshold = 0.75f;
    maxSize = 96;
    tableSize = 128;
    size = 0;
    table = new HashEntry*[tableSize];
        for (int i = 0; i < tableSize; i++){
            table[i] = NULL;
        }
}

HashTable::~HashTable()
{
    //dtor
}

void HashTable::setThreshold(float thold){
    threshold = thold;
    maxSize = (int) (tableSize*threshold);

}

//key=page
//returns the hashtable with the linked pages of the page/key
HashTableLinks HashTable::get(int key){
    int hash = (key%tableSize);
    int initialHash = -1;
    while(hash != initialHash &&
          (table[hash]== DeletedEntry::getUniqueDeletedEntry()||
           table[hash] != NULL&&
           table[hash]->getKey() != key)){
            if (initialHash==-1){
                initialHash = hash;
            }
            hash = (hash+1)%tableSize;
           }
    if (table[hash] == NULL || hash == initialHash){
        return -1;
    }
    else{
        return table[hash].getLinks();  //edw girnaei kanonika to value,alla girname to hashtable me ta links
    }
}

void HashTable::put(int key,HashTableLinks links){
    int hash = (key%tableSize);
    int initialHash = -1;
    int indexOfDeletedEntry = -1;
    while(hash != initialHash &&
         (table[hash]== DeletedEntry::getUniqueDeletedEntry()||
          table[hash] != NULL&&
          table[hash]->getKey() != key)){
        if(initialHash==-1){
            initialHash=hash;
        }
        if(table[hash] == DeletedEntry::getUniqueDeletedEntry()){
            indexOfDeletedEntry = hash;
        }
        hash = (hash+1)%tableSize;
    }
    if(table[hash]==NULL || hash==initialHash && indexOfDeletedEntry != -1){
        table[indexOfDeletedEntry] = new HashEntry(page,links);
        size = size+1;
    }
    else if(initialHash!=hash){
        if(table[hash] != DeletedEntry::getUniqueDeletedEntry() && table[hash] != NULL && table[hash]->getPage() == page){
            table[hash].setLinks(links);
        }
        else{
            table[hash]= new HashEntry(page,links);
            size = size+1;
        }

    }
    if(size>=maxSize){
        resize();
    }
}

void HashTable::resize(){
    int oldTableSize = tableSize;
    tableSize = 2*tableSize;
    maxSize = (int) (tableSize * threshold);
    HashEntry[] oldTable = table;
    table = new HashEntry[tableSize];
    size=0;
    for (int i = 0; i < oldTableSize; i++){
        if(oldTable[i]!=NULL && oldTable[i]!=DeletedEntry::getUniqueDeletedEntry()){
            put(oldTable[i].getPage(),oldTable[i].getLinks());
        }
    }
}

void HashTable::remove(int page){
    int hash = (key % tableSize);
    int initialHash = -1;
    while(hash != initialHash &&
         (table[hash]== DeletedEntry::getUniqueDeletedEntry() ||
          table[hash] != NULL&&
          table[hash]->getKey() != key)){
            if (initialHash == -1){
                initialHash = hash;
            }
            hash = (hash + 1) % tableSize;
          }
    if (hash != initialHash && table[hash] != NULL){
        table[hash] = DeletedEntry::getUniqueDeletedEntry();
        size--;
    }
}
