/* DrawEffect impact/ring effects TU (0x800CAE78..0x800CC130): dust ring,
 * timed smoke ring, spark tiers, hit flash and the item-hit spawners. One TU:
 * DrawEffect_ItemHitBurst_Spawn reaches the tint table .data 0x8041A4D0
 * through one pooled base, which CW only does for objects its own TU defines. */
#include "game/DrawEffectAccess.h"

/* The ring/flash updaters save registers one by one; the item-hit spawners
 * below use stmw (TU built with -use_lmw_stmw on). */
#pragma use_lmw_stmw off

/* DrawEffect_KartDustRing_Update (0x800CAE78): coloured dust puff
 * (resource 0x6D) trailing a tracked item at a random offset. The colour
 * comes from the tier in +0x190; it grows and fades once the item stops
 * homing or its 5..10-frame timer runs out. */

extern const float lbl_806D56F8; /* 1.0 */
extern const float lbl_806D5700; /* 2.0 */
extern const float lbl_806D570C; /* -10.0 */
extern const float lbl_806D5710; /* 10.0 */
extern const float lbl_806D5714; /* -5.0 */
extern const float lbl_806D571C; /* 0.0 */
extern const float lbl_806D5720; /* 0.8 */
extern const float lbl_806D5724; /* 1.2 */
extern const float lbl_806D5728; /* 0.1 */
/* The three tiers share the TU's data-section base register. */
Vec DrawEffect_KartDustRing_Update_data_8041A4D0 = { 1.0f, 1.0f, 1.0f };
Vec DrawEffect_ItemHitOriented_Spawn_data_8041A4DC = { 1.0f, 1.0f, 0.9f };
Vec DrawEffect_ItemHitOriented_Spawn_data_8041A4E8 = { 0.65f, 0.55f, 0.25f };
extern int Rand_RangeInt(int lo, int hi);
extern int Item_AdvanceTrackedHomingState(void *item, Vec *offset, float k);

void DrawEffect_KartDustRing_Update(unsigned char *self)
{
    switch (STATE) {
    case 0:
        if (P(0xCC) == 0) {
            DrawEffect_Free(self);
            return;
        }
        VfxSlot_BindResourceEx(SLOT(self), 0x6D, 0);
        switch (S8(0x190)) {
        case 1:
            Vec3_Copy(V(0x30), &DrawEffect_KartDustRing_Update_data_8041A4D0);
            break;
        case 2:
            Vec3_Copy(V(0x30), &DrawEffect_ItemHitOriented_Spawn_data_8041A4DC);
            break;
        case 3:
            Vec3_Copy(V(0x30), &DrawEffect_ItemHitOriented_Spawn_data_8041A4E8);
            break;
        }
        S8(0x28) = 1;
        F(0x2C) = lbl_806D56F8;
        F(0x150) = lbl_806D5700 * Rand_RangeFloat(lbl_806D5720, lbl_806D5724);
        F(0x154) = lbl_806D56F8;
        F(0x120) = Rand_RangeFloat(lbl_806D570C, lbl_806D5710);
        F(0x124) = lbl_806D5714;
        F(0x128) = Rand_RangeFloat(lbl_806D570C, lbl_806D5710);
        U32(0x180) = Rand_RangeInt(5, 10);
        STATE++;
    case 1:
        break;
    }

    if (Item_AdvanceTrackedHomingState(P(0xCC), V(0x120), lbl_806D56F8) == 1 || U32(0x180) == 0) {
        F(0x154) += lbl_806D5728;
        F(0x2C) -= lbl_806D5728;
        if (F(0x2C) < lbl_806D571C) {
            S8(0x28) = 0;
            DrawEffect_Free(self);
            return;
        }
    }
    Vec3_Add_DestFirst(V(0x8C), V_(P(0xCC), 0xA0), V(0x120));
    F(0xB0) = F(0x150) * F(0x154);
    {
        Vec pos = *V(0x8C);
        VfxSlot_SetPositionFromVec(SLOT(self), &pos);
    }
    VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
    TICK_TIMERS();
}

