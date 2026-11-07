#ifndef GAME_CLITEMBOXMANAGER_LISTDTORS_PRIVATE_H
#define GAME_CLITEMBOXMANAGER_LISTDTORS_PRIVATE_H

void operator delete(void *ptr);

struct ItemBoxListNode {
    ItemBoxListNode *prev;
    ItemBoxListNode *next;
    void *value;
};

struct ItemBoxListIter {
    ItemBoxListNode *node;
    ItemBoxListIter(ItemBoxListNode *p) : node(p) {}
};

extern "C" ItemBoxListIter DoublyLinkedList_EraseRange(
    void *self, const ItemBoxListIter &first, const ItemBoxListIter &last);

struct ItemBoxListStorage {
    unsigned long size;
    ItemBoxListNode *prev;
    ItemBoxListNode *next;
    ~ItemBoxListStorage() {
        DoublyLinkedList_EraseRange(this, ItemBoxListIter(next),
            ItemBoxListIter((ItemBoxListNode *)&prev));
    }
};

struct ItemBoxListBase : ItemBoxListStorage {
    ~ItemBoxListBase() {}
};

struct ItemBoxBoxes : ItemBoxListBase {
    ~ItemBoxBoxes();
};

struct ItemBoxResponders : ItemBoxListBase {
    ~ItemBoxResponders();
};

#endif
