/* Fall recovery state. Layouts describe only fields observed in this function. */
struct Vec3 { float x, y, z; };
struct GabyouItemFallView {
    unsigned char pad00[0x28];
    unsigned char active;
    unsigned char pad29[3];
    float lifetime;
    unsigned char pad30[0x70];
    Vec3 position;
    float yaw;
    unsigned char padB0[8];
    Vec3 velocity;
    unsigned char padC4[4];
    unsigned char state;
    signed char phase;
    unsigned char padCA;
    unsigned char kind;
};
struct GabyouFallContext {
    unsigned char pad00[4];
    unsigned int timer;
    unsigned char pad08[0xC];
    float groundHeight;
    unsigned char pad18[0x1C];
    Vec3 kartOffset;
    Vec3 velocity;
    unsigned char pad4C[0x50];
    void *kart;
};
extern "C" {
extern float lbl_806D62C0, lbl_806D62F0, lbl_806D6310;
extern float lbl_806D62FC, lbl_806D6300;
signed char ItemObject_GetGroundTypeAt(Vec3, float *, int);
void *KartDriver_GetKartRootMtx(void *);
void Mtx44_GetTranslation_RowMajor(Vec3 *, void *);
void Vec3_Subtract_DestFirst(Vec3 *, const Vec3 *, const Vec3 *);
void Vec3_Copy(Vec3 *, const Vec3 *);
void GetSpawnPosition(Vec3 *, float, float, float);
void Vec3_Add_DestFirst(Vec3 *, const Vec3 *, const Vec3 *);
float BuildOrientationFromYaw(float);
void Item_DecayVelocityScalar(GabyouItemFallView *, float);
unsigned char FinalLapCoinJump_CheckActiveForObject(void *);

static inline bool DecayLifetime(GabyouItemFallView *item, float decay)
{
    float minimum = 0.0f;
    item->lifetime -= decay;
    if (item->lifetime < minimum)
        return true;
    return false;
}

void GabyouItem_FallRecoveryTick(GabyouItemFallView *item, GabyouFallContext *context)
{
    Vec3 initialKartPosition;
    Vec3 currentKartPosition;
    float height;
    switch (item->phase) {
    case 0: {
        ItemObject_GetGroundTypeAt(item->position, &context->groundHeight, 0);
        if ((int)item->kind != 5)
            context->timer = 10;
        else
            context->timer = 0;
        if ((int)item->kind == 8)
            item->velocity.y = lbl_806D62C0;
        if (context->kart) {
            Mtx44_GetTranslation_RowMajor(&initialKartPosition, KartDriver_GetKartRootMtx(context->kart));
            Vec3_Subtract_DestFirst(&context->kartOffset, &item->position, &initialKartPosition);
            Vec3_Copy(&context->velocity, &item->velocity);
            GetSpawnPosition(&item->velocity, lbl_806D62C0, lbl_806D62C0, lbl_806D62C0);
        }
        ++item->phase;
        break;
    }
    case 1:
        break;
    }
    if (context->timer == 0) {
        if (DecayLifetime(item, lbl_806D62F0)) {
            item->active = 0;
            item->state = 3;
            item->phase = 0;
            return;
        }
    }
    if (!context->kart) {
        if ((int)item->kind != 8)
            item->velocity.y += lbl_806D6310;
        if (ItemObject_GetGroundTypeAt(item->position, &height, 0) != 0) {
            item->position.y += height - context->groundHeight;
            context->groundHeight = height;
        }
    } else {
        context->velocity.y += lbl_806D6310;
        Vec3_Add_DestFirst(&context->kartOffset, &context->kartOffset, &context->velocity);
        Mtx44_GetTranslation_RowMajor(&currentKartPosition, KartDriver_GetKartRootMtx(context->kart));
        Vec3_Add_DestFirst(&item->position, &currentKartPosition, &context->kartOffset);
    }
    switch ((signed char)item->kind) {
    case 1:
        item->yaw = BuildOrientationFromYaw(item->yaw - lbl_806D62FC);
        break;
    case 4:
        item->yaw = BuildOrientationFromYaw(item->yaw - lbl_806D62FC);
        break;
    case 9:
        item->yaw = BuildOrientationFromYaw(lbl_806D62FC + item->yaw);
        break;
    case 8:
    default:
        break;
    }
    Item_DecayVelocityScalar(item, lbl_806D6300);
    if (FinalLapCoinJump_CheckActiveForObject(context->kart))
        item->active = 0;
    else
        item->active = 1;
}
}
