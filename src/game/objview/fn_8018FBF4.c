typedef struct Obj {
    void *vt;
    void *jobj;
} Obj;

extern void Object_RenderJObjTree(void *jobj, int mask);

void fn_8018FBF4(Obj *o) {
    if (o->jobj != 0) {
        Object_RenderJObjTree(o->jobj, 7);
    }
}