/* DrawEffect_SmokeRingTimed_Update (0x800CB0C8): smoke ring (resource
 * 0x86) that waits 3 frames, then drifts with its velocity while growing;
 * the fade length (10/20/40 frames) and size depend on the tier in +0x190. */

extern const float lbl_806D56F8; /* 1.0 */
extern const float lbl_806D5700; /* 2.0 */
extern const float lbl_806D5710; /* 10.0 */
extern const float lbl_806D571C; /* 0.0 */
extern const float lbl_806D5720; /* 0.8 */
extern const float lbl_806D5724; /* 1.2 */
extern const float lbl_806D5728; /* 0.1 */
extern const float lbl_806D572C; /* 20.0 */
extern const float lbl_806D5730; /* 40.0 */
extern void VfxSlot_BindResource(void *slot, int res);

void DrawEffect_SmokeRingTimed_Update(unsigned char *self)
{
    switch (STATE) {
    case 0:
        switch (S8(0xB5)) {
        case 0:
            U32(0x180) = 3;
            S8(0xB5)++;
        case 1:
            if (U32(0x180) == 0) {
                STATE++;
            }
            break;
        }
        break;
    case 1:
        VfxSlot_BindResource(SLOT(self), 0x86);
        F(0x2C) = lbl_806D56F8;
        switch (S8(0x190)) {
        case 1:
            F(0x150) = Rand_RangeFloat(lbl_806D5720, lbl_806D5724);
            break;
        case 2:
            F(0x150) = Rand_RangeFloat(lbl_806D5720, lbl_806D5724);
            break;
        case 3:
            F(0x150) = lbl_806D5700 * Rand_RangeFloat(lbl_806D5720, lbl_806D5724);
            break;
        }
        F(0x154) = lbl_806D56F8;
        switch (S8(0x190)) {
        case 1:
            F(0x158) = lbl_806D5710;
            break;
        case 2:
            F(0x158) = lbl_806D572C;
            break;
        case 3:
            F(0x158) = lbl_806D5730;
            break;
        }
        STATE++;
    case 2:
        if (U32(0x180) == 0) {
            F(0x2C) -= lbl_806D56F8 / F(0x158);
            if (F(0x2C) < lbl_806D571C) {
                S8(0x28) = 0;
                DrawEffect_Free(self);
                return;
            }
        }
        F(0x154) += lbl_806D5728;
        F(0xB0) = F(0x150) * F(0x154);
        Vec3_Add_DestFirst(V(0x8C), V(0x8C), V(0xA4));
        {
            Vec pos = *V(0x8C);
            VfxSlot_SetPositionFromVec(SLOT(self), &pos);
        }
        VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
        break;
    }
    TICK_TIMERS();
}

/* DrawEffect_KartSparkTier_Update (0x800CB344): free-flying spark
 * (resource 0x13/0x14, or 0x84/0x85 for kind 4) that sinks and drifts with
 * its velocity; size and lifetime (5/15/35 frames) follow the tier in
 * +0x190, kind 5 is half size. */

extern const float lbl_806D56F8; /* 1.0 */
extern const float lbl_806D56FC; /* 0.4 */
extern const float lbl_806D5704; /* 0.5 */
extern const float lbl_806D5708; /* 1.5 */
extern const float lbl_806D5718; /* 0.2 */
extern const float lbl_806D571C; /* 0.0 */
extern const float lbl_806D5720; /* 0.8 */
extern const float lbl_806D5724; /* 1.2 */
extern const float lbl_806D5734; /* 3.0 */
extern const float lbl_806D5738; /* 0.09 */
extern int Rand_RangeIntMax(int max);

