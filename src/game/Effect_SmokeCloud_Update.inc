/* Effect_SmokeCloud_Update @ 0x800C39F8 (size 0x2D0): frees finished
 * sub-puffs, spawns a new one every ten frames, and ticks the timers. */

extern void DrawEffect_Free(void *e);
extern SmokePuff *DrawEffect_SpawnDirect(void *init);
extern void GetSpawnPosition(void *out, float a, float b, float c);
extern float Rand_RangeFloat(float lo, float hi);
extern void VfxSlot_BindResourceEx(void *slot, int id, int arg);
extern void VfxSlot_SetRotationZ(void *slot, float rot);
extern void fn_800AF4F8();

extern const float lbl_806D53E8;
extern const float lbl_806D53EC;
extern const float lbl_806D53F0;
extern const float lbl_806D53F4;
extern const float lbl_806D540C;
extern const float lbl_806D5424;
extern const float lbl_806D5428;
extern const float lbl_806D5434;
extern const float lbl_806D5454;
extern const float lbl_806D5470;
extern const float lbl_806D5474;
extern const float lbl_806D5478;

typedef struct SmokeSpawnSet {
    unsigned char pad00[0x10];
    SmokePuff *puffs[8];        /* 0x10 */
    unsigned char pad30[0xB4 - 0x30];
    unsigned int timers[4];     /* 0xB4 */
} SmokeSpawnSet;

#define SMOKE_STATE(e) (*(signed char *)((char *)(e) + 0xB4))
#define SMOKE_ROT(p) (*(float *)((char *)(p) + 0xA0))

#pragma exceptions on
#pragma use_lmw_stmw on
void Effect_SmokeCloud_Update(SmokePuff *e)
{
    SmokeSpawnSet *set = (SmokeSpawnSet *)&e->set;
    SmokePuff *p;
    int i;

    switch (SMOKE_STATE(e)) {
    case 0:
        set->timers[0] = 0;
        SMOKE_STATE(e)++;
        break;
    case 1:
        break;
    }
    for (i = 0; i < 8; i++) {
        p = set->puffs[i];
        if (p != 0 && p->finished) {
            DrawEffect_Free(p);
            set->puffs[i] = 0;
        }
    }
    if (set->timers[0] == 0) {
        for (i = 0; i < 8; i++) {
            if (set->puffs[i] == 0) {
                set->puffs[i] = DrawEffect_SpawnDirect(fn_800AF4F8);
                p = set->puffs[i];
                if (p != 0) {
                    VfxSlot_BindResourceEx(p->vfx, 0x6D, 0);
                    Vec3_Copy(&p->pos, &e->pos);
                    SMOKE_ROT(p) = lbl_806D53EC * Rand_RangeFloat(lbl_806D53F0, lbl_806D53F4);
                    VfxSlot_SetRotationZ(p->vfx, SMOKE_ROT(p));
                    p->scale = Rand_RangeFloat(lbl_806D5428, lbl_806D53E8);
                    Vec3_Scale(&p->vel, &e->vel, lbl_806D5470);
                    p->vel.x = lbl_806D5474 * Rand_RangeFloat(lbl_806D5434, lbl_806D5424) + p->vel.x;
                    p->vel.y = lbl_806D5474 * Rand_RangeFloat(lbl_806D5434, lbl_806D5424) + p->vel.y;
                    p->vel.z = lbl_806D5474 * Rand_RangeFloat(lbl_806D5434, lbl_806D5424) + p->vel.z;
                    p->visible = 0;
                    p->alpha = lbl_806D5424;
                    GetSpawnPosition((char *)p + 0x30, lbl_806D5424, lbl_806D5478, lbl_806D540C);
                    p->offset.x = lbl_806D540C * Rand_RangeFloat(lbl_806D5434, lbl_806D5424);
                    p->offset.y = lbl_806D540C * Rand_RangeFloat(lbl_806D5434, lbl_806D5424);
                    p->offset.z = lbl_806D540C * Rand_RangeFloat(lbl_806D5434, lbl_806D5424);
                    p->leash = lbl_806D5454;
                    p->timers[0] = 10;
                    p->active = 1;
                    p->life = lbl_806D5424;
                }
                set->timers[0] = 10;
                break;
            }
        }
    }
    if (e->finished) {
        for (i = 0; i < 8; i++) {
            DrawEffect_Free(set->puffs[i]);
            set->puffs[i] = 0;
        }
        DrawEffect_Free(e);
    } else {
        if (set->timers[0]) {
            set->timers[0]--;
        }
        if (set->timers[1]) {
            set->timers[1]--;
        }
        if (set->timers[2]) {
            set->timers[2]--;
        }
        if (set->timers[3]) {
            set->timers[3]--;
        }
    }
}
#pragma use_lmw_stmw reset
#pragma exceptions reset
