typedef struct Obj { void *vt; void *a; void *b; } Obj;

void *fn_801869C8(Obj *o) {
    if (o != 0) {
        return o->a;
    }
    return 0;
}
