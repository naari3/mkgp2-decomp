#define TEAM_ICON_ROW_EXTERNAL_VTABLE
#include "game/anon_8021B568_private.h"

static inline int QuerySlotTeam(int i) {
    int role = g_localPcbRole;
    int t = 0;
    int syncRole = PcbSyncTable_Ptr()[i + 4];
    if (syncRole == role) {
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

void TeamIconRow::Update() {
    TeamIcon *ic;
    TeamIconRow *cursor;
    switch (state) {
    case 0:
        state = 1;
        break;
    case 1: {
        int i = 0;
        for (cursor = this; i < 4; i++, cursor = (TeamIconRow *)((char *)cursor + sizeof(int))) {
            cursor->team[0] = QuerySlotTeam(i);
            ic = cursor->icons[0];
            int t = cursor->team[0];
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
            if (ic->state != 1 && ic->state != 3) {
                SpriteAnimParamBlock_SetKey(ic->anim, 0x156C, 0x1ECD);
            } else {
                SpriteAnimParamBlock_SetKey(ic->anim, 0x156C, 0x156C);
            }
            SpriteAnimParamBlock_SetKey(ic->anim, 0x157A, lbl_803C53C0[ic->state]);
        }
        break;
    }
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