void DrawEffect_KartSparkTier_Update(unsigned char *self)
{
    switch (STATE) {
    case 0:
        if ((int)U8(0x191) == 4) {
            if (Rand_RangeIntMax(16) % 2) {
                VfxSlot_BindResourceEx(SLOT(self), 0x84, 0);
            } else {
                VfxSlot_BindResourceEx(SLOT(self), 0x85, 0);
            }
        } else if (Rand_RangeIntMax(16) % 4) {
            VfxSlot_BindResourceEx(SLOT(self), 0x14, 0);
        } else {
            VfxSlot_BindResourceEx(SLOT(self), 0x13, 0);
        }
        if ((int)U8(0x191) == 4) {
            F(0x2C) = lbl_806D56F8;
        } else {
            F(0x2C) = lbl_806D56FC;
        }
        switch (S8(0x190)) {
        case 1:
            F(0x150) = lbl_806D5708 * Rand_RangeFloat(lbl_806D5720, lbl_806D5724);
            break;
        case 2:
            F(0x150) = lbl_806D5708 * Rand_RangeFloat(lbl_806D5720, lbl_806D5724);
            break;
        case 3:
            F(0x150) = lbl_806D5734 * Rand_RangeFloat(lbl_806D5720, lbl_806D5724);
            break;
        }
        if ((int)U8(0x191) == 5) {
            F(0x150) *= lbl_806D5704;
        }
        F(0x154) = lbl_806D56F8;
        switch (S8(0x190)) {
        case 1:
            U32(0x180) = 5;
            break;
        case 2:
            U32(0x180) = 15;
            break;
        case 3:
            U32(0x180) = 35;
            break;
        }
        STATE++;
    case 1:
        break;
    }

    F(0xA8) -= lbl_806D5738;
    if (U32(0x180) == 0) {
        F(0x154) -= lbl_806D5718;
        if (F(0x154) < lbl_806D571C) {
            DrawEffect_Free(self);
            return;
        }
    }
    Vec3_Add_DestFirst(V(0x8C), V(0x8C), V(0xA4));
    F(0xB0) = F(0x150) * F(0x154);
    {
        Vec pos = *V(0x8C);
        VfxSlot_SetPositionFromVec(SLOT(self), &pos);
    }
    VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
    TICK_TIMERS();
}


extern const float lbl_806D56F8; /* 1.0 */
extern const float lbl_806D5700; /* 2.0 */
extern const float lbl_806D5708; /* 1.5 */
extern const float lbl_806D571C; /* 0.0 */
extern const float lbl_806D5728; /* 0.1 */
extern const float lbl_806D5734; /* 3.0 */
extern const float lbl_806D573C; /* 4.5 */

void DrawEffect_HitFlash_Update(unsigned char *self)
{
    Vec pos;
    Vec rot;

    switch (STATE) {
    case 0:
        VfxSlot_BindResourceEx(SLOT(self), 0x1B, 0);
        switch (S8(0x190)) {
        case 1:
            F(0x154) = lbl_806D5708;
            break;
        case 2:
            F(0x154) = lbl_806D5734;
            break;
        case 3:
            F(0x154) = lbl_806D573C;
            break;
        }
        pos = *V(0x8C);
        VfxSlot_SetPositionFromVec(SLOT(self), &pos);
        rot = *V(0x98);
        VfxSlot_SetRotationXYZFromVec(SLOT(self), &rot);
        F(0x150) = lbl_806D571C;
        STATE++;
        break;
    case 1:
        break;
    }
    F(0x150) += 0.1f;
    if (1.0f < F(0x150)) {
        DrawEffect_Free(self);
        return;
    }
    F(0x2C) = 1.0f - F(0x150);
    F(0xB0) = lbl_806D5700 * (F(0x150) * F(0x154));
    VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
}


#pragma use_lmw_stmw reset
extern const float lbl_806D56F8; /* 1.0 */
extern const float lbl_806D5708; /* 1.5 */
extern const float lbl_806D5740; /* 500.0 */

extern unsigned char lbl_805DF3D0[];
extern float Item_ProbeForwardGroundPitch(Vec pos, float a, float b, float c);
extern float Item_ProbeLateralGroundPitch(Vec pos, float a, float b, float c);
extern float fn_800D3184(const Vec *a, const Vec *b);
extern signed char ItemObject_GetGroundTypeAt(Vec pos, float *outGroundY, int mode);
extern void DrawEffect_KartDustRing_Update(unsigned char *self);
extern void DrawEffect_KartSpark_Update(unsigned char *self);

