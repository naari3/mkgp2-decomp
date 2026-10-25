extern void MemoryManager_TimedFree(void *p);
extern void DebugPrintf(const char *fmt, ...);
extern void __destroy_new_array(void *block, void *dtor);
extern void *clDrawMan_Buckets_Free(void *self, short flag);
extern void *clDrawMan_NodePool_Free(void *self, short flag);

extern void *lbl_803FE05C[];
extern void *lbl_803FE068[];
extern char lbl_80311B5C[];

typedef struct clDrawMan {
    void **vtbl;
    void *buckets;
    void *nodes;
} clDrawMan;

/* 0x80079B24: deleting destructor of the draw manager. */
clDrawMan *clDrawMan_Dtor(clDrawMan *self, short flag)
{
    if (self != 0) {
        self->vtbl = lbl_803FE05C;
        DebugPrintf(lbl_80311B5C);
        __destroy_new_array(self->buckets, clDrawMan_Buckets_Free);
        self->buckets = 0;
        __destroy_new_array(self->nodes, clDrawMan_NodePool_Free);
        self->nodes = 0;
        if (self != 0) {
            self->vtbl = lbl_803FE068;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
