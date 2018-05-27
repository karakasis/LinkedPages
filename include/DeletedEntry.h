#ifndef DELETEDENTRY_H
#define DELETEDENTRY_H


class DeletedEntry: public HashEntry
{
    public:
        DeletedEntry();
        ~DeletedEntry();

    protected:

    private:
        static DeletedEntry *entry;
};

#endif // DELETEDENTRY_H
