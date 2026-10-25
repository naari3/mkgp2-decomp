typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct HSD_JObj HSD_JObj;

typedef struct ItemParams {
    float x0;
    float x4;
    float x8;
} ItemParams;

typedef struct Item {
    struct Item *next;
    ItemParams *params;
    HSD_JObj *jobj;
    Vec3 pos;
    float radius;
} Item;

typedef struct Group {
    struct Group *next;
    unsigned char pad4[4];
    Item *items;
} Group;

typedef struct Ctx {
    unsigned char pad0[4];
    Group *groups;
    int type;
    unsigned char flag;
} Ctx;

extern unsigned char fn_801379F0(Vec3 *pos, float radius);
extern void fn_80182B50(HSD_JObj *jobj, float a, float b);
extern void HSD_JObjDispAll(HSD_JObj *jobj, void *a, int b, int c);

static inline void DrawItem(Item *it) {
    if (it->jobj != 0 && fn_801379F0(&it->pos, it->radius)) {
        fn_80182B50(it->jobj, it->params->x4, it->params->x8);
        HSD_JObjDispAll(it->jobj, 0, 7, 0);
    }
}

static inline void DrawAll(Ctx *c) {
    Item *it;
    Group *g;
    for (g = c->groups; g != 0; g = g->next) {
        for (it = g->items; it != 0; it = it->next) {
            DrawItem(it);
        }
    }
}

void fn_801954F4(Ctx *c) {
    Group *g;
    Item *it;
    if (c->type == 8) {
        if (c->flag == 1) {
            return;
        }
        DrawAll(c);
    } else {
        for (g = c->groups; g != 0; g = g->next) {
            for (it = g->items; it != 0; it = it->next) {
                DrawItem(it);
            }
        }
    }
}
