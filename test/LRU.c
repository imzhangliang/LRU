#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../LRU.h"

extern struct LRU lru;
extern struct LRU mylru;

#define DEBUG printf

int main() {
    init(5);
    assert(lruget("key") == -1);
    lruput("key1", 1);
    assert(lru.list.tail->data == 1);
    lruput("key2", 2);
    assert(lru.list.tail->data == 2);

    assert(lruget("key1") == 1);
    assert(lru.list.tail->data == 1);
    assert(lruget("key2") == 2);
    assert(lru.list.tail->data == 2);

    lruput("key1", 11);
    assert(lru.list.tail->data == 11);
    assert(lruget("key1") == 11);

    lruput("key2", 22);
    assert(lru.list.tail->data == 22);
    assert(lruget("key2") == 22);

    lruput("key3", 33);
    lruput("key4", 44);
    lruput("key5", 55);

    assert(lru.list.head->data == 11);
    assert(strcmp(lru.list.head->extra, "key1") == 0);

    lruput("key6", 66);
    assert(lru.list.head->data == 22);
    assert(strcmp(lru.list.head->extra, "key2") == 0);

    for (Node *p = lru.list.head; p != NULL; p = p->next) {
        printf("%s: %d, ", (char *)p->extra, p->data);
    }
    printf("\n");
    
    lruput("key7", 77);

    for (Node *p = lru.list.head; p != NULL; p = p->next) {
        printf("%s: %d, ", (char *)p->extra, p->data);
    }
    printf("\n");

    assert(get("key1") == NULL);
    assert(get("key2") == NULL);








    return 0;
}