#include "HashTable.h"
#include "vector"


HashEntry* HashTable::deleted_entry = 0;

HashEntry* HashTable::getDeletedEntry() {
    if (deleted_entry == NULL)
        deleted_entry = new HashEntry(-987654);
    return deleted_entry;
}

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

void HashTable::insertLink(int key,int link){
    int hash = (key%tableSize);
    //cerr<<"trying -> page: "<<key<<" link: "<<link<<" with hash: "<<hash<<endl;
    bool found = false;
    while(table[hash] != NULL)
    {   //if we loop then either hash is taken from something else or
        //hash is the same cause key is the same
        //cout<<"old key .. "<<table[hash]->getKey()<<endl;
        //cout<<"stuck pls help me"<<endl;
        if(table[hash]->getKey() == key){
            table[hash]->getLinks().put(link,link);
            //cout<<"added_old -> page: "<<key<<" link: "<<link<<endl;
            found = true;
            break;
        }else if(table[hash] == HashTable::getDeletedEntry()){
            table[hash] = new HashEntry(key,link);  //isws na xreiazetai &
            //cout<<"added_deleted -> page: "<<key<<" link: "<<link<<endl;
            break;
        }
        hash = (hash+1)%tableSize; //and then try for 1 place below to find empty spot
        //cout<<"update hash to "<<hash<<endl;
    }
    if(!found){
        table[hash] = new HashEntry(key,link);
        //cout<<"added_new -> page: "<<key<<" link: "<<link<<endl;
        size = size+1;
    }
    //cout<<size<<endl;
    if(size>=maxSize){
        resize();
    }
}

void HashTable::deleteLink(int key,int link){
    int hash = (key % tableSize);
    int initialHash = -1;
    while(hash != initialHash &&
         (table[hash]== HashTable::getDeletedEntry() ||
          table[hash] != NULL&&
          table[hash]->getKey() != key)){
            if (initialHash == -1){
                initialHash = hash;
            }
            hash = (hash + 1) % tableSize;
          }
    if (hash != initialHash && table[hash] != NULL){
        table[hash]->getLinks().remove(link);
    }
}

HashTableLinks& HashTable::findNeighbors(int key){
    HashTableLinks tl = get(key);
    if(tl.size!=0){
       cout<<"[ ";
        for(int i=0; i<tl.getTableSize(); i++){
            if(tl.getAllLinks()[i] != NULL){
                LinkedHashEntry *entry = tl.getAllLinks()[i];
                cout<<entry->getKey()<<" ";
                while (entry->getNext() != NULL){
                    entry = entry->getNext();
                    cout<<entry->getKey()<<" ";
                }
            }
        }
        cout<<"]"<<endl;
    }
    return tl;
}

void HashTable::findNumConnectedComponents(){
    cout<<"running: findNumConnectedComponents();"<<endl;

    //trigger cloning
    cout<<"Cloning ..."<<endl;
    HashTable cloned(*this);
    duplicateLinks(cloned);
    cout<<"Finished cloning "<<endl;

    //edw prepei na ginete kathe fora arxikopoiisi tou color me to plithos twn pages
    //giati mporei na exei proigithei insert i delete    cout<<
    //cout<<cloned.pairs.size()<<endl;
    //cout<<pairs.size()<<endl;
    color = new int[cloned.tableSize];

    for(int i =0;i<cloned.tableSize;i++){
        color[i]=1; //oloi oi komvoi white(arxikopoiisi)
    }
    int cc=DFS(cloned);
    delete [] color;
    cout<<"Connected Components: "<<cc<<endl;
    cout<<endl;
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
          (table[hash]== HashTable::getDeletedEntry()||
           table[hash] != NULL&&
           table[hash]->getKey() != key)){
            if (initialHash==-1){
                initialHash = hash;
            }
            hash = (hash+1)%tableSize;
           }
    if (table[hash] == NULL || hash == initialHash){
        return HashTable::getDeletedEntry()->getLinks();//?+?
    }
    else{
        return table[hash]->getLinks();  //edw girnaei kanonika to value,alla girname to hashtable me ta links
    }
}

void HashTable::put(int key,HashTableLinks& links){
    int hash = (key%tableSize);
    //cerr<<"trying -> page: "<<key<<" with hash: "<<hash<<endl;
    while(table[hash] != NULL)
    {   //if we loop then either hash is taken from something else
        hash = (hash+1)%tableSize; //and then try for 1 place below to find empty spot
        //cout<<"update hash to "<<hash<<endl;
    }
    table[hash] = new HashEntry(key,links);
    //cout<<"added_new -> page: "<<key<<" link: "<<link<<endl;
    size = size+1;
    //cout<<size<<endl;
    if(size>=maxSize){
        resize();
    }
}

void HashTable::resize(){
    //cout<<"resized"<<endl;
    int oldTableSize = tableSize;
    tableSize = 2*tableSize;
    maxSize = (int) (tableSize * threshold);
    HashEntry** oldTable = new HashEntry*[oldTableSize];
    oldTable = table;
    table = new HashEntry*[tableSize];
    for (int i = 0; i < tableSize; i++)
        table[i] = NULL;
    size=0;
    for (int i = 0; i < oldTableSize; i++){
        if(oldTable[i]!=NULL && oldTable[i]!=HashTable::getDeletedEntry()){
            put(oldTable[i]->getPage(),oldTable[i]->getLinks());
        }
    }
    delete [] oldTable;
}

void HashTable::remove(int key){
    int hash = (key % tableSize);
    int initialHash = -1;
    while(hash != initialHash &&
         (table[hash]== HashTable::getDeletedEntry() ||
          table[hash] != NULL&&
          table[hash]->getKey() != key)){
            if (initialHash == -1){
                initialHash = hash;
            }
            hash = (hash + 1) % tableSize;
          }
    if (hash != initialHash && table[hash] != NULL){
        table[hash] = HashTable::getDeletedEntry();
        size--;
    }
}

//colors: 1->White, 2->Gray, 3->Black
//kathe fora pou ekteleitai vriskei mia sinektiki sinistwsa kai tin markarei
//counter me arithmo ektelesis tis= arithmos S.S.
int HashTable::DFS(HashTable& cloned){
    int counter=0;
    for(int j=0;j<cloned.tableSize;j++){
        if(color[j]==1 && cloned.table[j]!=NULL){
            DFSvisit(j, cloned);
            counter=counter+1;
        }
    }
    return counter;
}

//Vriskei sindedemenous komvous tou u(emmesa kai amesa) kai tous markarei.
void HashTable::DFSvisit(int u, HashTable& cloned){
    color[u]=2;
    //cout<<"here "<<endl;
    HashTableLinks neighbors = cloned.findNeighbors(cloned.table[u]->getKey()); //paizei na einai kenos kai na exei thema
    //cout<<"here "<<endl;
    for(int k = 0;k<neighbors.getTableSize();k++){
        if(neighbors.getAllLinks()[k] != NULL){
            LinkedHashEntry *entry = neighbors.getAllLinks()[k];
            if(color[entry->getKey()]==1){
                DFSvisit(entry->getKey(),cloned);
            }
            while (entry->getNext() != NULL){
                entry = entry->getNext();
                if(color[entry->getKey()]==1){
                    DFSvisit(entry->getKey(),cloned);
                }
            }
        }
    }
    color[u]=3;
}
