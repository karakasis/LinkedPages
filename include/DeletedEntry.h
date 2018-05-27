#ifndef DELETEDENTRY_H
#define DELETEDENTRY_H

#include "HashEntry.h"
#include "HashTableLinks.h"



class DeletedEntry: public HashEntry
{
    public:
        DeletedEntry();
        ~DeletedEntry();
        static DeletedEntry* getUniqueDeletedEntry();

    protected:

    private:
        static DeletedEntry *entry;
};

#endif // DELETEDENTRY_H
