#include "AI_ItemEffects_private.h"
#include "game/EnemyFaceDraw.h"

struct AIIncomingItem {
    unsigned char reserved00[8];
    int item;
    unsigned char reserved0C[0xAC];
    Vec3c velocity;
};
extern "C" {
unsigned char ItemEffectBus_ArmTornadoAndQuery(void *, int);
unsigned char ItemObject_GetByteAt0xEC(void *, int);
int fn_801DB878(void *, int);
int fn_801DB848(void *, int);
void fn_801E9094(void *);
void fn_801DF010(void *, int, void *);
void fn_801DEAF4(void *, int);
void KartItemAudio_PlaySEByItemId(void *, int);
struct ItemVariants { int items[3]; };
extern const ItemVariants KartController_Update_rodata_803BD770;
extern const float lbl_806DA388;
extern const double lbl_806DA3A0, lbl_806DA3A8;
}

static inline void ItemVectorLength(float &value) {
    volatile float result;
    if (value > lbl_806DA388) {
        double estimate = __frsqrte(value);
        estimate = lbl_806DA3A0 * estimate * (lbl_806DA3A8 - value * (estimate * estimate));
        estimate = lbl_806DA3A0 * estimate * (lbl_806DA3A8 - value * (estimate * estimate));
        estimate = lbl_806DA3A0 * estimate * (lbl_806DA3A8 - value * (estimate * estimate));
        result = value * estimate;
        value = result;
    }
}

int AIItemController::ApplyIncomingItem(AIIncomingItem *incoming) {
    AIItemController *self = this;
    void *bus = self->driver->bus;
    int item = incoming->item;
    if (!ItemEffectBus_ArmTornadoAndQuery(bus, item)) return 0;
    if (self->cooldown > 0) return 0;
    if (item <= 0 || item >= 0x115) return 0;
    float y = incoming->velocity.y;
    float x = incoming->velocity.x;
    float z = incoming->velocity.z;
    Vec3c velocity;
    velocity.x = x;
    velocity.y = y;
    velocity.z = z;
    Vec3c direction = velocity;
    float length = (float)direction.x * (float)direction.x +
        (float)direction.y * (float)direction.y + (float)direction.z * (float)direction.z;
    ItemVectorLength(length);
    if (length <= lbl_806DA388) {
        direction.z = lbl_806DA388;
        direction.y = lbl_806DA388;
        direction.x = lbl_806DA388;
    } else {
        float scale = lbl_806DA390 / length;
        direction.x *= scale;
        direction.y *= scale;
        direction.z *= scale;
    }
    if (item == 0x77) {
        ItemVariants variants = KartController_Update_rodata_803BD770;
        item = variants.items[ItemObject_GetByteAt0xEC(incoming, 0)];
    }
    self->cooldown = fn_801DB878(fn_801DB8F0(), item);
    switch (fn_801DB848(fn_801DB8F0(), item)) {
    case 1:
        ItemEffectBus_ApplyItemConfirm(bus, item);
        TornadoEffect_ApplyItemVisual_Compact(self->visual, item, 1);
        fn_801EC7F0(self->movement, 1);
        return 1;
    case 2:
        fn_801E9094(self->holder);
        break;
    }
    fn_801DF010(self->steering, item, incoming);
    fn_801DEAF4(self->follower, item);
    KartItemAudio_PlaySEByItemId(self->audio, item);
    return 1;
}
