#include "game/types/text_word.h"
/* CelebPop17_Update. This TU owns the shared effect .rodata block
 * (0x80328EB8..0x80329908): the original effects file addressed it from one
 * section anchor, so the per-pop tables must live here to get the target's
 * addi+lwzx form. Layout follows target accesses; Ghidra exposes an untyped
 * self pointer.
 */
#include "game/types/Vec.h"
struct Effect { char p0[16]; int index; char slot[20]; char visible; char p29[3]; float alpha; char p30[0x5c]; Vec pos; char p98[12]; Vec velocity; float scale; signed char state; char pb5[0xcb]; unsigned int timer; };
/* .rodata 0x80328EB8..0x80329908: shared effect tables (section anchor of the original effects TU) */
extern "C" const unsigned int CelebPop17Update_rodata_80328EB8[255] = {
    0x3F800000, 0x3F333333, 0x3F666666, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000,
    0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000,
    0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000,
    0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000,
    0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000,
    0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000,
    0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000,
    0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000,
    0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000,
    0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000,
    0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB
};
extern "C" const unsigned int ParticleBurst_Draw_rodata_803292B4[5] = {
    0xFFFFFFFF, 0x000000FF, 0x000000FF, 0xFFFF00FF, 0x00FF0000
};
extern "C" const unsigned int ParticleBurst_DrawCb_rodata_803292C8[3] = {
    0x00000000, 0x00000000, 0x3F800000
};
extern "C" const unsigned int TripleBladeRing_SetWorldYaw_rodata_803292D4[3] = {
    0x00000000, 0x41700000, 0x41F00000
};
extern "C" const unsigned int Kart_rodata_803292E0[60] = {
    0x00002B00, 0x00002B01, 0x00002B02, 0x00002B03, 0xBFCEA897, 0x3FC5C2E3, 0x3E9320DA, 0x3FCA46F1,
    0x3FC5C2E3, 0x3E9320DA, 0x3FCA46F1, 0x40A128F6, 0x3E9320DA, 0xBFCEA897, 0x40A128F6, 0x3E9320DA,
    0xBFCEA897, 0x3FC5C2E3, 0x3DB2E9CC, 0x3FCA46F1, 0x3FC5C2E3, 0x3DB2E9CC, 0x3FCA46F1, 0x40A128F6,
    0x3DB2E9CC, 0xBFCEA897, 0x40A128F6, 0x3DB2E9CC, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000001, 0xFFFFFFFF,
    0x00000001, 0x00000001, 0xFFFFFFFF, 0x00000001, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000001, 0xFFFFFFFF,
    0x00000001, 0x00000001, 0xFFFFFFFF, 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 0x00000001, 0x00000001,
    0x00000001, 0x00000000, 0x00000000, 0x00000000
};
extern "C" const unsigned int KartPair3ArmUpdate_rodata_803293D0[3] = {
    0x00000000, 0x40060A90, 0x40860A90
};
extern "C" const unsigned int CarrotItemEffect_AddDraw_rodata_803293DC[38] = {
    0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x3C23D70A, 0x3CA3D70A, 0xBFCEA897, 0x3FC5C2E3,
    0x3E3FDB4C, 0x3FCA46F1, 0x3FC5C2E3, 0x3E3FDB4C, 0x3FCA46F1, 0x40A128F6, 0x3E3FDB4C, 0xBFCEA897,
    0x40A128F6, 0x3E3FDB4C, 0xBFCEA897, 0x3FC5C2E3, 0x3DB2E9CC, 0x3FCA46F1, 0x3FC5C2E3, 0x3DB2E9CC,
    0x3FCA46F1, 0x40A128F6, 0x3DB2E9CC, 0xBFCEA897, 0x40A128F6, 0x3DB2E9CC, 0x00000000, 0x00000001,
    0x00000001, 0x00000001, 0x00000001, 0x00000000, 0x00000000, 0x00000000
};
extern "C" const unsigned int KartBurstShard_SpawnSet_rodata_80329474[6] = {
    0xC2B40000, 0xC2580000, 0xC1900000, 0x41900000, 0x42580000, 0x42B40000
};
extern "C" const unsigned int TwinSpriteOverlay_AddDraw_rodata_8032948C[3] = {
    0x00000000, 0x00000000, 0x3F800000
};
extern "C" const unsigned int TwinSpriteOverlay_Render_rodata_80329498[21] = {
    0x43960000, 0xC2200000, 0x00000000, 0x43AA0000, 0xC2C80000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x42B40000, 0xC1B00000, 0x00000000, 0x43960000, 0xC2A00000, 0x00000000, 0x44208000,
    0xC2200000, 0x00000000, 0x3FDF66F0, 0x00000000, 0x405F66F0
};
extern "C" const char lbl_803294EC[0x13] = "chara_pop_01_joint";
extern "C" const char lbl_80329500[0x13] = "chara_pop_02_joint";
extern "C" const char lbl_80329514[0x13] = "chara_pop_03_joint";
extern "C" const char lbl_80329528[0x13] = "chara_pop_04_joint";
extern "C" const char lbl_8032953C[0x13] = "chara_pop_05_joint";
extern "C" const char lbl_80329550[0x13] = "chara_pop_06_joint";
extern "C" const char lbl_80329564[0x13] = "chara_pop_07_joint";
extern "C" const char lbl_80329578[0x13] = "chara_pop_08_joint";
extern "C" const char lbl_8032958C[0x13] = "chara_pop_09_joint";
extern "C" const char lbl_803295A0[0x13] = "chara_pop_10_joint";
extern "C" const char lbl_803295B4[0x13] = "chara_pop_11_joint";
extern "C" const char lbl_803295C8[0x13] = "chara_pop_12_joint";
extern "C" const char lbl_803295DC[0x12] = "chara_null1_joint";
extern "C" const unsigned int data_80419FB8_rodata_803295F0[5] = {TEXT_WORD('c', 'h', 'a', 'r'), TEXT_WORD('a', '_', 'p', 'o'), TEXT_WORD('p', '_', '0', '0'), TEXT_WORD('_', 'j', 'o', 'i'), TEXT_WORD('n', 't', 0, 0)};
static const int celebDelay[17] = {1, 2, 3, 5, 7, 9, 13, 16, 18, 10, 10, 10, 10, 18, 27, 36, 47};
static const int celebAnim[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1};
static const int celebDuration[17] = {15, 15, 15, 15, 15, 15, 22, 24, 24, 15, 30, 30, 30, 30, 30, 30, 30};
static const int celebX0[17] = {160, 187, 116, 134, 188, 169, 215, 102, 157, 147, 160, 171, 160, 189, 197, 148, 160};
static const int celebX1[17] = {160, 187, 116, 134, 188, 169, 241, 91, 157, 147, 352, -50, 19, -4, 338, 380, 19};
static const int celebY0[17] = {120, 150, 123, 149, 114, 154, 129, 142, 103, 128, 120, 150, 120, 129, 149, 158, 120};
static const int celebY1[17] = {120, 150, 123, 149, 114, 154, 116, 150, 103, 128, -2, 243, 206, 38, 33, 168, 206};
extern "C" const unsigned int VfxBannerSequence_Tick_rodata_803297E0[68] = {
    0x00000AD6, 0x00000AD7, 0x00000AD8, 0x00000AD9, 0x00000ADA, 0x00000ADB, 0x00000ADC, 0x00000ADD,
    0x00000ADE, 0x00000ADF, 0x00000AE0, 0x00000AE1, 0x00000AE2, 0x00000AE3, 0x00000AE4, 0x00000AE5,
    0x00000AE6, 0x00000AE7, 0x00000AE8, 0x00000AE9, 0x00000AEA, 0x00000AEB, 0x00000AEC, 0x00000AED,
    0x00000AEE, 0x00000AEF, 0x00000AF0, 0x00000AF1, 0x00000AF2, 0x00000AF3, 0x00000AF4, 0x00000AF5,
    0x00000AF6, 0x00000AF7, 0x00000AF8, 0x00000AF9, 0x00000AFA, 0x00000AFB, 0x00000AFC, 0x00000AFD,
    0x00000AFE, 0x00000AFF, 0x00000B00, 0x00000B01, 0x00000B02, 0x00000B03, 0x00000B04, 0x00000B05,
    0x00000B06, 0x00000B07, 0x00000B08, 0x00000B09, 0x00000B0A, 0x00000B0B, 0x00000B0C, 0x00000B0D,
    0x00000B0E, 0x00000B0F, 0x00000B10, 0x00000B11, 0x00000B12, 0x00000B13, 0x00000B14, 0x00000B15,
    0x00000B16, 0x00000B17, 0x00000B18, 0x00000B19
};
extern "C" const char lbl_803298F0[0x14] = "item_carrot_1_joint";
extern "C" {
extern const float lbl_806D5044,lbl_806D5048,lbl_806D504C,lbl_806D5050,lbl_806D5054,lbl_806D5058,lbl_806D505C;
void VfxSlot_BindResourceEx(void*,int,int);
#ifdef __MWERKS__
void VfxSlot_SetPositionFromVec(void*,Vec);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void VfxSlot_SetPositionFromVec(void*, Vec *);
static inline void VfxSlot_SetPositionFromVec_ByValue(void*a0, Vec a1) { VfxSlot_SetPositionFromVec(a0, &a1); }
#define VfxSlot_SetPositionFromVec VfxSlot_SetPositionFromVec_ByValue
#endif
void VfxSlot_SetScaleUniform(void*,float);
void Vec3_Add_DestFirst(Vec*,const Vec*,const Vec*);
void DrawEffect_Free(Effect*);
void CelebPop17_Update(Effect *e) {
    switch(e->state) {
    case 0:
        if(celebAnim[e->index]==0) VfxSlot_BindResourceEx(e->slot,0x95,0);
        else VfxSlot_BindResourceEx(e->slot,0x96,0);
        e->timer=celebDelay[e->index]-1;
        e->alpha=1.0f;
        e->scale=lbl_806D5048;
        e->visible=0;
        e->pos.x+=lbl_806D5044*((float)celebX0[e->index]-lbl_806D504C);
        e->pos.y+=lbl_806D5044*((float)celebY0[e->index]-lbl_806D5050);
        e->pos.y+=lbl_806D5054;
        e->velocity.x=lbl_806D5044*((float)(celebX1[e->index]-celebX0[e->index])/(float)celebDuration[e->index]);
        e->velocity.y=lbl_806D5044*((float)(celebY1[e->index]-celebY0[e->index])/(float)celebDuration[e->index]);
        e->velocity.z=0.0f;
        ++e->state;
    case 1:
        if(e->timer) --e->timer;
        if(!e->timer) { e->timer=celebDuration[e->index]; ++e->state; }
        break;
    case 2:
        e->visible=1;
        if((int)(celebDuration[e->index]-e->timer)<5) {
            e->scale+=lbl_806D5048;
            if(1.0f<e->scale) e->scale=1.0f;
        } else {
            e->scale+=lbl_806D5058/(float)(celebDuration[e->index]-5);
            e->alpha-=1.0f/(float)(celebDuration[e->index]-5);
            if(e->alpha<0.0f) e->alpha=0.0f;
        }
        Vec3_Add_DestFirst(&e->pos,&e->pos,&e->velocity);
        VfxSlot_SetPositionFromVec(e->slot,e->pos);
        VfxSlot_SetScaleUniform(e->slot,lbl_806D505C*e->scale);
        if(e->timer) --e->timer;
        if(!e->timer) DrawEffect_Free(e);
        break;
    }
}
}
