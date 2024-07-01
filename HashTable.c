#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashTable.h"

HashNodeHeader hashNodeHeaders[HASH_TABLE_SIZE];
int hasInit = 0;

HashNode *_newHashNode(char *key, void *pData) {
    HashNode *pHashNode = (HashNode *)malloc(sizeof(HashNode));
    strcpy(pHashNode->key, key);
    pHashNode->pData = pData;
    pHashNode->next = NULL;

    return pHashNode;
}

int hashCode(char* key) {
    char *p = key;
    int res = 0;

    while (*p != '\0') {
        res = res * 256 + *(unsigned char *)p;
        res %= HASH_TABLE_SIZE;
        p++;
    }
    
    return res;
}


void *get(char* key) {
    int hash = hashCode(key);
    for (HashNode *p = hashNodeHeaders[hash].pListHead; p != NULL; p = p->next) {
        if (strcmp(p->key, key) == 0) {
            return p->pData;
        }
    }

    return NULL;
}

void put(char* key, void *pData) {
    int hash = hashCode(key);
    HashNode *pNode = _newHashNode(key, pData);
    if (hashNodeHeaders[hash].pListHead == NULL) {
        hashNodeHeaders[hash].pListHead = hashNodeHeaders[hash].pListTail = _newHashNode(key, pData);
        return ;
    }

    for (HashNode *p = hashNodeHeaders[hash].pListHead; p != NULL; p = p->next) {
        if (strcmp(p->key, key) == 0) {
            p->pData = pData;
            free(pNode);
            return ;
        }
    }

    hashNodeHeaders[hash].pListTail->next = pNode;
    hashNodeHeaders[hash].pListTail = pNode;
}

int exists(char* key) {
    int hash = hashCode(key);

    for (HashNode *p = hashNodeHeaders[hash].pListHead; p != NULL; p = p->next) {
        if (strcmp(p->key, key) == 0) {
            return 1;
        }
    }

    return 0;
}

void delete(char* key) {
    HashNode *prev, *curr;
    int hash = hashCode(key);

    if (hashNodeHeaders[hash].pListHead == NULL) {
        return ;
    }

    // only one element
    if (hashNodeHeaders[hash].pListHead->next == NULL) {
        if (strcmp(hashNodeHeaders[hash].pListHead->key, key) == 0) {
            hashNodeHeaders[hash].pListHead = hashNodeHeaders[hash].pListTail = NULL;
        }
        return ;
    }

    // more than one element
    for (prev = NULL, curr = hashNodeHeaders[hash].pListHead; curr != NULL; prev = curr, curr = curr->next) {
        if (strcmp(curr->key, key) == 0) {
            HashNode *deleteNode = curr;

            if (prev == NULL) {
                hashNodeHeaders[hash].pListHead = curr->next;
            } else if (curr->next == NULL) {
                hashNodeHeaders[hash].pListTail = prev;
                prev->next = NULL;
            } else {
                prev->next = curr->next;
            }

            free(deleteNode);
            return ;
        }
    }
}