#include <stdio.h>
#include <stdlib.h>
#include "HashTable.h"
#include "LinkedList.h"
#include "LRU.h"

#define DEBUG printf

struct LRU lru;

void init(int capacity) {
    DEBUG("init() &lru = %p\n", &lru);
    lru.capacity = capacity;
}

int lruget(char *key) {
    Node *pNode = (Node *)get(key);

    if (pNode != NULL) {
        listRemove(&lru.list, pNode, 0);
        addLastNode(&lru.list, pNode);

        return pNode->data;
    }

    return -1;
}

void lruput(char *key, int value) {
    Node *pNode = (Node *)get(key);
    if (pNode != NULL) {
        pNode->data = value;
        lruget(key);

        return ;
    }

    addLastExtra(&lru.list, value, (void *)key);
    put(key, (void *)lru.list.tail);

    if (listSize(&lru.list) > lru.capacity) {
        char *deleteKey = lru.list.head->extra;
        removeFirst(&lru.list);
        delete(deleteKey);
    }

}

