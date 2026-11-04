#ifndef MAPOBJECT17B_DEBUG_PRIVATE_H
#define MAPOBJECT17B_DEBUG_PRIVATE_H

#include "game/mapobject/mapobject.h"
#include "game/FlowScene.h"

/* Virtual input view: axis slots 0x10/0x14 return floats here. */
struct MapDebugInput {
    virtual void v0();
    virtual void v1();
    virtual float AxisX();
    virtual float AxisY();
    virtual float Right();
    virtual float Left();
    virtual unsigned char Pressed(int);
    virtual unsigned char Held(int);
};

struct MapDebugCamera : VObject {
    virtual ~MapDebugCamera();
    void *cobj;
    virtual unsigned char Begin();
    virtual void End();
};

struct clPathNode {
    Vec3f points[4];
    int index;
    clPathNode *next;
    ~clPathNode() {}
};

extern "C" {
extern MapDebugCamera *lbl_806D1618;
extern clNormal3D *lbl_806D1620;
extern unsigned int lbl_806D1614;
extern int lbl_806D1628, lbl_806D162C, lbl_806D1630;
extern int lbl_806D1634, lbl_806D1638;
extern clPathNode *lbl_806D163C, *lbl_806D1640;
extern Vec3f lbl_80677D00, lbl_80677D0C;
extern const char lbl_80376220[];
extern bool lbl_806CFB84;
extern unsigned char lbl_806CFB85, lbl_806CFBA1;
void *GetInputManager();
MapDebugInput *InputMgr_GetPlayer(void *, int);
unsigned char fn_8017E6A8();
void HSD_CObjSetEyePosition(void *, const Vec3f *);
void HSD_CObjSetInterest(void *, const Vec3f *);
extern const float lbl_806D9188, lbl_806D918C, lbl_806D9190;
extern const float lbl_806D91A8, lbl_806D91AC;
extern const char lbl_806D9194[5], lbl_806D919C[6], lbl_806D91A4[4];
}

static inline void MapDebugRemoveNode(clPathNode *node) {
    if (node == 0) return;
    clPathNode *prev = lbl_806D163C;
    if (node == prev) {
        lbl_806D163C = node->next;
        delete node;
        lbl_806D1640 = lbl_806D163C;
        return;
    }
    while (prev->next) {
        clPathNode *p = prev->next;
        if (p == node) {
            clPathNode *next = p->next;
            delete p;
            prev->next = next;
            lbl_806D1640 = prev;
            return;
        }
        prev = p;
    }
}

static inline void MapDebugSelectStart() {
    clPathNode *node = lbl_806D1640;
    if (node) {
        node->index = 0;
        lbl_80677D00.x = node->points[0].x;
        lbl_80677D00.z = node->points[0].z;
    }
}

static inline void MapDebugMoveCamera(MapDebugInput *input) {
    float axis = input->AxisX();
    if (axis > lbl_806D9188 || axis < lbl_806D918C) {
        if (lbl_806D1614 == 1) lbl_80677D00.x += lbl_806D9190 * axis;
        else lbl_80677D00.x += lbl_806D9190 * axis;
    }
    axis = input->AxisY();
    if (axis > lbl_806D9188 || axis < lbl_806D918C) {
        if (lbl_806D1614 == 1) lbl_80677D00.z -= lbl_806D9190 * axis;
        else lbl_80677D00.y += lbl_806D9190 * axis;
    }
}

#endif
