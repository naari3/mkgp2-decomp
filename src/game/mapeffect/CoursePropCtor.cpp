#include "game/mapobject/mapobject.h"

struct CoursePropData {
    Vec3f position;
    float yaw;
    int kind;
};
struct CoursePropResource {
    const char *resource;
    float radius, height, scale;
};
extern "C" {
extern char lbl_80490FE0[], lbl_80491150[], lbl_8036D8BC[];
extern const CoursePropResource lbl_8036D75C[3];
extern const float lbl_806D8BAC;
extern int g_longRoundFlag, g_reverseRoundFlag;
void fn_8016E7E4(void *, void *);
}
struct CoursePropBase {
    void *vtable;
    CoursePropBase() { vtable = lbl_80490FE0; }
    ~CoursePropBase();
};
struct CoursePropNode {
    CoursePropNode *next;
    int reserved;
    CoursePropData *data;
    float frame;
    virtual void Update();
    CoursePropNode(CoursePropData *d) : next(0), reserved(0), data(d), frame(0.0f) {}
};
struct CoursePropNodeA : CoursePropNode {
    virtual void Update();
    CoursePropNodeA(CoursePropData *d) : CoursePropNode(d) {}
};
struct CoursePropNodeB : CoursePropNode {
    virtual void Update();
    CoursePropNodeB(CoursePropData *d) : CoursePropNode(d) {}
};
struct CoursePropList : CoursePropBase {
    clNormal3D *models[3];
    CoursePropNode *nodes;
    CoursePropList();
};
CoursePropList::CoursePropList() {
    char *table = lbl_80491150;
    vtable = table + 0x5c;
    DebugPrintf(lbl_8036D8BC);
    for (int i = 0; i < 3; i++) {
        models[i] = new clNormal3D(lbl_8036D75C[i].resource, 0);
        clNormal3D_SetScale(models[i], 0, 0.0f, lbl_806D8BAC, 0.0f, 0.0f);
    }
    nodes = 0;
    CoursePropData **items;
    if (!g_longRoundFlag) {
        if (!g_reverseRoundFlag) items = (CoursePropData **)(table + 0);
        else items = (CoursePropData **)(table + 0x1c);
    } else {
        if (!g_reverseRoundFlag) items = (CoursePropData **)(table + 0x38);
        else items = (CoursePropData **)(table + 0x44);
    }
    while (*items) {
        CoursePropNode *node;
        switch ((*items)->kind) {
        case 1: node = new CoursePropNodeA(*items); break;
        case 0: node = new CoursePropNodeA(*items); break;
        case 2: node = new CoursePropNodeB(*items); break;
        default: node = new CoursePropNode(*items); break;
        }
        if (nodes) fn_8016E7E4(nodes, node);
        else nodes = node;
        items++;
    }
}
