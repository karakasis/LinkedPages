#ifndef LINKEDHASHENTRY_H
#define LINKEDHASHENTRY_H


class LinkedHashEntry
{
    public:
        LinkedHashEntry(int key, int value);
        ~LinkedHashEntry();
        int getKey();
        int getValue();
        void setValue(int value);
        LinkedHashEntry *getNext();
        void setNext(LinkedHashEntry *next);

    protected:

    private:
        int key;
        int value;
        LinkedHashEntry *next;
};

#endif // LINKEDHASHENTRY_H
