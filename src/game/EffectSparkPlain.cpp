/* Target-observed local view; no live Ghidra type lookup was performed. */
struct SparkPlainVec { float x, y, z; };
struct SparkPlainEffect {
    char pad00[0x14];
    char slot[0x14];
    unsigned char visible;
    char pad29[0x87];
    float scale;
    signed char state;
    char padB5[0x14];
    unsigned char cleanup;
    char padCA[0x56];
    SparkPlainVec velocity;
    char pad12C[0x24];
    float lifetime, angle, phase;
};
extern "C" {
extern const float lbl_806D54A8, lbl_806D54AC, lbl_806D54E8;
extern const float lbl_806D54F8, lbl_806D54FC, lbl_806D552C;
extern const float lbl_806D5524, lbl_806D5528, lbl_806D54B8, lbl_806D54C0, lbl_806D5510;
void VfxSlot_BindResourceEx(void*, int, int);
float Rand_RangeFloat(float, float);
int Rand_RangeIntMax(int);
void GetSpawnPosition(SparkPlainVec*, float, float, float);
float BuildOrientationFromYaw(float);
double sin(double);

void Effect_SparkPlain_Update(SparkPlainEffect* effect) {
    switch (effect->state) {
    case 0:
        VfxSlot_BindResourceEx(effect->slot, 0x7f, 0);
        effect->visible = 0;
        effect->lifetime = Rand_RangeFloat(lbl_806D54A8, lbl_806D54AC);
        effect->angle = lbl_806D54E8;
        GetSpawnPosition(&effect->velocity,
            Rand_RangeFloat(lbl_806D54F8, lbl_806D54FC),
            Rand_RangeFloat(lbl_806D54F8, lbl_806D54FC),
            Rand_RangeFloat(lbl_806D54F8, lbl_806D54FC));
        if (Rand_RangeIntMax(15) % 2) effect->velocity.x *= lbl_806D552C;
        if (Rand_RangeIntMax(15) % 2) effect->velocity.y *= lbl_806D552C;
        if (Rand_RangeIntMax(15) % 2) effect->velocity.z *= lbl_806D552C;
        effect->phase = lbl_806D54E8;
        ++effect->state;
    case 1:
        effect->phase -= lbl_806D5524;
        effect->angle = BuildOrientationFromYaw(lbl_806D5528 + effect->angle);
        {
            float lifetime;
            float oscillation = (float)sin(effect->angle);
            oscillation = lbl_806D54B8 + oscillation;
            oscillation = oscillation * lbl_806D54C0;
            oscillation = oscillation * lbl_806D54C0 + lbl_806D54C0;
            lifetime = effect->lifetime;
            effect->scale = lifetime * oscillation;
        }
        effect->lifetime -= lbl_806D5510;
        if (effect->lifetime < lbl_806D54E8) {
            effect->visible = 0;
            effect->cleanup = 1;
            ++effect->state;
        }
        break;
    default:
        break;
    }
}
}
