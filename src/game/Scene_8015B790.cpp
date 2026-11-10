#include "game/Scene_8015B790_private.h"

extern "C" {
void *GetInputManager(); ViewerInput *InputMgr_GetPlayer(void *, int);
extern int lbl_806D1594, lbl_806D1598, lbl_806D159C, lbl_806D15A0;
extern float lbl_806D15A4, lbl_806D15A8;
extern CameraOwner *lbl_806D1588;
extern void *lbl_806D158C;
extern ViewerVec lbl_80677CD8;
void fn_8015BCC4(const char *, float);
void fn_80168EFC(int, float, float, const char *, ...);
#ifdef __MWERKS__
void fn_80169040(void *, float,float,float,float,float,float,int,unsigned int);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern void fn_80169040(void *, int, float, float, float, float, float, float, unsigned int);
static inline void fn_80169040_Reordered(void *a0, float a1, float a2, float a3, float a4, float a5, float a6, int a7, unsigned int a8) { fn_80169040(a0, a7, a1, a2, a3, a4, a5, a6, a8); }
#define fn_80169040 fn_80169040_Reordered
#endif
void Object_SetJObjPositionX(void *, float);
void Object_SetJObjField40(void *, float);
void HSD_CObjSetEyePosition(void *, const ViewerVec *);
extern const float lbl_806D85E8;
extern const float lbl_806D85EC;
extern const float lbl_806D85F0;
extern const float lbl_806D85F4;
extern const float lbl_806D85F8;
extern const float lbl_806D85FC;
extern const float lbl_806D8600;
extern const float lbl_806D8604;
extern const float lbl_806D860C;
extern const float lbl_806D8610;
extern const float lbl_806D8618;
extern const float lbl_806D8620;
extern const float lbl_806D8628;
extern const float lbl_806D862C;
extern const float lbl_806D8630;
extern const float lbl_806D8634;
extern const float lbl_806D8638;
extern const char lbl_806D8608[4];
extern const char lbl_806D8614[4];
extern const char lbl_806D861C[4];
extern const char lbl_806D8624[4];
}
// The viewer owns this shared filename, model and adjustment-step pool.
static const char lbl_80367F68[] = "MR_highway_short_A.dat";
static const char lbl_80367F80[] = "MR_highway_long_A.dat";
static const char lbl_80367F98[] = "DK_jungle_short_a.dat";
static const char lbl_80367FB0[] = "DK_jungle_long_a.dat";
static const char lbl_80367FC8[] = "WC_dcity_short_A.dat";
static const char lbl_80367FE0[] = "WC_dcity_long_A.dat";
static const char lbl_80367FF4[] = "PC_land_short_a.dat";
static const char lbl_80368008[] = "PC_land_long_a.dat";
static const char lbl_8036801C[] = "KP_castle_ground_A.dat";
static const char lbl_80368034[] = "KP_castle_ground_B.dat";
static const char lbl_8036804C[] = "RB_road_short_a.dat";
static const char lbl_80368060[] = "RB_road_long_a.dat";
extern "C" const ModelEntry Scene_8015BE44_rodata_80368074[14] = {
    {lbl_80367F68, 10000.0f, 57, 1.0f, -25.0f, -2.0f, 0.032f, 0.034f, 0.0f},
    {lbl_80367F80, 13000.0f, 56, 0.75f, -33.0f, 25.0f, 0.025f, 0.025f, 0.0f},
    {lbl_80367F98, 7000.0f, 59, 0.8f, -15.0f, 3.0f, 0.033f, 0.033f, 0.0f},
    {lbl_80367FB0, 13000.0f, 58, 0.75f, 18.0f, 38.0f, 0.024f, 0.024f, 40.0f},
    {lbl_80367FC8, 17000.0f, 61, 0.7f, -18.0f, 43.0f, 0.024f, 0.024f, 0.0f},
    {lbl_80367FE0, 20000.0f, 60, 0.7f, -63.0f, 37.0f, 0.023f, 0.023f, 0.0f},
    {lbl_80367FF4, 22000.0f, 64, 0.7f, 11.0f, 74.0f, 0.021f, 0.021f, 0.0f},
    {lbl_80368008, 22000.0f, 62, 0.7f, 57.0f, 53.0f, 0.022f, 0.022f, 0.0f},
    {lbl_80368008, 22000.0f, 63, 0.7f, -178.0f, 73.0f, 0.019f, 0.019f, 0.0f},
    {lbl_8036801C, 10000.0f, 66, 1.0f, -20.0f, -7.0f, 0.024f, 0.024f, 0.0f},
    {lbl_80368034, 15000.0f, 65, 0.75f, -18.0f, 16.0f, 0.023f, 0.022f, 0.0f},
    {lbl_8036804C, 15000.0f, 67, 0.7f, -79.0f, 1.0f, 0.019f, 0.019f, 0.0f},
    {lbl_8036804C, 18000.0f, 69, 0.7f, 49.0f, -38.0f, 0.019f, 0.019f, 0.0f},
    {lbl_80368060, 18000.0f, 68, 0.7f, 110.0f, -38.0f, 0.025f, 0.025f, 0.0f},
};
static const float viewerSteps[3] = {10.0f, 10.0f, 10.0f};
extern "C" const char lbl_80368278[] = "clCSSceneCourceAdj";
extern "C" const char lbl_8036828C[] = "clSceneInterface";
static const char viewerFormat[] = "COURCE %03d";

