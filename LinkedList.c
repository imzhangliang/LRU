#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"


Node *_newNode(int data) {
    struct Node *p = (struct Node *)malloc(sizeof(struct Node));
    p->next = NULL;
    p->prev = NULL;
    p->data = data;

    return p;
}

Node *_newNodeExtra(int data, void *extra) {
    struct Node *p = _newNode(data);
    p->extra = extra;

    return p;
}

void addLast(LinkedList *list, int data) {
    Node *pNode = _newNode(data);

    addLastNode(list, pNode);
}

void addLastExtra(LinkedList *list, int data, void *extra) {
    Node *pNode = _newNodeExtra(data, extra);

    addLastNode(list, pNode);
}

void addLastNode(LinkedList *list, Node *pNode) {
    if (pNode == NULL) {
        return ;
    }

    if (list->head == NULL) {
        list->head = list->tail = pNode;
        list->size = 1;
        return ;
    }

    list->tail->next = pNode;
    pNode->prev = list->tail;
    list->tail = pNode;
    (list->size)++;
}


void removeFirst(LinkedList *list) {
    if (list->head == NULL) {
        return ;
    }

    Node *deleteNode = list->head;
    if (list->size == 1) {
        list->head = list->tail = NULL;
        list->size = 0;
        return ;
    } else {
        Node *head = list->head->next;
        list->head = head;
        head->prev = NULL;
        --list->size;
    }

    free(deleteNode);
}


int listSize(LinkedList *list) {
    if (list->head == NULL) {
        list->size = 0;     // in case list hasn't been set to zero when initialization
    }

    return list->size;
}

void outputList(LinkedList *list) {
    for (Node *p = list->head; p != NULL; p = p->next) {
        printf("(%d)", p->data);
    }
    printf("\n");
}

void outputListReverse(LinkedList *list) {
    for (Node *p = list->tail; p != NULL; p = p->prev) {
        printf("(%d)", p->data);
    }
    printf("\n");
}


void listRemove(LinkedList *list, Node *pNode, int freeNode) {
    if (listSize(list) == 0) {
        return ;
    }
 
    if (listSize(list) == 1) {
        if (list->head == pNode) {
            list->head = list->tail = NULL;
            list->size = 0;

            if (freeNode) {
                free(pNode);
            }
        }
        return ;
    }

    if (list->head == pNode) {
        Node *newHead = pNode->next;
        newHead->prev = NULL;
        list->head = newHead;
    } else if (list->tail == pNode) {
        Node *newTail = pNode->prev;
        newTail->next = NULL;
        list->tail = newTail;
    } else {
        Node *prevNode = pNode->prev;
        Node *nextNode = pNode->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
    }

    --list->size;

    if (freeNode) {
        free(pNode);
    }
}