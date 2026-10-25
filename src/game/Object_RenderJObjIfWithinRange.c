extern void Object_RenderJObjTree(void *jobj, int mask);
extern const float lbl_806CEDBC;

typedef struct RenderRangeObj {
    unsigned char pad_0[4];
    float dist;
    unsigned char pad_8[0x3C];
    void *jobj;
} RenderRangeObj;

/* 0x8003D304: render the object's JObj tree while it is within range. */
int Object_RenderJObjIfWithinRange(RenderRangeObj *obj)
{
    if (obj->jobj == 0) {
        return 0;
    }
    if (obj->dist >= lbl_806CEDBC) {
        return 0;
    }
    Object_RenderJObjTree(obj->jobj, 7);
    return 1;
}