#pragma exceptions on
#pragma push
static inline float ViewerMul(float a, float b) { return a * b; }
extern "C" void fn_8015B790() {
    if (InputMgr_GetPlayer(GetInputManager(),0)->right() > lbl_806D85E8) {
        if (lbl_806D159C < 0) lbl_806D159C = 0;
        else if (++lbl_806D159C > 20) lbl_806D159C = 18;
    } else if (InputMgr_GetPlayer(GetInputManager(),0)->left() > lbl_806D85E8) {
        if (lbl_806D159C > 0) lbl_806D159C = 0;
        else if (--lbl_806D159C < -20) lbl_806D159C = -18;
    } else lbl_806D159C = 0;
    int selected = lbl_806D1594;
    if (lbl_806D159C == 1) { if (++selected >= 14) selected = 0; }
    if (lbl_806D159C == -1) { if (--selected < 0) selected = 13; }
    if (lbl_806D1594 != selected) {
        lbl_806D1594 = selected;
        const ModelEntry *models = Scene_8015BE44_rodata_80368074;
        fn_8015BCC4(models[selected].res, models[selected].scale);
        lbl_806D15A4 = lbl_806D85EC;
        lbl_806D15A8 = lbl_806D85EC;
        return;
    }
    if (InputMgr_GetPlayer(GetInputManager(),0)->pressed(0x400)) {
        if (++lbl_806D1598 >= 3) lbl_806D1598 = 0;
    } else {
        float axis = InputMgr_GetPlayer(GetInputManager(),0)->axis();
        if (axis > lbl_806D85F0) {
            if (lbl_806D15A0 < 0) lbl_806D15A0 = 0;
            else if (++lbl_806D15A0 > 20) lbl_806D15A0 = 18;
        } else if (axis < lbl_806D85F4) {
            if (lbl_806D15A0 > 0) lbl_806D15A0 = 0;
            else if (--lbl_806D15A0 < -20) lbl_806D15A0 = -18;
        } else lbl_806D15A0 = 0;
    }
    float step = lbl_806D85EC;
    if (lbl_806D15A0 == 1 || lbl_806D15A0 == 20) { const float *steps = viewerSteps; step = steps[lbl_806D1598]; }
    if (lbl_806D15A0 == -1 || lbl_806D15A0 == -20) { const float *steps = viewerSteps; step = -steps[lbl_806D1598]; }
    if (InputMgr_GetPlayer(GetInputManager(),0)->held(0x2000)) step = ViewerMul(step, lbl_806D85F8);
    if (lbl_806D85EC != step) {
        switch (lbl_806D1598) {
        case 0: lbl_806D15A4 += step; break;
        case 1: lbl_806D15A8 += step; break;
        case 2: lbl_80677CD8.y += step; break;
        }
    }
    fn_80168EFC(1, lbl_806D85FC, lbl_806D8604 * (lbl_806D1598 + 1) + lbl_806D8600, lbl_806D8608);
    fn_80168EFC(1, lbl_806D85FC, lbl_806D8600, viewerFormat, lbl_806D1594);
    fn_80168EFC(1, lbl_806D860C, lbl_806D8610, lbl_806D8614);
    fn_80168EFC(1, lbl_806D860C, lbl_806D8618, lbl_806D861C);
    fn_80168EFC(1, lbl_806D860C, lbl_806D8620, lbl_806D8624);
    if (!lbl_806D1588 || !lbl_806D158C) return;
    {
        Object_SetJObjPositionX(lbl_806D158C, lbl_806D15A4);
        Object_SetJObjField40(lbl_806D158C, lbl_806D15A8);
        /* fakematch (hand): natural code is `entry = &Scene_8015BE44_rodata_80368074[lbl_806D1594]`.
           The target keeps the scaled index in the entry register and adds the
           table base to it, so the offset has to be a named value first. */
        int off = lbl_806D1594 * 36;
        off += (int)Scene_8015BE44_rodata_80368074;
        const ModelEntry *entry = (const ModelEntry *)off;
        float size = lbl_806D8628 * entry->iconScale;
        fn_80169040(0, lbl_806D862C, lbl_806D8630, size,size, lbl_806D8634 * -entry->iconY, lbl_806D8638, entry->icon, 0);
        void *camera = lbl_806D1588->camera;
        if (camera) HSD_CObjSetEyePosition(camera, &lbl_80677CD8);
    }
}
#pragma pop

#pragma exceptions reset
