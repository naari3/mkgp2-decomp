/* ASM-derived partial ABI views; Ghidra types were unavailable.
 * Only GabyouItem_ReturnToHandTick, .text [800FA3D8,800FA6DC).
 * TransformVec3 takes its third vector by value (caller-owned copy).
 * Text and automatic EH/index match exactly. Keep the selected radius in
 * the scale expression so it remains a temporary across the magnitude call.
 */
struct GabyouReturnVec { float x, y, z; };
struct GabyouReturnMatrix { float m[16]; };
struct GabyouReturnTable { float value[11]; };
struct GabyouReturnItem {
    unsigned char pad00[0x28]; unsigned char active;
    unsigned char pad29[3]; float lifetime;
    unsigned char pad30[0xC]; unsigned char flag3C;
    unsigned char pad3D[0x63]; GabyouReturnVec position;
    float pitch, yaw, roll; GabyouReturnVec velocity;
    float speed; unsigned char state; signed char phase;
};
struct GabyouReturnContext {
    unsigned char pad00[4]; unsigned int timer;
    unsigned char pad08[0x2C]; GabyouReturnVec localPosition;
    unsigned char pad40[0x5C]; void *kart;
};
extern "C" {
const void *KartDriver_GetJointByIdx(void *, int);
void Mtx_TransposeToMtx44(GabyouReturnMatrix *, const void *);
void Mtx44_GetTranslation_ColMajor(GabyouReturnVec *, const GabyouReturnMatrix *);
float Vec3_ToYaw(const GabyouReturnVec *);
float Vec3_HorizontalYawTo(const GabyouReturnVec *, const GabyouReturnVec *);
double FAbs_FloatAsDouble(float);
void Vec3_Subtract_DestFirst(GabyouReturnVec *, const GabyouReturnVec *, const GabyouReturnVec *);
void Mtx44_Inverse_GaussJordan(GabyouReturnMatrix *, const GabyouReturnMatrix *);
#ifdef __MWERKS__
void Mtx44_TransformVec3(GabyouReturnVec *, const GabyouReturnMatrix *, GabyouReturnVec);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void Mtx44_TransformVec3(GabyouReturnVec *, const GabyouReturnMatrix *, GabyouReturnVec *);
static inline void Mtx44_TransformVec3_ByValue(GabyouReturnVec *a0, const GabyouReturnMatrix *a1, GabyouReturnVec a2) { Mtx44_TransformVec3(a0, a1, &a2); }
#define Mtx44_TransformVec3 Mtx44_TransformVec3_ByValue
#endif
float Vec3_Magnitude_Wrapper(const GabyouReturnVec *);
void Vec3_Scale(GabyouReturnVec *, const GabyouReturnVec *, float);
void GetSpawnPosition(GabyouReturnVec *, float, float, float);
int KartCharacterParam_GetIdentityIndex(void *);
float KartFxParam_GetConst1p5(void *);
void Item_DecayVelocityScalar(GabyouReturnItem *, float);
float AngleStepTowards_Shortest(float, float, float);
float Vec3_PitchTo(const GabyouReturnVec *, const GabyouReturnVec *);
float BuildOrientationFromYaw(float);
unsigned char FinalLapCoinJump_CheckActiveForObject(void *);
extern const GabyouReturnTable GabyouItem_ReturnToHandTick_rodata_8032FF10;
extern const float lbl_806D62C0, lbl_806D62C4, lbl_806D62F0;
extern const float lbl_806D62F8, lbl_806D62FC, lbl_806D630C;

void GabyouItem_ReturnToHandTick(GabyouReturnItem *item, GabyouReturnContext *context)
{
    GabyouReturnMatrix world;
    GabyouReturnMatrix inverse;
    GabyouReturnTable radius;
    GabyouReturnVec hand;
    float yaw;
    Mtx_TransposeToMtx44(&world, KartDriver_GetJointByIdx(context->kart, 15));
    Mtx44_GetTranslation_ColMajor(&hand, &world);
    switch (item->phase) {
    case 0: {
        yaw = Vec3_ToYaw(&item->velocity);
        for (;;) {
            if (FAbs_FloatAsDouble(Vec3_HorizontalYawTo(&item->position, &hand) - yaw) < lbl_806D62F8)
                break;
            Vec3_Subtract_DestFirst(&item->position, &item->position, &item->velocity);
        }
        Mtx44_Inverse_GaussJordan(&inverse, &world);
        Mtx44_TransformVec3(&context->localPosition, &inverse, item->position);
        if (context->localPosition.y < 0.0f)
            context->localPosition.y = 0.0f;
        float reciprocal = lbl_806D62C4 / Vec3_Magnitude_Wrapper(&context->localPosition);
        Vec3_Scale(&context->localPosition, &context->localPosition, lbl_806D630C * reciprocal);
        GetSpawnPosition(&item->velocity, lbl_806D62C0, lbl_806D62C0, lbl_806D62C0);
        context->timer = 30;
        item->flag3C = 0;
        ++item->phase;
        break;
    }
    case 1: break;
    }
    radius = GabyouItem_ReturnToHandTick_rodata_8032FF10;
    Vec3_Scale(&context->localPosition, &context->localPosition,
        (lbl_806D62C4 / Vec3_Magnitude_Wrapper(&context->localPosition)) *
        radius.value[KartCharacterParam_GetIdentityIndex(context->kart)]);
    if (context->timer == 0) {
        item->lifetime -= lbl_806D62F0;
        if (item->lifetime < lbl_806D62C0) {
            item->active = 0;
            item->state = 3;
            item->phase = 0;
            return;
        }
    }
    Item_DecayVelocityScalar(item, KartFxParam_GetConst1p5(context->kart));
    Mtx44_TransformVec3(&item->position, &world, context->localPosition);
    item->yaw = AngleStepTowards_Shortest(item->yaw,
        Vec3_HorizontalYawTo(&item->position, &hand), lbl_806D62FC);
    item->pitch = AngleStepTowards_Shortest(item->pitch,
        BuildOrientationFromYaw(lbl_806D62F8 + Vec3_PitchTo(&item->position, &hand)), lbl_806D62FC);
    if (FinalLapCoinJump_CheckActiveForObject(context->kart)) item->active = 0;
    else item->active = 1;
}
}
