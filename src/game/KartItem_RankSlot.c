/*
 * Kart rank-slot registration, 0x8003F418..0x8003F518.
 */

typedef struct RankKart {
    unsigned char pad000[0x1F4];
    int field1F4;
    int field1F8;
    unsigned char pad1FC[0x23C - 0x1FC];
    int rankSlot; /* 0x23C */
    unsigned char pad240[4];
    unsigned char rankSlotValid; /* 0x244 */
    unsigned char pad245[0x2D0 - 0x245];
    unsigned char kartIndex; /* 0x2D0 */
    unsigned char pad2D1[0x34A - 0x2D1];
    unsigned short time[6]; /* 0x34A */
    unsigned char pad356[0x358 - 0x356];
    int field358;
} RankKart;

extern const float lbl_806D2540;

int RankSlot_AppendOrUpdate(unsigned char kart, int a1, int a2, void *time,
                            unsigned char b18, unsigned char b19, int a1c, unsigned char b28,
                            float f20, float f24, int index);

#pragma exceptions on

int KartItem_GetOrAssignId(RankKart *kart) {
    if (kart->rankSlotValid == 1) {
        return kart->rankSlot;
    }
    kart->rankSlot = RankSlot_AppendOrUpdate(kart->kartIndex, kart->field1F4, kart->field1F8, kart->time, 0, 0,
                                             kart->field358, 1, lbl_806D2540, lbl_806D2540, kart->rankSlot);
    kart->rankSlotValid = 1;
    return kart->rankSlot;
}

int KartMovement_CalcFinishPosition(RankKart *kart, unsigned char finished) {
    if (kart->rankSlotValid == 1) {
        return kart->rankSlot;
    }
    kart->rankSlot = RankSlot_AppendOrUpdate(kart->kartIndex, kart->field1F4, kart->field1F8, kart->time, 0, 0,
                                             kart->field358, finished, lbl_806D2540, lbl_806D2540, -1);
    kart->rankSlotValid = 1;
    return kart->rankSlot;
}

#pragma exceptions reset
