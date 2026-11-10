/* Ranking flow teardown. The list nodes own polymorphic entries. */
class RankingOwnedObject {
public:
    virtual ~RankingOwnedObject();
};
struct RankingNode {
    RankingNode *prev;
    RankingNode *next;
    RankingOwnedObject *entry;
};
struct RankingList {
    int count;
    RankingNode *last;
    RankingNode *first;
};
struct RankingIterator {
    RankingNode *node;
    RankingIterator() {}
    RankingIterator(RankingNode *p) : node(p) {}
    RankingIterator(const RankingIterator &it) : node(it.node) {}
};
struct RankingOwner {
    void *vtable;
    int state;
    RankingList entries;
    RankingOwnedObject *players[4];
    RankingOwnedObject *other;
    void *lobjList;
};
extern "C" {
extern char RankingFlow_vtable_8049B51C[];
void LObjList_Destroy(void *, int);
void dtor_801BA14C(void *, int);
void MemoryManager_TimedFree(void *);
RankingIterator DoublyLinkedList_EraseRange(RankingList *, const RankingIterator *, const RankingIterator *);
}
extern "C" RankingOwner *fn_801D1D9C(RankingOwner *self, short flags) {
    RankingNode *node;
    RankingNode *end;
    if (self) {
        self->vtable = RankingFlow_vtable_8049B51C;
        end = (RankingNode *)&self->entries.last;
        for (node = self->entries.first; node != end; node = node->next) {
            delete node->entry;
        }
        delete self->other;
        LObjList_Destroy(self->lobjList, 1);
        if (&self->entries) {
            if (&self->entries) {
                if (&self->entries) {
                    RankingIterator last(end);
                    RankingIterator first(end->next);
                    DoublyLinkedList_EraseRange(&self->entries, &first, &last);
                }
            }
        }
        dtor_801BA14C(self, 0);
        if (flags > 0) MemoryManager_TimedFree(self);
    }
    return self;
}
