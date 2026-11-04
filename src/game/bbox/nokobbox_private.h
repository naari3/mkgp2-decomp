#ifndef NOKO_BBOX_PRIVATE_H
#define NOKO_BBOX_PRIVATE_H
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct FlagObject { unsigned char pad[0x14]; unsigned int flags; } FlagObject;
typedef struct ShadowEntry {
    struct ShadowEntry *next;
    FlagObject *dobj;
    Vec3 pos;
    float radius;
    FlagObject *jobj;
} ShadowEntry;
typedef struct BBox {
    Vec3 min, max, center;
    float radius;
    int oct, parent;
    struct BBox *next, *child;
    ShadowEntry *head;
    int cursor;
} BBox;
#endif
