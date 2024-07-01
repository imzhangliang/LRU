#ifndef _HASH_TABLE
#define _HASH_TABLE

#define HASH_KEY_MAX_SIZE 64
#define HASH_TABLE_SIZE 92297

struct hashNode {
    char key[HASH_KEY_MAX_SIZE];
    void *pData;
    struct hashNode *next;
};

typedef struct hashNode HashNode;

typedef struct {
    HashNode *pListHead;
    HashNode *pListTail;
} HashNodeHeader;

extern HashNodeHeader hashNodeHeaders[];

int hashCode(char* key);
HashNode *_newHashNode(char *key, void *pData);
void *get(char* key);
void put(char* key, void *pData);
int exists(char* key);
void delete(char* key);


#endif