/* Impact state for item types 0x2e..0x31. Views contain only observed fields.
 * Target and callees audited from disassembly; Ghidra was unavailable.
 * Ground/audio positions are copied by-value in the observed ABI. Literal
 * zero in the expiry calculation is required for the native FP web; the
 * existing shared-pool postprocessor maps it to lbl_806D5D20.
 * Remaining mismatch: counter store scheduling within InitializeImpactScale.
 * Native text is 816 bytes; automatic extab/extabindex are exact. */
struct ImpactVec3 { float x, y, z; };
struct ImpactItem {
    unsigned char opaque00[8];
    int kind;
    unsigned char opaque0c[0x1c];
    unsigned char enabled;
    unsigned char opaque29[3];
    float lifetime;
    ImpactVec3 scale;
    unsigned char opaque3c[0x64];
    ImpactVec3 position;
    float yaw;
    unsigned char opaqueb0[8];
    ImpactVec3 velocity;
    unsigned char opaquec4[4];
    signed char state, phase;
    unsigned char opaqueca;
    unsigned char groundType;
};
struct ImpactContext {
    unsigned char opaque00[4];
    unsigned int counter, delay;
    unsigned char opaque0c[8];
    float groundY;
    unsigned char opaque18[0x1c];
    ImpactVec3 relativePosition, velocity;
    unsigned char opaque4c[0x50];
    void *driver;
};
extern "C" {
signed char ItemObject_GetGroundTypeAt(ImpactVec3, float *, int);
void GetSpawnPosition(ImpactVec3 *, float, float, float);
void *KartDriver_GetKartRootMtx(void *);
void Mtx44_GetTranslation_RowMajor(ImpactVec3 *, const void *);
void Vec3_Subtract_DestFirst(ImpactVec3 *, const ImpactVec3 *, const ImpactVec3 *);
void Vec3_Add_DestFirst(ImpactVec3 *, const ImpactVec3 *, const ImpactVec3 *);
void SoundMgr_PlaySE_Positional(int, ImpactVec3, int);
float BuildOrientationFromYaw(float);
void Item_DecayVelocityScalar(ImpactItem *, float);
extern float lbl_806D5D20, lbl_806D5D24, lbl_806D5D2C;
extern float lbl_806D5D50, lbl_806D5D54, lbl_806D5D58;
extern float lbl_806D5D5C, lbl_806D5D60;

static inline void InitializeImpactScale(ImpactItem *item, ImpactContext *context, float scale)
{
    context->counter = 0;
    GetSpawnPosition(&item->scale, scale, scale, scale);
}

void GabyouItem_OnImpactTick_2Eto31(ImpactItem *item, ImpactContext *context)
{
    ImpactVec3 initialTranslation;
    ImpactVec3 currentTranslation;
    float groundY;
    float zero, decrement, lifetime;
    switch (item->phase) {
    case 0:
        ItemObject_GetGroundTypeAt(item->position, &context->groundY, 0);
        if ((int)item->groundType != 5) context->delay = 10;
        else context->delay = 0;
        if ((int)item->groundType == 5) item->velocity.y = lbl_806D5D20;
        if (context->driver) {
            GetSpawnPosition(&item->velocity, lbl_806D5D20, lbl_806D5D20, lbl_806D5D20);
            Mtx44_GetTranslation_RowMajor(&initialTranslation, KartDriver_GetKartRootMtx(context->driver));
            Vec3_Subtract_DestFirst(&context->relativePosition, &item->position, &initialTranslation);
            GetSpawnPosition(&context->velocity, lbl_806D5D20, lbl_806D5D50, lbl_806D5D20);
            SoundMgr_PlaySE_Positional(0xcb, item->position, 0);
        }
        InitializeImpactScale(item, context, lbl_806D5D24);
        ++item->phase;
        break;
    case 1:
    default:
        break;
    }
    if (context->delay == 0) {
        lifetime = item->lifetime;
        decrement = lbl_806D5D54;
        zero = 0.0f;
        item->lifetime = lifetime - decrement;
        if (item->lifetime < zero) {
            item->enabled = 0;
            item->state = 3;
            item->phase = 0;
            return;
        }
    }
    if (!context->driver) {
        if ((int)item->groundType != 5) item->velocity.y += lbl_806D5D58;
        if (ItemObject_GetGroundTypeAt(item->position, &groundY, 0)) {
            item->position.y += groundY - context->groundY;
            context->groundY = groundY;
        }
    } else {
        context->velocity.y += lbl_806D5D58;
        Vec3_Add_DestFirst(&context->relativePosition, &context->relativePosition, &context->velocity);
        Mtx44_GetTranslation_RowMajor(&currentTranslation, KartDriver_GetKartRootMtx(context->driver));
        Vec3_Add_DestFirst(&item->position, &currentTranslation, &context->relativePosition);
    }
    item->yaw = BuildOrientationFromYaw(lbl_806D5D5C + item->yaw);
    switch ((signed char)item->groundType) {
    case 9: item->yaw = BuildOrientationFromYaw(lbl_806D5D60 + item->yaw); break;
    case 0: item->yaw = BuildOrientationFromYaw(item->yaw - lbl_806D5D60); break;
    case 5: default: break;
    }
    switch (item->kind) {
    case 0x2e: Item_DecayVelocityScalar(item, lbl_806D5D24); break;
    case 0x2f: Item_DecayVelocityScalar(item, lbl_806D5D24); break;
    case 0x30: Item_DecayVelocityScalar(item, lbl_806D5D2C); break;
    case 0x31: Item_DecayVelocityScalar(item, lbl_806D5D2C); break;
    }
}
}
