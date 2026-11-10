/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct KartItem KartItem;
struct KartItem {
    /* 0x000 */ unsigned char pad_000[0x1F0];
    /* 0x1F0 */ long currentState;
    /* 0x1F4 */ unsigned char pad_1F4[0x10];
    /* 0x204 */ unsigned char flag204;
    /* 0x205 */ unsigned char pad_205[0x43];
    /* 0x248 */ int slot;
    /* 0x24C */ unsigned char pad_24C[0x50];
    /* 0x29C */ void *driver;
    /* 0x2A0 */ unsigned char pad_2A0[0x20];
    /* 0x2C0 */ long currentItemId;
    /* 0x2C4 */ unsigned char pad_2C4[0x74];
    /* 0x338 */ float velocity[3];
};

extern int g_kartStartSlot;
extern void fn_801737CC(void *);

float *KartMovement_GetVelocityPtr(KartItem *kart) {
    return kart->velocity;
}

int KartItem_SetVec3At338(KartItem *kart, float *vec) {
    if (vec == 0) {
        return 0;
    }
    kart->velocity[0] = vec[0];
    kart->velocity[1] = vec[1];
    kart->velocity[2] = vec[2];
    return 1;
}

#pragma exceptions on
int KartItem_IsAtStartSlot(KartItem *kart) {
    if (kart->slot != g_kartStartSlot) {
        return 0;
    }
    fn_801737CC(kart->driver);
    return 1;
}
#pragma exceptions reset
