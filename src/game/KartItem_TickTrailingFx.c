/* KartItem_TickTrailingFx @ 0x8003EF20: steps the held item effect and keeps
 * its trailing sound effect following the kart until the item is cleared. */

typedef struct ItemKartFlag {
    unsigned char pad0[4];
    unsigned char active; /* 0x4 */
} ItemKartFlag;

typedef struct ItemKart {
    void *object;
    unsigned char pad004[0xC - 0x4];
    void *field00C;
    unsigned char pad010[0x174 - 0x10];
    unsigned char field174;
    unsigned char pad175[0x1E0 - 0x175];
    float stunTime; /* 0x1E0 */
    unsigned char pad1E4[0x205 - 0x1E4];
    unsigned char flag205;
    unsigned char pad206[0x248 - 0x206];
    int field248;
    unsigned char pad24C[0x290 - 0x24C];
    int counter290;
    unsigned char pad294[0x29C - 0x294];
    void *field29C;
    unsigned char pad2A0[4];
    int hitDir; /* 0x2A4 */
    unsigned char pad2A8[0x2B0 - 0x2A8];
    unsigned char field2B0;
    unsigned char pad2B1[2];
    unsigned char iseActive; /* 0x2B3 */
    int field2B4;
    unsigned char pad2B8[0x2C0 - 0x2B8];
    int currentItemId; /* 0x2C0 */
    unsigned char pad2C4[4];
    int currentISESlot; /* 0x2C8 */
    unsigned char pad2CC[0x2DC - 0x2CC];
    void *iseSlots[20]; /* 0x2DC */
    void *field32C;
    unsigned char pad330[0x35C - 0x330];
    ItemKartFlag *field35C;
    ItemKartFlag *field360;
} ItemKart;

void ISESlot_Deactivate(void *slot);
void ISESlot_StopEffect(void *slot, int a, int b);
void ItemEffectState_Init(void *state, int id);
void fn_80173B68(void *p, int v);
void fn_80173BE8(void *p);

static inline void ClearCurrentItem(ItemKart *kart)
{
    if (kart->iseActive == 1) {
        ISESlot_Deactivate(kart->iseSlots[kart->currentISESlot]);
    }
    kart->field2B0 = 0;
    kart->iseActive = 0;
    kart->field2B4 = 0;
    kart->currentISESlot = -1;
    kart->currentItemId = -1;
    kart->flag205 = 0;
    if (kart->field32C != 0) {
        ItemEffectState_Init(kart->field32C, -1);
    }
    kart->field174 = 0;
    fn_80173B68(kart->field29C, 0);
    fn_80173BE8(kart->field29C);
    if (kart->field35C != 0) {
        kart->field35C->active = 0;
    }
    if (kart->field360 != 0) {
        kart->field360->active = 0;
    }
    fn_80173BE8(kart->field29C);
}

typedef struct Vec3f {
    float x, y, z;
} Vec3f;

extern const float lbl_806D25A8;
extern const float lbl_806D25AC;
extern const float lbl_806D25B0;
void ISESlot_StartCleanup(void *slot, int arg);
void ISESlot_SetByte18c(void *slot, int value);
unsigned char fn_8016C360(int se);
int SoundMgr_PlaySE(int id);
float *Object_GetJObjLocalMatrix(void *object);
void fn_8016C288(int se, Vec3f *pos);
void fn_8016C394(int se);

int KartItem_TickTrailingFx(ItemKart *kart)
{
    int slot = kart->currentISESlot;
    int se;

    if (slot == -1) {
        return 0;
    }
    if (kart->field2B4 == 0 && kart->stunTime >= lbl_806D25A8) {
        ISESlot_StartCleanup(kart->iseSlots[slot], 5);
        kart->field2B4 = 1;
    }
    se = ((kart->field248 & 0xF) << 27) | 0xB3;
    if (kart->field2B4 == 1) {
        float *mtx;
        Vec3f pos;

        if (!fn_8016C360(se)) {
            SoundMgr_PlaySE(se);
        }
        if (kart->object == 0 || kart->field00C == 0) {
            mtx = 0;
        } else {
            mtx = Object_GetJObjLocalMatrix(kart->object);
        }
        pos.x = mtx[3];
        pos.y = mtx[7];
        pos.z = mtx[11];
        fn_8016C288(se, &pos);
    }
    if (kart->counter290 != 0 && kart->stunTime >= lbl_806D25AC) {
        kart->stunTime = lbl_806D25B0;
        kart->counter290--;
    }
    if (kart->field2B4 == 1 && kart->stunTime >= lbl_806D25AC) {
        ISESlot_SetByte18c(kart->iseSlots[kart->currentISESlot], 1);
        kart->field2B4 = 2;
        ClearCurrentItem(kart);
        fn_8016C394(se);
    }
    return 1;
}
