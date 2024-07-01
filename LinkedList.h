#ifndef _LINKED_LIST
#define _LINKED_LIST

#define LINKED_LIST_DATA_MAX_LENGTH 128

struct Node {
    void *extra;
    int data;
    struct Node *prev;
    struct Node *next;
};

typedef struct Node Node;

struct LinkedList {
    Node *head;
    Node *tail;
    int size;
};

typedef struct LinkedList LinkedList;

Node *_newNode(int data);
Node *_newNodeExtra(int data, void *extra);
void addLast(LinkedList *list, int data);
void addLastExtra(LinkedList *list, int data, void *extra);
void addLastNode(LinkedList *list, Node *pNode);
void removeFirst(LinkedList *list);
int listSize(LinkedList *list);
void outputList(LinkedList *list);
void listRemove(LinkedList *list, Node *pNode, int freeNode);
void outputListReverse(LinkedList *list);


// typedef struct Node Node;

// Node *newNode(int data);
// char *nodeToString(Node *pNode);
// void printNode(Node *pNode);
// void iterate(Node *listHead, void func(Node *));
// Node *newListFromArray(int *nums, int n);
// Node *deleteNode(Node *list, Node *pNode);
// Node *findFirstNode(Node *list, int value);



#endif
