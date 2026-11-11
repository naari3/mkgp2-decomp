#ifndef GAME_RIVALMARKERPRIVATE_H
#define GAME_RIVALMARKERPRIVATE_H
#include "game/FlowScene.h"

struct RivalRender {
    char pad000[0x1e8];
    int active;
    char pad1ec[8];
    int slot, character;
    char pad1fc[0x40];
    int lap;
};
struct RivalPathEntry {
    int field00, id;
    char pad08[0x88];
    RivalRender *kart;
};
struct RivalPath;
struct RivalOther {
    char opaque[0x60];
    RivalOther(RivalRender *, int);
};
struct RivalMarker {
    virtual void _key();
    RivalRender *render;
    int layer;
    unsigned char active;
    float x, y, scale;
    unsigned char flip;
    int resource, alias, variant, texture;
    int field30, field34, field38;
    RivalOther *other;
    RivalMarker(RivalRender *, int);
};
struct RivalMarkerHud {
    void *vtable;
    int countdown, layer, state;
    unsigned char active;
    FlowFader *fade;
    RivalPath *path;
    int order[8];
    RivalRender *karts[8];
    RivalMarker *markers[8];
};
struct RivalPosition { float x, y, z; };
struct RivalWaypoint { int flags; float x, y, z; };
extern "C" {
int Path_GetTotalCount(RivalPath *);
RivalWaypoint *Path_GetWaypointPtr(RivalPath *, int);
int Waypoint_FindNearest(RivalPath *, int, float, float, float, float);
void *GetPlayerCarObject();
float *CarObject_GetTransformMatrix(void *);
RivalRender *CarObject_GetRenderObj(void *);
float *KartDriver_GetKartRootMtx(RivalRender *);
extern const float lbl_806DBE80, lbl_806DBE84, lbl_806DBE88;
extern const float lbl_806DBE8C, lbl_806DBE90, lbl_806DBE98;
extern const float lbl_806DBE9C, lbl_806DBEA0, lbl_806DBEA4;
extern int g_countdownPhase, g_gameMode, g_roundIndex, g_cupId;
extern const float lbl_806DBE60, lbl_806DBE64;
#include "game/types/tween_set_order.h"
void fn_8020A734(FlowFader *, int, float, float);
float fn_8020A6CC(FlowFader *);
void fn_80120A08(int);
int fn_8023DBEC(int);
void *GetEnemyParam();
int *AI_GetItemList(void *, int, int, int, int);
void fn_80243464(RivalMarkerHud *);
void fn_80243C70(RivalMarker *);
float fn_80243074(RivalMarkerHud *, int, const RivalPosition *);
}
extern "C" {
RivalPathEntry *PathManager_GetEntrySubStruct(RivalPath *, int);
int GetDisplayBufferIndex();
unsigned char fn_802317E0(int *, int *, int *, int, int, unsigned char);
unsigned char fn_80231644(int *, int *, int *, int, int);
int fn_80231BD4(int, int, int);
unsigned char fn_80231B74(int);
extern const float lbl_806DBE94;
}
inline RivalMarker::RivalMarker(RivalRender *render_, int layer_) :
    render(render_), layer(layer_), active(0),
    x(lbl_806DBE64), y(lbl_806DBE64), scale(lbl_806DBE94),
    field30(0), field34(0), field38(0) {
    other = new RivalOther(render_, layer_);
    variant = render_->slot;
    if (g_gameMode == 0) {
        if (!fn_802317E0(&alias, &resource, &texture, variant, render_->character, 0)) {
            resource = fn_80231BD4(6, render_->character, 0);
        }
    } else if (g_gameMode == 2) {
        if (!fn_80231644(&alias, &resource, &texture, variant, render_->character)) {
            resource = fn_80231BD4(6, render_->character, 0);
        }
    }
    flip = fn_80231B74(resource);
}
#endif