void DrawEffect_ItemHitFx_Spawn(const Vec *at, int owner)
{
    Vec pos;
    unsigned char *e;
    signed char ground;
    int i;

    if (lbl_806D5740 < fn_800D3184((Vec *)(lbl_805DF3D0 + 0x80), at)) {
        return;
    }
    Vec3_Copy(&pos, at);
    ground = ItemObject_GetGroundTypeAt(pos, &pos.y, 0);
    if (ground == 0) {
        return;
    }
    switch (ground) {
    case 1:
    case 2:
    case 3:
        e = DrawEffect_SpawnDirect(DrawEffect_KartDustRing_Update);
        if (e != 0) {
            Vec3_Copy((Vec *)(e + 0x8C), &pos);
            ((Vec *)(e + 0x8C))->y += lbl_806D5708;
            *(signed char *)(e + 0x190) = ground;
            *(int *)(e + 0xCC) = owner;
        }
        break;
    case 4:
    case 5:
        for (i = 0; i < 4; i++) {
            unsigned char *s = DrawEffect_SpawnDirect(DrawEffect_KartSpark_Update);
            if (s != 0) {
                Vec3_Copy((Vec *)(s + 0x8C), &pos);
                ((Vec *)(s + 0x8C))->y += lbl_806D56F8;
                *(int *)(s + 0xCC) = owner;
                *(signed char *)(s + 0x190) = ground;
            }
        }
        break;
    }
}

/* DrawEffect_ItemHitOriented_Spawn (0x800CB8C0): spawn the ground-type
 * specific impact effect (debris, smoke ring or sparks) at a hit position
 * near the camera. */


extern void Matrix4_Identity(float m[4][4]);
extern void Matrix4_PreMultiplyRotX(float dst[4][4], float src[4][4], float a);
extern void Matrix4_PreMultiplyRotZ(float dst[4][4], float src[4][4], float a);
extern unsigned char *DrawEffect_SpawnDirect(void (*callback)(unsigned char *));
extern void Effect_ExplosionPiece_Update(unsigned char *e);
extern void DrawEffect_SmokeRingTimed_Update(unsigned char *e);
extern void DrawEffect_KartSparkTier_Update(unsigned char *e);
extern float Rand_RangeFloat(float lo, float hi);

void DrawEffect_ItemHitOriented_Spawn(Vec *pos, Vec *vel, signed char kind)
{
    float m[4][4];
    Vec p;
    signed char ground;
    float pitch;
    float roll;
    unsigned char *e;
    int type;

    if (500.0f < fn_800D3184((Vec *)(lbl_805DF3D0 + 0x80), pos)) {
        return;
    }
    Vec3_Copy(&p, pos);
    ground = ItemObject_GetGroundTypeAt(p, &p.y, 0);
    if (ground == 0) {
        return;
    }
    pitch = Item_ProbeForwardGroundPitch(p, 0.0f, 10.0f, 0.0f);
    roll = Item_ProbeLateralGroundPitch(p, 0.0f, 10.0f, 0.0f);
    Matrix4_Identity(m);
    Matrix4_PreMultiplyRotX(m, m, pitch);
    Matrix4_PreMultiplyRotZ(m, m, roll);
    Vec3_Magnitude_Wrapper(vel);
    type = ground;
    switch (type) {
    case 1:
        break;
    case 2:
    case 3:
        e = DrawEffect_SpawnDirect(Effect_ExplosionPiece_Update);
        if (e != 0) {
            Vec3_Copy((Vec *)(e + 0x8C), &p);
            *(float *)(e + 0x90) += 1.5f;
            GetSpawnPosition((Vec *)(e + 0xA4), 0.0f, 0.0f, 0.0f);
            switch (kind) {
            case 1:
                e[0x191] = 1;
                break;
            case 2:
                e[0x191] = 1;
                break;
            case 3:
                e[0x191] = 2;
                break;
            }
            switch (type) {
            case 2:
                e[0x193] = 2;
                break;
            case 3:
                e[0x193] = 0;
                break;
            }
            switch (type) {
            case 2:
                Vec3_Copy((Vec *)(e + 0x120), &DrawEffect_ItemHitOriented_Spawn_data_8041A4DC);
                break;
            case 3:
                Vec3_Copy((Vec *)(e + 0x120), &DrawEffect_ItemHitOriented_Spawn_data_8041A4E8);
                break;
            }
        }
        break;
    case 4:
        e = DrawEffect_SpawnDirect(DrawEffect_SmokeRingTimed_Update);
        if (e != 0) {
            Vec3_Copy((Vec *)(e + 0x8C), &p);
            *(float *)(e + 0x90) += 1.0f;
            e[0x190] = kind;
        }
        break;
    case 5:
        e = DrawEffect_SpawnDirect(DrawEffect_KartSparkTier_Update);
        if (e != 0) {
            Vec3_Copy((Vec *)(e + 0x8C), &p);
            Vec3_Copy((Vec *)(e + 0xA4), vel);
            Vec3_Scale((Vec *)(e + 0xA4), (Vec *)(e + 0xA4), 0.9f);
            Vec2_RotateY((Vec *)(e + 0xA4), (Vec *)(e + 0xA4), 0.017453289f * Rand_RangeFloat(-10.0f, 10.0f));
            *(float *)(e + 0xA8) += 1.5f;
            e[0x190] = kind;
            e[0x191] = ground;
        }
        break;
    }
}

