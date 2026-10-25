typedef struct Obj { void *vt; void *a; void *b; } Obj;

void *fn_801869E0(Obj *o) {
    if (o != 0) {
        return o->b;
    }
    return 0;
}
