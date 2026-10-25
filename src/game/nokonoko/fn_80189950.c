typedef struct Link {
    struct Link *next;
} Link;

typedef struct Owner {
    unsigned char pad[0x38];
    Link *head;
} Owner;

extern int lbl_806D1690;
extern void MemoryManager_TimedFree(void *p);

void fn_80189950(Owner *o) {
    Link *l = o->head;
    while (l != 0) {
        Link *next = l->next;
        if (l != 0) {
            lbl_806D1690--;
            MemoryManager_TimedFree(l);
        }
        l = next;
    }
    o->head = 0;
}
