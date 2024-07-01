#ifndef _LRU
#define _LRU
#include "HashTable.h"
#include "LinkedList.h"

struct LRU {
    int capacity;
    LinkedList list;
};

void init(int capacity);
int lruget(char *key);
void lruput(char *key, int value);


#endif