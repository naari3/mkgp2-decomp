typedef struct JObjFlags {
    unsigned char pad[0x14];
    unsigned int flags;
} JObjFlags;

typedef struct Link {
    struct Link *next;
    JObjFlags *jobj;
} Link;

typedef struct Owner {
    unsigned char pad[0x38];
    Link *head;
} Owner;

void fn_80189394(Owner *o) {
    Link *l;
    for (l = o->head; l != 0; l = l->next) {
        l->jobj->flags |= 1;
    }
}
