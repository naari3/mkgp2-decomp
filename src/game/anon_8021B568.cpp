/*
 * 0x8021B568..0x8021BC44: per-player team icon row on the result screen
 * (clCSPartsInerface subclass, vtable lbl_804EDD2C).
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
    int state;
    float x1C;
    int frame;
    int timer;
    unsigned char closing;
    int team[4];
    TeamIcon *icons[4];
    TeamIconRow();
    virtual ~TeamIconRow();
    virtual void Update();
    virtual void Draw();
    int CountFlagged();
    void Close();
    void SetLayer(int layer);
};

int TeamIconRow::CountFlagged() {
    int n = 0;
    for (int i = 0; i < 4; i++) {
        if (team[i] == 1 || team[i] == 3) {
            n++;
        }
    }
    return n;
}

void TeamIconRow::Close() {
    if (closing != 1) {
        closing = 1;
        state = 2;
    }
}

void TeamIconRow::SetLayer(int layer) {
    icons[0]->anim->obj->layer = layer;
    icons[1]->anim->obj->layer = layer;
    icons[2]->anim->obj->layer = layer;
    icons[3]->anim->obj->layer = layer;
}

void TeamIconRow::Draw() {
    for (int i = 0; i < 4; i++) {
        fn_801A0004(icons[i]->anim->obj);
    }
}

void TeamIconRow::Update() {
    switch (state) {
    case 0:
        state = 1;
        break;
    case 1:
        for (int i = 0; i < 4; i++) {
            team[i] = SlotTeam(i);
            TeamIcon *ic = icons[i];
            int t = team[i];
            if (ic->state == t) {
                continue;
            }
            if (t == 0) {
                ic->locked = 0;
            }
            if (ic->locked == 1) {
                continue;
            }
            if (ic->state == 3 && t == 1) {
                ic->state = 2;
                ic->locked = 1;
            } else {
                ic->state = t;
            }
            if (ic->state == 0) {
                SpriteAnimParamBlock_SetKey(ic->anim, 0x1567, 0x156B);
                if (ic->isMe == 0) {
                    SpriteAnimParamBlock_SetKey(ic->anim, 0x156D, ic->slot + 0x1575);
                }
            } else {
                SpriteAnimParamBlock_SetKey(ic->anim, 0x1567, ic->slot + 0x1567);
                if (ic->isMe == 0) {
                    SpriteAnimParamBlock_SetKey(ic->anim, 0x156D, ic->slot + 0x156D);
                } else {
                    SpriteAnimParamBlock_SetKey(ic->anim, 0x156D, ic->slot + 0x1571);
                }
            }
            if (ic->state == 1 || ic->state == 3) {
                SpriteAnimParamBlock_SetKey(ic->anim, 0x156C, 0x156C);
            } else {
                SpriteAnimParamBlock_SetKey(ic->anim, 0x156C, 0x1ECD);
            }
            SpriteAnimParamBlock_SetKey(ic->anim, 0x157A, lbl_803C53C0[ic->state]);
        }
        break;
    case 2:
        timer++;
        if (timer >= 15) {
            state = 3;
        }
        break;
    }
    frame++;
    for (int i = 0; i < 4; i++) {
        Sprite_AdvanceAnim(icons[i]->anim->obj, 0.0165f);
    }
}

TeamIconRow::~TeamIconRow() {
    for (int i = 0; i < 4; i++) {
        if (icons[i] != 0) {
            delete icons[i];
            icons[i] = 0;
        }
    }
    fn_80120A08(0x157B);
    fn_80120A08(0x1579);
    fn_80120A08(0x157A);
    fn_80120A08(0x156C);
    fn_80120A08(0x156B);
    fn_80120A08(0x1567);
    fn_80120A08(0x156D);
    fn_80120A08(0x1575);
}

TeamIconRow::TeamIconRow() {
    state = 0;
    x1C = 0.0f;
    frame = 0;
    timer = 0;
    closing = 0;
    icons[0] = 0;
    icons[1] = 0;
    icons[2] = 0;
    icons[3] = 0;
    team[0] = 0;
    team[1] = 0;
    team[2] = 0;
    team[3] = 0;
    PreloadResource(0x157B);
    PreloadResource(0x1579);
    PreloadResource(0x157A);
    PreloadResource(0x156C);
    PreloadResource(0x156B);
    PreloadResource(0x1567);
    PreloadResource(0x156D);
    PreloadResource(0x1575);
    for (int i = 0; i < 4; i++) {
        icons[i] = new TeamIcon(i);
        AnimObj *o = icons[i]->anim->obj;
        *(float *)((char *)o + 0xC) = 143.0f * i + 105.0f;
        *(float *)((char *)o + 0x10) = 387.0f;
    }
}
