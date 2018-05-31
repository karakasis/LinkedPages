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
    for (int i = 0; i < tableSize; i++)
      if (table[i] != NULL && table[i] != HashTable::getDeletedEntry())
            delete table[i];
    delete[] table;
}

void HashTable::createLink(int key,int link){
    int hash = (key%tableSize);
    bool found = false;
    while(table[hash] != NULL)
    {   //if we loop then either hash is taken from something else or
        //hash is the same cause key is the same
        if(table[hash]->getKey() == key){
            table[hash]->getLinks().put(link,link);
            found = true;
            break;
        }else if(table[hash] == HashTable::getDeletedEntry()){
            table[hash] = new HashEntry(key,link);
            break;
        }
        hash = (hash+1)%tableSize; //and then try for 1 place below to find empty spot
    }
    if(!found){
        table[hash] = new HashEntry(key,link);
        size = size+1;
    }
    if(size>=maxSize){
        resize();
    }
}

void HashTable::insertLink(int key,int link){
    std::ofstream out("output.txt", std::ofstream::out | std::ofstream::app);
    out<<"running: insertLink("<<key<<","<<link<<");"<<endl;
    int hash = (key%tableSize);
    bool found = false;
    while(table[hash] != NULL)
    {   //if we loop then either hash is taken from something else or
        //hash is the same cause key is the same
        if(table[hash]->getKey() == key){
            table[hash]->getLinks().put(link,link);
            out<<"added link "<<link<<" in page "<<key<<endl;
            found = true;
            break;
        }else if(table[hash] == HashTable::getDeletedEntry()){
            table[hash] = new HashEntry(key,link);
            break;
        }
        hash = (hash+1)%tableSize; //and then try for 1 place below to find empty spot
    }
    if(!found){
        out<<"page "<<key<<" was created"<<endl;
        table[hash] = new HashEntry(key,link);
        out<<"added link "<<link<<" in page "<<key<<endl;
        size = size+1;
    }
    if(size>=maxSize){
        resize();
    }

    out<<endl;
}

void HashTable::deleteLink(int key,int link){
    std::ofstream out("output.txt", std::ofstream::out | std::ofstream::app);

    out<<"running: deleteLink("<<key<<","<<link<<");"<<endl;
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
    }else{
        out<<"link "<<link<<" in page "<<key<<" not found"<<endl;
    }

    out<<endl;
}

HashTableLinks HashTable::findNeighbors(int key){
    std::ofstream out("output.txt", std::ofstream::out | std::ofstream::app);
    out<<"running: findNeighbors("<<key<<");"<<endl;
    HashTableLinks tl = get(key);
    if(tl.size!=0){
       out<<"[ ";
        for(int i=0; i<tl.getTableSize(); i++){
            if(tl.getAllLinks()[i] != NULL){
                LinkedHashEntry *entry = tl.getAllLinks()[i];
                out<<entry->getKey()<<" ";
                while (entry->getNext() != NULL){
                    entry = entry->getNext();
                    out<<entry->getKey()<<" ";
                }
            }
        }
        out<<"]"<<endl;
    }else{
        out<<"page "<<key<<" not found"<<endl;
    }

    out<<endl;
    return tl;
}

void HashTable::findNumConnectedComponents(){
    std::ofstream out("output.txt", std::ofstream::out | std::ofstream::app);
    out<<"running: findNumConnectedComponents();"<<endl;

    //trigger cloning
    cout<<"Cloning ..."<<endl;
    HashTable cloned(*this);
    //cloned = new HashTable(*this);
    duplicateLinks(cloned);
    std::cout<<"Finding connected components ... "<<std::endl;

    //edw prepei na ginete kathe fora arxikopoiisi tou color me to plithos twn pages
    //giati mporei na exei proigithei insert i delete    cout<<
    //cout<<cloned.size<<endl;
    //cout<<size<<endl;
    color = new int[cloned.tableSize];

    for(int i =0;i<cloned.tableSize;i++){
        color[i]=1; //oloi oi komvoi white(arxikopoiisi)
    }
    int cc=DFS(cloned);
    delete [] color;
    out<<"Connected Components: "<<cc<<endl;

    out<<endl;
    //delete cloned;
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
    HashTableLinks neighbors = cloned.get(cloned.table[u]->getKey()); //paizei na einai kenos kai na exei thema
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
