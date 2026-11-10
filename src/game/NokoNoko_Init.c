#pragma cplusplus on
#pragma exceptions on
/* Observed allocation sizes; external constructors own unobserved fields.
 * Automatic new-expression cleanup replaces the old manual exception tables. */
struct Normal3D {
    unsigned char opaque[92];
    Normal3D(void *resource, int mode);
    ~Normal3D();
};
#include "game/types/Vec3.h"
struct NokoEntity {
    NokoEntity *next;
    unsigned char opaque04[60];
    NokoEntity(const Vec3 *);
    ~NokoEntity() {}
};
#include "game/types/SpawnRow.h"
extern "C" {
extern unsigned char g_nokonokoEnable;
extern NokoEntity *g_nokonokoHead;
extern Normal3D *lbl_80677EC8[];
extern Vec3 lbl_80677ED8;
extern void *NokoNoko_Init_data_80495D34[];
extern SpawnRow NokoNoko_Init_data_80495C28[];
extern float NokoNoko_data_806CFBD8, lbl_806D168C;
extern int lbl_806D1684;
extern const float lbl_806D9324, lbl_806D931C, lbl_806D9354;
unsigned int OSGetTick(void);
unsigned char IsSpawnTableTerminator(const SpawnRow *);
int clNormal3D_SetScale(Normal3D *, unsigned int, float, float, float, float);
void Object_SetJObjScaleXYZ(Normal3D *, float, float, float);
}
static inline void DestroyNormals() {
    Normal3D **cursor = lbl_80677EC8;
    int i = 0;
    for (; i < 4; ++i, ++cursor) {
        if (*cursor) delete *cursor;
    }
}
extern "C" void NokoNoko_Init(float value) {
    if (g_nokonokoEnable) {
        while (g_nokonokoHead) {
            NokoEntity *p = g_nokonokoHead;
            g_nokonokoHead = p->next;
            delete p;
        }
        DestroyNormals();
    }
    g_nokonokoHead = 0;
    lbl_80677EC8[0] = 0;
    lbl_80677EC8[1] = 0;
    lbl_80677EC8[2] = 0;
    lbl_80677EC8[3] = 0;
    unsigned int tick = OSGetTick();
    int seconds = (int)(tick / (*(volatile unsigned int *)0x800000F8 >> 2));
    g_nokonokoEnable = 0;
    lbl_80677ED8.x = lbl_806D9324;
    lbl_80677ED8.y = lbl_806D9324;
    lbl_80677ED8.z = lbl_806D9324;
    lbl_806D168C = lbl_806D9324;
    lbl_806D1684 = seconds % 64;
    lbl_80677EC8[0] = new Normal3D(NokoNoko_Init_data_80495D34[0], 0);
    clNormal3D_SetScale(lbl_80677EC8[0], 0, lbl_806D9324, lbl_806D931C, lbl_806D9324, lbl_806D9324);
    Object_SetJObjScaleXYZ(lbl_80677EC8[0], lbl_806D9354, lbl_806D9354, lbl_806D9354);
    lbl_80677EC8[1] = new Normal3D(NokoNoko_Init_data_80495D34[1], 0);
    clNormal3D_SetScale(lbl_80677EC8[1], 0, lbl_806D9324, lbl_806D931C, lbl_806D9324, lbl_806D9324);
    Object_SetJObjScaleXYZ(lbl_80677EC8[1], lbl_806D9354, lbl_806D9354, lbl_806D9354);
    lbl_80677EC8[2] = new Normal3D(NokoNoko_Init_data_80495D34[2], 0);
    clNormal3D_SetScale(lbl_80677EC8[2], 0, lbl_806D9324, lbl_806D931C, lbl_806D9324, lbl_806D9324);
    Object_SetJObjScaleXYZ(lbl_80677EC8[2], lbl_806D9354, lbl_806D9354, lbl_806D9354);
    lbl_80677EC8[3] = new Normal3D(NokoNoko_Init_data_80495D34[3], 1);
    clNormal3D_SetScale(lbl_80677EC8[3], 0, lbl_806D9324, lbl_806D931C, lbl_806D9324, lbl_806D9324);
    Object_SetJObjScaleXYZ(lbl_80677EC8[3], lbl_806D9354, lbl_806D9354, lbl_806D9354);
    NokoEntity *tail = 0;
    for (SpawnRow *row = NokoNoko_Init_data_80495C28; !IsSpawnTableTerminator(row); ++row) {
        Vec3 pos;
        pos.x = row->x;
        pos.y = row->y;
        pos.z = row->z;
        NokoEntity *node = new NokoEntity(&pos);
        if (node) {
            if (tail) tail->next = node;
            else g_nokonokoHead = node;
            tail = node;
        }
    }
    NokoNoko_data_806CFBD8 = value;
    lbl_80677ED8.x = lbl_806D9324;
    lbl_80677ED8.y = lbl_806D9324;
    lbl_80677ED8.z = lbl_806D9324;
    lbl_806D168C = lbl_806D9324;
    g_nokonokoEnable = 1;
}

