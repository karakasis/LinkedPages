//Supportive class for hashTable with open addressing
//Represents a deleted slot of the table
#include "DeletedEntry.h"

class DeletedEntry: public HashEntry {

private:
    static DeletedEntry *entry;
    DeletedEntry() :
        HashEntry(-1, HashTableLinks t) {
    }

public:
    static DeletedEntry *getUniqueDeletedEntry() {
        if (entry == NULL)
            entry = new DeletedEntry();
        return entry;
    }
};

DeletedEntry *DeletedEntry::entry = NULL;
