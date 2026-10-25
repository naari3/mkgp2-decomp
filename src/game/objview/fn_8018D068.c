extern void Object_RenderJObjTree(void *jobj, int flags);

typedef struct Obj {
    unsigned char pad0[0x4];
    void **items;
    int count;
} Obj;

void fn_8018D068(Obj *o) {
    int i;

    if (o->items == 0 || o->count == 0) {
        return;
    }
    for (i = 0; i < o->count; i++) {
        if (o->items[i] != 0) {
            Object_RenderJObjTree(o->items[i], 7);
        }
    }
}