/* DrawEffect_ItemHitBurst_Spawn (0x800CBBD4): debris burst when an item
 * hits the ground near the camera. Ground types 1..3 throw explosion
 * pieces tinted per ground type; types 4..5 throw spark tiers, and type 4
 * also leaves a timed smoke ring. `strength` (1..3) sets the piece count
 * and the angular spread. Pieces fan out on the local ground slope. */

extern float FAbs_FloatAsDouble(float x);
extern void Mtx44_TransformVec3(Vec *out, float m[4][4], Vec *in);

extern const float lbl_806D5740; /* 500.0 */
extern const float lbl_806D5710; /* 10.0 */
extern const float lbl_806D5708; /* 1.5 */
extern const float lbl_806D56F8; /* 1.0 */
extern const float lbl_806D5750; /* -180.0 */
extern const float lbl_806D5754; /* 180.0 */
extern const float lbl_806D5720; /* 0.8 */
extern const float lbl_806D5724; /* 1.2 */
extern const float lbl_806D5758; /* -15.0 */
extern const float lbl_806D575C; /* 15.0 */

extern const float lbl_806D5748; /* degrees to radians */
extern const float lbl_806D5704; /* 0.5 */

extern const float lbl_806D5760; /* pi */
extern const float lbl_806D5764; /* pi / 2 */
extern const float lbl_806D5768; /* pi / 4 */
extern const float lbl_806D576C; /* -pi / 4 */

extern const float lbl_806D5734; /* 3.0 */
extern const float lbl_806D574C; /* 5.0 */

static inline void TransformVelocity(Vec *v, float m[4][4])
{
    Vec local = *v;
    Mtx44_TransformVec3(v, m, &local);
}

