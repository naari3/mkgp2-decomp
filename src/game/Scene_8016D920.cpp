/*
 * 0x8016D920..0x8016DA30: constructor of the JObj-chain marker (vtable
 * lbl_80491134, base vtable lbl_80490FE0). Real C++ for its EH actions;
 * mangled names are bridged in tools/extab_user_renames.json.
 */

struct HSD_JObj;

struct clNormal3D {
    char _opaque[0x5C];
    clNormal3D(void *res, int flags);
};

struct MarkerSource {
    char pad00[0x10];
    HSD_JObj *chain;
};

extern "C" {
extern char lbl_8036D660[];
extern char lbl_8036D680[];
void DebugPrintf(const char *, ...);
HSD_JObj *Archive_GetRootJObj(clNormal3D *);
void fn_802D0BE4(HSD_JObj *, int);
void fn_802D0870(HSD_JObj *, int);
void clNormal3D_SetScale(clNormal3D *, int, float, float, float, float);
void Object_SetJObjScaleXYZ(clNormal3D *, float, float, float);
}

struct CourseMarkerBase {
    virtual void vKeyFunction();
    virtual ~CourseMarkerBase();
    CourseMarkerBase() {}
};

struct MarkerChain : CourseMarkerBase {
    clNormal3D *model;
    HSD_JObj *chain;

    MarkerChain(MarkerSource *src);
    virtual void vKeyFunction2();
};

#pragma exceptions on

MarkerChain::MarkerChain(MarkerSource *src) {
    DebugPrintf(lbl_8036D660);
    model = 0;
    chain = 0;
    model = new clNormal3D(lbl_8036D680, 0);
    if (model == 0) {
        return;
    }
    fn_802D0BE4(Archive_GetRootJObj(model), 0xE00);
    fn_802D0870(Archive_GetRootJObj(model), 0x400);
    clNormal3D_SetScale(model, 0, 0.0f, 1.0f, 0.0f, 0.0f);
    Object_SetJObjScaleXYZ(model, 1.5f, 1.5f, 1.5f);
    chain = src == 0 ? 0 : src->chain;
}

#pragma exceptions reset
