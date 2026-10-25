/*
 * 0x8014E04C..0x8014E0C4: list holder dtor.
 */
#pragma cplusplus on

struct ListNode {
    ListNode *prev;
    ListNode *next;
};
struct ListIter {
    ListNode *n;
};
struct List {
    int size;
    ListNode head;
};

/* TOP-END */

extern "C" {
void MemoryManager_TimedFree(void *p);
void fn_80157D30(struct ListIter *ret, struct List *l, struct ListIter *first, struct ListIter *last);
List *fn_8014E04C(List *self, short flag);

#pragma section R ".extab_user"

#pragma section R ".extabindex_user"

}





extern "C" List *fn_8014E04C(List *self, short flag)
{
    if (self) {
        if (self) {
            if (self) {
                ListIter e, f, r;
                e.n = &self->head;
                f.n = self->head.next;
                fn_80157D30(&r, self, &f, &e);
            }
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

