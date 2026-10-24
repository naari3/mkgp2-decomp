typedef struct KartItem {
    unsigned char pad_000[0x248];
    int slot;
    unsigned char pad_24C[0x50];
    void *driver;
    unsigned char pad_2A0[0x98];
    float velocity[3];
} KartItem;

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
