#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../HashTable.h"

char *getString(char *s) {
    char *p = (char *)malloc(strlen(s) + 1);
    strcpy(p, s);
    return p;
}

char **getTwoCollisionKeys() {
    char key[HASH_KEY_MAX_SIZE];
    char **retKeys = calloc(sizeof(char *), 2);
    char *usedHash[HASH_TABLE_SIZE] = {NULL};
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        sprintf(key, "%d", i);
        int hash = hashCode(key);
        if (usedHash[hash] != NULL) {
            retKeys[0] = usedHash[hash];
            retKeys[1] = getString(key);
            return retKeys;
        }

        usedHash[hash] = getString(key);
    }

    return NULL;
}

int main() {
    char s[] = {0,0,0,0,0,0,0};
    for (int ch = 1; ch < 256; ch++) {
        s[0] = ch;
        assert(hashCode(s) == ch);
    }
    // test _newHashNode
    char key[] = "hashkey";
    char *value = "value";
    HashNode *pNode = _newHashNode(key, value);
    assert(pNode->key != key);
    assert(strcmp(pNode->key, key) == 0);
    assert(pNode->pData == value);
    assert(pNode->next == NULL);
    free(pNode);


    printf("hash(ab) = %d\n", hashCode("ab"));
    assert(hashCode("ab") == 24930 % HASH_TABLE_SIZE);
    assert(hashCode("abc") == 6382179 % HASH_TABLE_SIZE);
    assert(hashCode("abcd") == 1633837924 % HASH_TABLE_SIZE);
    assert(hashCode("hash") == 1751217000 % HASH_TABLE_SIZE);

    // assert that the global variale hashNodeHeaders has been set to zeros
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        assert(hashNodeHeaders[i].pListTail == NULL);
        assert(hashNodeHeaders[i].pListHead == NULL);
    }

    char *key1 = "key1", *value1 = "value1";
    char *key2 = "key2", *value2 = "value2";
    char *anotherValue1 = "anotherValue1";

    assert(get(key1) == NULL);
    assert(get(key2) == NULL);
    put(key1, value1);
    assert(exists(key1));
    assert(get(key1) == value1);
    assert(!exists(key2));
    assert(get(key2) == NULL);
    put(key2, value2);
    assert(get(key1) == value1);
    assert(get(key2) == value2);
    put(key1, anotherValue1);
    assert(get(key1) == anotherValue1);
    printf("%s: %s\n%s: %s\n", key1, (char *)get(key1), key2, (char *)get(key2));

    delete(key1);
    assert(get(key1) == NULL);
    delete(key2);
    assert(get(key2) == NULL);



    // test hash collision
    char **keys = getTwoCollisionKeys();
    printf("collison keys: %s %s\n", keys[0], keys[1]);

    assert(!exists(keys[0]));
    assert(!exists(keys[1]));

    put(keys[0], value1);
    put(keys[1], value2);
    int hash = hashCode(keys[0]);

    HashNode *pKeys0Node;
    for (pKeys0Node = hashNodeHeaders[hash].pListHead; strcmp(pKeys0Node->key, keys[0]) != 0; pKeys0Node = pKeys0Node->next) {
        ;
    }

    assert(pKeys0Node->key != keys[0]);
    assert(strcmp(pKeys0Node->key, keys[0]) == 0);
    assert(pKeys0Node->pData == value1);

    assert(strcmp(pKeys0Node->next->key, keys[1]) == 0);
    assert(pKeys0Node->next->next == NULL);

    delete(keys[1]);
    assert(get(keys[1]) == NULL);
    assert(pKeys0Node->next == NULL);
    delete(keys[0]);
    assert(get(keys[0]) == NULL);
    assert(hashNodeHeaders[hash].pListHead == NULL);
    assert(hashNodeHeaders[hash].pListTail == NULL);

    return 0;
}