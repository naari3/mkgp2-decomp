#include "game/Scene_8015B790_private.h"

extern "C" {
void *GetInputManager(); ViewerInput *InputMgr_GetPlayer(void *, int);
extern ViewerPool lbl_80367F68;
extern int lbl_806D1594, lbl_806D1598, lbl_806D159C, lbl_806D15A0;
extern float lbl_806D15A4, lbl_806D15A8;
extern CameraOwner *lbl_806D1588;
extern void *lbl_806D158C;
extern ViewerVec lbl_80677CD8;
void fn_8015BCC4(unsigned int, float);
void fn_80168EFC(int, float, float, const char *, ...);
void fn_80169040(int, int, float,float,float,float,float,float,int);
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
#pragma exceptions on
extern "C" void fn_8015B790() {
    ViewerPool *pool = &lbl_80367F68;
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
        ModelEntry *models = pool->models;
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
    if (lbl_806D15A0 == 1 || lbl_806D15A0 == 20) { float *steps = pool->steps; step = steps[lbl_806D1598]; }
    if (lbl_806D15A0 == -1 || lbl_806D15A0 == -20) { float *steps = pool->steps; step = -steps[lbl_806D1598]; }
    if (InputMgr_GetPlayer(GetInputManager(),0)->held(0x2000)) step *= lbl_806D85F8;
    if (lbl_806D85EC != step) {
        switch (lbl_806D1598) {
        case 0: lbl_806D15A4 += step; break;
        case 1: lbl_806D15A8 += step; break;
        case 2: lbl_80677CD8.y += step; break;
        }
    }
    fn_80168EFC(1, lbl_806D85FC, lbl_806D8604 * (lbl_806D1598 + 1) + lbl_806D8600, lbl_806D8608);
    fn_80168EFC(1, lbl_806D85FC, lbl_806D8600, (char *)pool + 0x338, lbl_806D1594);
    fn_80168EFC(1, lbl_806D860C, lbl_806D8610, lbl_806D8614);
    fn_80168EFC(1, lbl_806D860C, lbl_806D8618, lbl_806D861C);
    fn_80168EFC(1, lbl_806D860C, lbl_806D8620, lbl_806D8624);
    if (!lbl_806D1588 || !lbl_806D158C) return;
    {
        Object_SetJObjPositionX(lbl_806D158C, lbl_806D15A4);
        Object_SetJObjField40(lbl_806D158C, lbl_806D15A8);
        ModelEntry *models = pool->models;
        ModelEntry *entry = &models[lbl_806D1594];
        float size = lbl_806D8628 * entry->iconScale;
        fn_80169040(0, entry->icon, lbl_806D862C, lbl_806D8630, size,size, lbl_806D8634 * -entry->iconY, lbl_806D8638,0);
        void *camera = lbl_806D1588->camera;
        if (camera) HSD_CObjSetEyePosition(camera, &lbl_80677CD8);
    }
}
#pragma exceptions reset
