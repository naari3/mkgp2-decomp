#ifndef SYSDOLPHIN_BASELIB_FOG_H
#define SYSDOLPHIN_BASELIB_FOG_H

#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h> // IWYU pragma: export

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <sysdolphin/baselib/object.h>

// mkgp2 (newer HSD): flags word at 0x08, size 0x54.
struct HSD_FogAdj {
    /* 0x00 */ HSD_Obj parent;
    /* 0x08 */ u32 flags;
    /* 0x0C */ s16 center;
    /* 0x0E */ u16 width;
    /* 0x10 */ Mtx44 mtx;
    /* 0x50 */ HSD_AObj* aobj;
};

struct HSD_Fog {
    /* 0x00 */ HSD_Obj parent;
    /* 0x08 */ u32 type;
    /* 0x0C */ HSD_FogAdj* fog_adj;
    /* 0x10 */ f32 start;
    /* 0x14 */ f32 end;
    /* 0x18 */ GXColor color;
    /* 0x1C */ HSD_AObj* aobj;
};

struct HSD_FogAdjDesc {
    /* 0x00 */ u32 flags;
    /* 0x04 */ u16 center;
    /* 0x06 */ u16 width;
    /* 0x08 */ Mtx44 mtx;
};

// mkgp2: the info has an anim update callback slot at 0x3C.
struct HSD_FogInfo {
    HSD_ObjInfo parent;
    void (*update)(void* obj, enum_t type, HSD_ObjData* val);
};

struct HSD_FogAdjInfo {
    HSD_ObjInfo parent;
};

struct HSD_FogDesc {
    /* 0x00 */ u32 type;
    /* 0x04 */ HSD_FogAdjDesc* fogadjdesc;
    /* 0x08 */ f32 start;
    /* 0x0C */ f32 end;
    /* 0x10 */ GXColor color;
};

void HSD_FogSet(HSD_Fog*);
HSD_FogAdj* HSD_FogAdjLoadDesc(HSD_FogAdjDesc*);
void HSD_FogInit(HSD_Fog*, HSD_FogDesc*);
void HSD_FogAdjInit(HSD_FogAdj*, HSD_FogAdjDesc*);
void HSD_FogReqAnimByFlags(HSD_Fog*, u32 flags, f32 frame);
void FogUpdateFunc(void* obj, enum_t type, HSD_ObjData* fval);
HSD_Fog* HSD_FogLoadDesc(HSD_FogDesc* desc);

HSD_Fog* HSD_FogAlloc(void);
HSD_FogAdj* HSD_FogAdjAlloc(void);
void HSD_Fog_8037DE7C(HSD_Fog* fog, HSD_AObjDesc* desc);
void HSD_FogReqAnim(HSD_Fog* fog, f32 frame);
void HSD_FogInterpretAnim(HSD_Fog* fog);

#endif
