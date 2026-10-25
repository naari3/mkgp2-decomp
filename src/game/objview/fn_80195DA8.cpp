typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct HSD_JObj HSD_JObj;

struct clNormal3D {
    clNormal3D(const char *name, int flags);
    unsigned char pad[0x5c];
};

struct ItemParams {
    const char *name;
    float x4;
    float x8;
};

struct GroupParams {
    const char *model;
    ItemParams *items;
    int count;
};

extern "C" {
extern void DebugPrintf(const char *fmt, ...);
extern HSD_JObj *Archive_GetRootJObj(clNormal3D *model);
extern HSD_JObj *ResolveJointByName(clNormal3D *model, const char *name);
extern void fn_801847DC(HSD_JObj *jobj, Vec3 *min, Vec3 *max);
extern void Vec3_Subtract(Vec3 *a, Vec3 *b, Vec3 *out);
extern float Vec3_Magnitude(Vec3 *v);
extern void HSD_JObjClearFlags(HSD_JObj *jobj, unsigned int flags);
extern const char lbl_8037D85C[];
extern const float lbl_806D9558;
extern const float lbl_806D955C;
}

struct Item {
    Item *next;
    ItemParams *params;
    HSD_JObj *jobj;
    Vec3 pos;
    float radius;

    Item(ItemParams *p, clNormal3D *model) {
        next = 0;
        jobj = 0;
        pos.x = lbl_806D9558;
        pos.y = lbl_806D9558;
        pos.z = lbl_806D9558;
        radius = lbl_806D9558;
        params = p;
        if (params->name == 0) {
            jobj = Archive_GetRootJObj(model);
        } else {
            jobj = ResolveJointByName(model, params->name);
        }
        if (jobj == 0) {
            DebugPrintf(lbl_8037D85C);
        } else {
            Vec3 min;
            Vec3 max;
            min.x = lbl_806D9558;
            min.y = lbl_806D9558;
            min.z = lbl_806D9558;
            max.x = lbl_806D9558;
            max.y = lbl_806D9558;
            max.z = lbl_806D9558;
            fn_801847DC(jobj, &min, &max);
            pos.x = lbl_806D955C * (min.x + max.x);
            pos.y = lbl_806D955C * (min.y + max.y);
            pos.z = lbl_806D955C * (min.z + max.z);
            Vec3_Subtract(&max, &pos, &min);
            radius = Vec3_Magnitude(&min);
            HSD_JObjClearFlags(jobj, 0x10);
        }
    }
};

extern "C" void fn_80195F54(Item *list, Item *item);

struct Group {
    Group *next;
    clNormal3D *model;
    Item *items;

    Group(GroupParams *p);
};

Group::Group(GroupParams *p) {
    int i;
    next = 0;
    items = 0;
    model = new clNormal3D(p->model, 0);
    for (i = 0; i < p->count; i++) {
        Item *it = new Item(&p->items[i], model);
        if (items != 0) {
            fn_80195F54(items, it);
        } else {
            items = it;
        }
    }
}
