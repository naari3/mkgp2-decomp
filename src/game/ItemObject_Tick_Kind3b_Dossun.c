/* ItemObject_Tick_Kind3b_Dossun (0x800EDE8C): per-frame tick of the Dossun
 * (Thwomp) item. State 1 is held/flying, state 2 dispatches on the drop
 * sub-state, sub-state 3 reels the item back to the kart's joint 13 before
 * it is retired. */
#include "game/DrawEffectAccess.h"

typedef struct DossunWork {
    unsigned char pad0[3];
    unsigned char buildMtx;
    unsigned int timers[4];
    float tether;
    float tetherScale;
    unsigned char pad1C[0x90 - 0x1C];
    unsigned char active;
} DossunWork;

extern const float lbl_806D5ED0; /* 0.0 */
extern const float lbl_806D5ED4; /* 5 deg */
extern void SpriteSlot_InitNonLoop(void *slot, int id);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int on);
extern void Dossun_State1And2_HeldOrFly(unsigned char *self, DossunWork *w);
extern void Dossun_State2_Drop(unsigned char *self, DossunWork *w);
extern int Item_AdvanceTetherToJoint13(unsigned char *self, float *tether, float scale, float a, float b);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void SpriteSlot_Container_Free(unsigned char *self);
extern void Mtx44_Scale_Uniform(float dst[4][4], float src[4][4], float s);
extern void Matrix4_PreMultiplyRotX(float dst[4][4], float src[4][4], float a);
extern void Matrix4_PreMultiplyRotY(float dst[4][4], float src[4][4], float a);
extern void Matrix4_PreMultiplyRotZ(float dst[4][4], float src[4][4], float a);
extern void Mtx44_Translate(float dst[4][4], float src[4][4], Vec *t);

void ItemObject_Tick_Kind3b_Dossun(unsigned char *self)
{
    DossunWork *w = (DossunWork *)(self + 0xEC);

    switch (S8(0xC8)) {
    case 0:
        w->active = 1;
        SpriteSlot_InitNonLoop(SLOT(self), 0x3F);
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(SLOT(self), 1);
        w->buildMtx = 1;
        S8(0x8C) = 4;
        S8(0x8D) = 0;
        S8(0xC8) = 1;
        S8(0xC9) = 0;
    case 1:
        Dossun_State1And2_HeldOrFly(self, w);
        break;
    case 2:
        switch (S8(0xCB)) {
        case 4:
            Dossun_State2_Drop(self, w);
            break;
        case 9:
            Dossun_State2_Drop(self, w);
            break;
        case 0:
            Dossun_State2_Drop(self, w);
            break;
        case 5:
            Dossun_State2_Drop(self, w);
            break;
        case 3:
            switch (S8(0xC9)) {
            case 0:
                GetSpawnPosition(V(0xB8), lbl_806D5ED0, lbl_806D5ED0, lbl_806D5ED0);
                U8(0x3C) = 0;
                w->tether = lbl_806D5ED0;
                w->tetherScale = F(0xC4);
                S8(0xC9)++;
            case 1:
                break;
            }
            if (Item_AdvanceTetherToJoint13(self, &w->tether, w->tetherScale, lbl_806D5ED4, lbl_806D5ED4) != 0) {
                U8(0x28) = 0;
                S8(0xC8) = 3;
                S8(0xC9) = 0;
            }
            break;
        }
        break;
    case 3:
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
        return;
    }

    Vec3_Add_DestFirst(V(0xA0), V(0xA0), V(0xB8));
    if (w->buildMtx) {
        float m[4][4];
        Matrix4_Identity(m);
        Mtx44_Scale_Uniform(m, m, F(0xC4));
        Matrix4_PreMultiplyRotZ(m, m, F(0xB4));
        Matrix4_PreMultiplyRotX(m, m, F(0xAC));
        Matrix4_PreMultiplyRotY(m, m, F(0xB0));
        {
            Vec pos = *V(0xA0);
            Mtx44_Translate(m, m, &pos);
        }
        DbgScene_CopyMatrix3x4Transpose(self + 0x48, m);
    }
    if (w->timers[0] != 0) w->timers[0]--;
    if (w->timers[1] != 0) w->timers[1]--;
    if (w->timers[2] != 0) w->timers[2]--;
    if (w->timers[3] != 0) w->timers[3]--;
}
