//Supportive class for hashTable with open addressing
//Represents a deleted slot of the table
#include "DeletedEntry.h"
#include "HashTableLinks.h"


//DeletedEntry *DeletedEntry::entry = NULL;

DeletedEntry::DeletedEntry() :

        DeletedEntry::HashEntry(-1, HashTableLinks t{}) {
    }

DeletedEntry::~DeletedEntry(){}

static DeletedEntry* DeletedEntry::getUniqueDeletedEntry() {
        if (entry == NULL)
            entry = new DeletedEntry();
        return entry;
    }
