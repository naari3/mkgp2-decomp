/* Target-observed field view; live Ghidra types were unavailable. */
typedef struct { float x, y, z; } StarVec;
typedef struct { int joints[3]; } StarJoints;
typedef struct {
    char pad00[0x14];
    char slotHead[8];
    unsigned char slotKind;
    char pad1D[11];
    unsigned char visible;
    char pad29[0x77];
    float rotation;
    char padA4[12];
    float scale;
    signed char state;
    unsigned char substate;
    char padB6[0x13];
    unsigned char cleanup;
    char padCA[0x56];
    StarVec velocity;
    char pad12C[0x24];
    float amplitude, phase, unusedPhase;
    char pad15C[0x34];
    signed char variant;
} StarEffect;
extern const StarJoints lbl_8032A7C0;
extern const float lbl_806D54F8, lbl_806D54FC, lbl_806D54E8, lbl_806D552C;
extern const float lbl_806D54C8, lbl_806D54CC, lbl_806D54C4, lbl_806D5530;
extern const float lbl_806D5534, lbl_806D54B8, lbl_806D5514;
void VfxSlot_BindResourceEx(void*, int, int);
void VfxSlot_ResolveJoint(void*, int);
int Rand_RangeIntMax(int);
float Rand_RangeFloat(float, float);
void GetSpawnPosition(StarVec*, float, float, float);
float BuildOrientationFromYaw(float);
double sin(double);
float FAbs_FloatAsDouble(float);
void Effect_StarBurst_Update(StarEffect* effect) {
    switch (effect->state) {
    default:
        return;
    case 0:
        if (!effect->variant) VfxSlot_BindResourceEx(effect->slotHead, 0x7f, 0);
        else VfxSlot_BindResourceEx(effect->slotHead, 3, 0);
        if (effect->slotKind == 3) {
            StarJoints joints = lbl_8032A7C0;
            VfxSlot_ResolveJoint(effect->slotHead, joints.joints[Rand_RangeIntMax(15) % 3]);
        }
        effect->visible = 0;
        effect->amplitude = lbl_806D54F8 * Rand_RangeFloat(lbl_806D54F8, lbl_806D54FC);
        effect->phase = lbl_806D54E8;
        GetSpawnPosition(&effect->velocity,
            Rand_RangeFloat(lbl_806D54F8, lbl_806D54FC),
            Rand_RangeFloat(lbl_806D54F8, lbl_806D54FC),
            Rand_RangeFloat(lbl_806D54F8, lbl_806D54FC));
        if (Rand_RangeIntMax(15) % 2) effect->velocity.x *= lbl_806D552C;
        if (Rand_RangeIntMax(15) % 2) effect->velocity.y *= lbl_806D552C;
        if (Rand_RangeIntMax(15) % 2) effect->velocity.z *= lbl_806D552C;
        effect->unusedPhase = lbl_806D54E8;
        effect->rotation = lbl_806D54C4 * Rand_RangeFloat(lbl_806D54C8, lbl_806D54CC);
        ++effect->state;
        effect->substate = 0;
    case 1:
        effect->rotation = BuildOrientationFromYaw(lbl_806D5530 + effect->rotation);
        effect->scale = effect->amplitude * (lbl_806D54B8 - FAbs_FloatAsDouble((float)sin(lbl_806D54C4 * (lbl_806D54CC * effect->phase + lbl_806D5534))));
        effect->phase += lbl_806D5514;
        if (lbl_806D54B8 < effect->phase) {
            effect->visible = 0;
            effect->cleanup = 1;
            ++effect->state;
        }
        break;
    }
}
