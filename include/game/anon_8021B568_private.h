/*
 * 0x8021B568..0x8021BC44: per-player team icon row on the result screen
 * (clCSPartsInerface subclass, vtable TeamIconRow_vtable_804EDD2C).
 */

#include "game/CSParts.h"

struct AnimObj {
    int x0;
    int layer;
};

struct SpriteAnim {
    AnimObj *obj;
    char pad04[0xCC - 0x4];
    SpriteAnim(int res);
    ~SpriteAnim();
};

extern "C" {
extern const int lbl_803C53C0[];
extern int g_localPcbRole;
unsigned char *PcbSyncTable_Ptr(void);
int PcbSlot_GetCharIdByte(int slot);
void SpriteAnimParamBlock_SetKey(SpriteAnim *s, int key, int value);
void SpriteAnimParamBlock_SetAnimParamCached(SpriteAnim *s, int key, int value);
void fn_8019FF6C(AnimObj *o, int loop);
void fn_801A0004(AnimObj *o);
void Sprite_AdvanceAnim(AnimObj *o, float step);
void fn_80120A08(int res);
int GetDisplayBufferIndex(void);
}

struct TeamIcon {
    SpriteAnim *anim;
    int state;
    int slot;
    unsigned char isMe;
    unsigned char locked;
    TeamIcon(int s) : anim(0), state(1), slot(s), isMe(0), locked(0) {
        if (s == GetDisplayBufferIndex()) {
            isMe = 1;
        }
        anim = new SpriteAnim(0xC9);
        SpriteAnimParamBlock_SetAnimParamCached(anim, 0x1567, s + 0x1567);
        fn_8019FF6C(anim->obj, 1);
        if (isMe == 1) {
            SpriteAnimParamBlock_SetAnimParamCached(anim, 0x156D, s + 0x1571);
        } else {
            SpriteAnimParamBlock_SetAnimParamCached(anim, 0x156D, s + 0x156D);
        }
    }
    ~TeamIcon() {
        if (anim != 0) {
            delete anim;
            anim = 0;
        }
    }
};

static inline int SlotTeam(int i) {
    int role = g_localPcbRole;
    int t = 0;
    if (PcbSyncTable_Ptr()[i + 4] == role) {
        if (PcbSlot_GetCharIdByte(i) == 0x2D || PcbSlot_GetCharIdByte(i) == 0x2E ||
            PcbSlot_GetCharIdByte(i) == 0x2F) {
            t = 1;
        }
        if (PcbSlot_GetCharIdByte(i) == 0x31) {
            t = 1;
        }
        if (PcbSlot_GetCharIdByte(i) == 0x32) {
            t = 2;
        }
    }
    if (PcbSlot_GetCharIdByte(i) == 0x30) {
        t = 3;
    }
    return t;
}

struct TeamIconRow : clCSPartsInerface {
/* Update-only TU uses the externally defined Draw method as its vtable key. */
#ifdef TEAM_ICON_ROW_EXTERNAL_VTABLE
    virtual void Draw();
#endif
    virtual void Update();
    int state;
    float x1C;
    int frame;
    int timer;
    unsigned char closing;
    int team[4];
    TeamIcon *icons[4];
    TeamIconRow();
    virtual ~TeamIconRow();
#ifndef TEAM_ICON_ROW_EXTERNAL_VTABLE
    virtual void Draw();
#endif
    int CountFlagged();
    void Close();
    void SetLayer(int layer);
};

