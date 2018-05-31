#include "LinkedHashEntry.h"
#include <iostream>

using namespace std;

LinkedHashEntry::LinkedHashEntry(int key, int value)
{
    this->key = key;
    this->value = value;
    this->next = NULL;
}

LinkedHashEntry::~LinkedHashEntry()
{

}

int LinkedHashEntry::getKey(){
    return key;
}

int LinkedHashEntry::getValue() {
    return value;
}

void LinkedHashEntry::setValue(int value) {
    this->value = value;
}

LinkedHashEntry* LinkedHashEntry::getNext() {
    return next;
}

void LinkedHashEntry::setNext(LinkedHashEntry *next) {
    this->next = next;
}
