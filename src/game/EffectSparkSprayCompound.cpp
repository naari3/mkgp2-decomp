/* Narrow target-observed local views; no canonical Ghidra type lookup performed. */
struct SprayVec3 { float x, y, z; };
struct SprayEffect;
struct SprayGroup {
    unsigned char pad00[0x10];
    SprayEffect *children[8];
    unsigned char pad30[0x84];
    unsigned int timers[4];
    signed char variant;
};
struct SprayEffect {
    unsigned char pad00[0x10];
    int kind;
    unsigned char pad14[0x78];
    SprayVec3 position;
    unsigned char pad98[0x1C];
    signed char state;
    unsigned char padB5[0x14];
    signed char cleanup;
    unsigned char padCA[2];
    SprayGroup group;
};
extern "C" {
void DrawEffect_Free(SprayEffect *);
SprayEffect *DrawEffect_SpawnDirect(void (*)(SprayEffect *));
void Effect_StarBurst_Update(SprayEffect *);
void Effect_SparkPlain_Update(SprayEffect *);
void Vec3_Copy(SprayVec3 *, const SprayVec3 *);

static inline void ReleaseSprayChildren(SprayEffect *effect, SprayGroup *group) {
    int index;
    for (index = 0; index < 8; ++index) {
        DrawEffect_Free(group->children[index]);
        group->children[index] = 0;
    }
    DrawEffect_Free(effect);
}

void Effect_SparkSprayCompound_Update(SprayEffect *effect) {
    int freeIndex;
    SprayGroup *group = &effect->group;
    switch (effect->state) {
    case 0:
        group->timers[0] = 0;
        ++effect->state;
        break;
    case 1: break;
    }
    for (int i = 0; i < 8; ++i) {
        if (group->children[i] && group->children[i]->cleanup) {
            DrawEffect_Free(group->children[i]);
            group->children[i] = 0;
        }
    }
    if (group->timers[0] == 0) {
        for (freeIndex = 0; freeIndex < 8; ++freeIndex) {
            if (group->children[freeIndex] == 0) {
                switch (effect->kind) {
                case 0: group->children[freeIndex] = DrawEffect_SpawnDirect(Effect_StarBurst_Update); break;
                case 1: group->children[freeIndex] = DrawEffect_SpawnDirect(Effect_SparkPlain_Update); break;
                }
                if (group->children[freeIndex]) {
                    Vec3_Copy(&group->children[freeIndex]->position, &effect->position);
                    group->children[freeIndex]->group.variant = group->variant;
                }
                switch (effect->kind) {
                case 0: group->timers[0] = 15; break;
                case 1: group->timers[0] = 10; break;
                }
                break;
            }
        }
    }
    if (effect->cleanup) {
        ReleaseSprayChildren(effect, group);
    } else {
        if (group->timers[0]) --group->timers[0];
        if (group->timers[1]) --group->timers[1];
        if (group->timers[2]) --group->timers[2];
        if (group->timers[3]) --group->timers[3];
    }
}
}
