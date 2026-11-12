#include "game/types/clKPCharaData.h"
#include "game/mapobject/mapobject.h"

#include "game/types/CoursePropData.h"
#include "game/types/CoursePropResource.h"
extern "C" {
extern char lbl_80490FE0[], lbl_8036D8BC[];
extern const CoursePropResource lbl_8036D75C[3];
extern const float lbl_806D8BAC;
extern int g_longRoundFlag, g_reverseRoundFlag;
void fn_8016E7E4(void *, void *);
extern CoursePropData CoursePropCtor_rodata_8036D78C, CoursePropCtor_rodata_8036D7A0, CoursePropCtor_rodata_8036D7B4, CoursePropCtor_rodata_8036D7C8;
extern CoursePropData CoursePropCtor_rodata_8036D7DC, CoursePropCtor_rodata_8036D7F0, CoursePropCtor_rodata_8036D804, CoursePropCtor_rodata_8036D818;
extern CoursePropData CoursePropCtor_rodata_8036D82C, CoursePropCtor_rodata_8036D840, CoursePropCtor_rodata_8036D854, CoursePropCtor_rodata_8036D868;
extern char CoursePropCtor_data_806CFA50[], CoursePropCtor_data_806CFA58[];
void fn_8016E358();
void fn_8016E308();
void fn_8016E1C0();
void fn_8016A26C();
}
static CoursePropData *normalProps[7] = {
    &CoursePropCtor_rodata_8036D78C, &CoursePropCtor_rodata_8036D7DC, &CoursePropCtor_rodata_8036D82C, &CoursePropCtor_rodata_8036D840,
    &CoursePropCtor_rodata_8036D854, &CoursePropCtor_rodata_8036D868, 0
};
static CoursePropData *reverseProps[7] = {
    &CoursePropCtor_rodata_8036D7A0, &CoursePropCtor_rodata_8036D7F0, &CoursePropCtor_rodata_8036D82C, &CoursePropCtor_rodata_8036D840,
    &CoursePropCtor_rodata_8036D854, &CoursePropCtor_rodata_8036D868, 0
};
static CoursePropData *longProps[3] = { &CoursePropCtor_rodata_8036D7B4, &CoursePropCtor_rodata_8036D804, 0 };
static CoursePropData *longReverseProps[3] = { &CoursePropCtor_rodata_8036D7C8, &CoursePropCtor_rodata_8036D818, 0 };
// RTTI hierarchy record followed by the list virtual table.
#include "game/types/shared_data.h"
#ifndef __MWERKS__ /* the names other units use (tools/alias_census.py) */
#define propTypeInfo sdata_806CF750_data_804911A0
#define propVtable Scene_8016E1C0_data_804911AC
#endif
SHARED_STATIC void *propTypeInfo[3] = { CoursePropCtor_data_806CFA50, 0, 0 };
SHARED_STATIC void *propVtable[6] = {
    CoursePropCtor_data_806CFA58, 0, (void *)fn_8016E358, (void *)fn_8016E308,
    (void *)fn_8016E1C0, (void *)fn_8016A26C
};

struct CoursePropBase {
    void *vtable;
    CoursePropBase() { vtable = lbl_80490FE0; }
    ~CoursePropBase();
};
typedef clKPCharaData CoursePropNode;
typedef clKPCharaData_NokoPata CoursePropNodeA;
typedef clKPCharaData_MKoopa CoursePropNodeB;
struct CoursePropList : CoursePropBase {
    clNormal3D *models[3];
    CoursePropNode *nodes;
    CoursePropList();
};

static inline CoursePropData **SelectCourseProps() {
    if (!g_longRoundFlag) {
        if (!g_reverseRoundFlag) return normalProps;
        else return reverseProps;
    } else {
        if (!g_reverseRoundFlag) return longProps;
        else return longReverseProps;
    }
}

CoursePropList::CoursePropList() {
    vtable = propVtable;
    DebugPrintf(lbl_8036D8BC);
    for (int i = 0; i < 3; i++) {
        models[i] = new clNormal3D(lbl_8036D75C[i].resource, 0);
        clNormal3D_SetScale(models[i], 0, 0.0f, lbl_806D8BAC, 0.0f, 0.0f);
    }
    nodes = 0;
    CoursePropData **items = SelectCourseProps();
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