void DrawEffect_ItemHitBurst_Spawn(Vec *pos, Vec *vel, signed char strength)
{
    float m[4][4];
    Vec p;
    unsigned char *self;
    int count;
    int i;
    signed char ground;
    float spread2;
    float spread;
    float pitch;
    float roll;
    float speed;
    float yaw2;
    float yaw;

    if (lbl_806D5740 < fn_800D3184((Vec *)(lbl_805DF3D0 + 0x80), pos)) {
        return;
    }
    Vec3_Copy(&p, pos);
    ground = ItemObject_GetGroundTypeAt(p, &p.y, 0);
    if (ground == 0) {
        return;
    }
    pitch = Item_ProbeForwardGroundPitch(p, 0.0f, lbl_806D5710, 0.0f);
    roll = Item_ProbeLateralGroundPitch(p, 0.0f, lbl_806D5710, 0.0f);
    Matrix4_Identity(m);
    Matrix4_PreMultiplyRotX(m, m, pitch);
    Matrix4_PreMultiplyRotZ(m, m, roll);
    speed = FAbs_FloatAsDouble(vel->y);
    if (speed < lbl_806D5734) {
        speed = lbl_806D5734;
    }
    if (lbl_806D574C < speed) {
        speed = lbl_806D574C;
    }
    switch (ground) {
    case 1:
    case 2:
    case 3: {
        switch (strength) {
        case 1:
            count = 2;
            break;
        case 2:
            count = 4;
            break;
        case 3:
            count = 8;
            break;
        }
        yaw = lbl_806D5748 * Rand_RangeFloat(lbl_806D5750, lbl_806D5754);
        spread = lbl_806D5704 * speed;
        for (i = 0; i < count; i++) {
            self = DrawEffect_SpawnDirect(Effect_ExplosionPiece_Update);
            if (self != 0) {
                Vec3_Copy(V(0x8C), &p);
                F(0x90) += lbl_806D5708;
                GetSpawnPosition(V(0xA4), 0.0f, 0.0f,
                                 spread * Rand_RangeFloat(lbl_806D5720, lbl_806D5724));
                Vec2_RotateY(V(0xA4), V(0xA4),
                             BuildOrientationFromYaw(lbl_806D5748 * Rand_RangeFloat(lbl_806D5758, lbl_806D575C) + yaw));
                TransformVelocity(V(0xA4), m);
                switch (strength) {
                case 1:
                    S8(0x191) = 1;
                    break;
                case 2:
                    S8(0x191) = 1;
                    break;
                case 3:
                    S8(0x191) = 2;
                    break;
                }
                S8(0x193) = 2;
                switch (ground) {
                case 1:
                    Vec3_Copy(V(0x120), &DrawEffect_KartDustRing_Update_data_8041A4D0);
                    break;
                case 2:
                    Vec3_Copy(V(0x120), &DrawEffect_ItemHitOriented_Spawn_data_8041A4DC);
                    break;
                case 3:
                    Vec3_Copy(V(0x120), &DrawEffect_ItemHitOriented_Spawn_data_8041A4E8);
                    break;
                }
            }
            switch (strength) {
            case 1:
                yaw = BuildOrientationFromYaw(lbl_806D5760 + yaw);
                break;
            case 2:
                yaw = BuildOrientationFromYaw(lbl_806D5764 + yaw);
                break;
            case 3:
                yaw = BuildOrientationFromYaw(lbl_806D5768 + yaw);
                break;
            }
        }
        break;
    }
    case 4:
    case 5: {
        switch (strength) {
        case 1:
            count = 4;
            break;
        case 2:
            count = 8;
            break;
        case 3:
            count = 8;
            break;
        }
        yaw2 = lbl_806D5748 * Rand_RangeFloat(lbl_806D5750, lbl_806D5754);
        spread2 = lbl_806D5704 * speed;
        for (i = 0; i < count; i++) {
            self = DrawEffect_SpawnDirect(DrawEffect_KartSparkTier_Update);
            if (self != 0) {
                Vec3_Copy(V(0x8C), &p);
                GetSpawnPosition(V(0xA4), 0.0f, 0.0f,
                                 spread2 * Rand_RangeFloat(lbl_806D5720, lbl_806D5724));
                Vec2_RotateX(V(0xA4), V(0xA4), lbl_806D576C);
                Vec2_RotateY(V(0xA4), V(0xA4),
                             BuildOrientationFromYaw(lbl_806D5748 * Rand_RangeFloat(lbl_806D5758, lbl_806D575C) + yaw2));
                TransformVelocity(V(0xA4), m);
                S8(0x190) = strength;
                S8(0x191) = ground;
            }
            switch (strength) {
            case 1:
                yaw2 = BuildOrientationFromYaw(lbl_806D5764 + yaw2);
                break;
            case 2:
                yaw2 = BuildOrientationFromYaw(lbl_806D5768 + yaw2);
                break;
            case 3:
                yaw2 = BuildOrientationFromYaw(lbl_806D5768 + yaw2);
                break;
            }
        }
        if (ground == 4) {
            self = DrawEffect_SpawnDirect(DrawEffect_SmokeRingTimed_Update);
            if (self != 0) {
                Vec3_Copy(V(0x8C), &p);
                F(0x90) += lbl_806D56F8;
                S8(0x190) = strength;
            }
        }
        break;
    }
    }
}
