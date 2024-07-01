#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../LinkedList.h"

LinkedList list;

int main() {

    Node *pNode = _newNode(5);
    assert(pNode->data == 5);
    assert(pNode->prev == NULL);
    assert(pNode->next == NULL);
    assert(listSize(&list) == 0);

    assert(list.head == NULL);
    assert(list.tail == NULL);
    assert(list.size == 0);

    for (int i = 1; i <= 5; i++) {
        addLast(&list, i);
        assert(list.tail->data == i);
        assert(listSize(&list) == i);
    }

    Node *p = list.head;
    for (int i = 1; i <= 5; i++) {
        assert(p->data == i);
        if (p->next != NULL) {
            assert(p->next->prev == p);
        }
        p = p->next;
    }
    assert(p == NULL);

    outputList(&list);
    outputListReverse(&list);


    for (int i = 1; i <= 5; i++) {
        assert(list.head->data == i);
        removeFirst(&list);
        assert(listSize(&list) == (5 - i));
    }
    assert(list.head == NULL);
    assert(list.tail == NULL);

    //TODO: unit test for listRemove()

    return 0;
}
