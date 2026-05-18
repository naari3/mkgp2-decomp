/*
 * KartReaction Front/Side/Rear @ 0x80040C24 / 0x80040CA0 / 0x80040D1C.
 *
 * 3 sibling triggers that queue a hit-reaction animation on a KartItem
 * when the kart is hit from front/side/rear respectively. Each function:
 *   - returns 0 immediately when the KartItem is inactive (flag204 == 0)
 *   - returns 0 if the item slot is already in a non-idle state
 *     (currentState != 0; Rear skips this check)
 *   - returns 0 if the held item is the lightning bolt (0x51, immune)
 *   - otherwise calls SetAnimState() with a per-direction tuple of
 *     {anim_id, dirX, dirY, dirZ, magnitude} read from sdata and returns 1
 *
 * SetAnimState takes 8 args via the PowerPC EABI:
 *   r3=self, r4=anim_id, r5=unk_zero, r6=trigger_flag,
 *   f1..f4 = (dirX, dirY, dirZ, magnitude)
 *
 * The four float constants live in the .sdata blob at 0x806CF01C..0x806CF048
 * (Rear → Side → Front, 4 floats per direction). They are referenced as
 * individual extern float symbols so CW emits the lfs ... @sda21 sequence
 * that the target uses, matching the auto blob byte-for-byte.
 *
 * #pragma exceptions on/reset wraps the body so CW auto-emits the
 * extab/extabindex entry (one per function), matching the layout that
 * the original CW 1.3.2 build produced for each KartReaction_* function.
 */

typedef unsigned char u8;
typedef int s32;

typedef struct KartItem {
    u8 _pad_000[0x1F0];
    s32 currentState;        /* 0x1F0 */
    u8 _pad_1F4[0x204 - 0x1F4];
    u8 flag204;              /* 0x204 */
    u8 _pad_205[0x2C0 - 0x205];
    s32 currentItemId;       /* 0x2C0 */
} KartItem;

extern void SetAnimState(KartItem *self, int anim_id, int unk_zero, int trigger_flag,
                         float f1, float f2, float f3, float f4);

/* Direction tables in .sdata (Rear / Side / Front, 4 floats each).
 * Values: {2.0, 0.1, 0.1, mag}; mag = 40 (Rear) / 50 (Side, Front). */
extern float lbl_806CF01C;
extern float lbl_806CF020;
extern float lbl_806CF024;
extern float lbl_806CF028;
extern float lbl_806CF02C;
extern float lbl_806CF030;
extern float lbl_806CF034;
extern float lbl_806CF038;
extern float lbl_806CF03C;
extern float lbl_806CF040;
extern float lbl_806CF044;
extern float lbl_806CF048;

#pragma exceptions on
int KartReaction_Front(KartItem *self) {
    if (self->flag204 == 0) {
        return 0;
    }
    if (self->currentState != 0) {
        return 0;
    }
    if (self->currentItemId == 0x51) {
        return 0;
    }
    SetAnimState(self, 0x16, 0, 1, lbl_806CF03C, lbl_806CF040, lbl_806CF044, lbl_806CF048);
    return 1;
}

int KartReaction_Side(KartItem *self) {
    if (self->flag204 == 0) {
        return 0;
    }
    if (self->currentState != 0) {
        return 0;
    }
    if (self->currentItemId == 0x51) {
        return 0;
    }
    SetAnimState(self, 0x15, 0, 1, lbl_806CF02C, lbl_806CF030, lbl_806CF034, lbl_806CF038);
    return 1;
}

int KartReaction_Rear(KartItem *self) {
    if (self->flag204 == 0) {
        return 0;
    }
    if (self->currentItemId == 0x51) {
        return 0;
    }
    SetAnimState(self, 0x14, 0, 1, lbl_806CF01C, lbl_806CF020, lbl_806CF024, lbl_806CF028);
    return 1;
}
#pragma exceptions reset
