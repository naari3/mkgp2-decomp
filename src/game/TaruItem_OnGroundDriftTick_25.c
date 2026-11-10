/* TaruItem_OnGroundDriftTick_25 (0x800E9E94): the barrel rolling loose on
 * the ground.  After an optional linger time (none for kind 5) it fades out
 * and hands over to state 3.  Otherwise it falls, accelerates (class-
 * dependent), spins, steers its yaw towards the velocity, bounces off walls
 * and, on landing, tilts with the ground and veers down steep slopes. */
#include "game/types/Vec.h"

typedef struct TaruItem {
    unsigned char pad000[0x28];
    signed char visible;    /* 0x028 */
    unsigned char pad029[0x3];
    float alpha;            /* 0x02C */
    unsigned char pad030[0xA0 - 0x30];
    Vec pos;                /* 0x0A0 */
    float spin;             /* 0x0AC */
    float yaw;              /* 0x0B0 */
    float pitch;            /* 0x0B4 */
    Vec vel;                /* 0x0B8 */
    unsigned char pad0C4[0xC8 - 0xC4];
    signed char state;      /* 0x0C8 */
    signed char subState;   /* 0x0C9 */
    unsigned char pad0CA;
    signed char hitType;    /* 0x0CB */
} TaruItem;

typedef struct TaruTimers {
    unsigned int pad00;
    unsigned int linger; /* 0x04 */
} TaruTimers;

extern int g_ccClass;

extern void Item_AccelClampVelocity(TaruItem *self, float accel, float maxv);
extern float BuildOrientationFromYaw(float yaw);
extern float Vec3_ToYaw(const Vec *v);
extern float AngleStepTowards_Shortest(float cur, float target, float step);
extern void Item_DecayVelocityScalar(TaruItem *self, float k);
extern int Item_CheckWallCollision(TaruItem *self, Vec *normal, int mode);
#ifdef __MWERKS__
extern void Item_BounceOffWall(TaruItem *self, Vec normal, int a, int b, float restitution, float c);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void Item_BounceOffWall(TaruItem *, Vec *, int, int, float, float);
static inline void Item_BounceOffWall_ByValue(TaruItem *self, Vec normal, int a, int b, float restitution, float c) { Item_BounceOffWall(self, &normal, a, b, restitution, c); }
#define Item_BounceOffWall Item_BounceOffWall_ByValue
#endif
extern int Item_AdvanceFallingDrop(TaruItem *self, int *landed, float *groundY, float gravity);
#ifdef __MWERKS__
extern float Item_ProbeLateralGroundPitch(Vec pos, float yaw, float a, float b);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern float Item_ProbeLateralGroundPitch(Vec *, float, float, float);
static inline float Item_ProbeLateralGroundPitch_ByValue(Vec pos, float yaw, float a, float b) { return Item_ProbeLateralGroundPitch(&pos, yaw, a, b); }
#define Item_ProbeLateralGroundPitch Item_ProbeLateralGroundPitch_ByValue
#endif
extern float FAbs_FloatAsDouble(float x);
extern void Vec2_RotateY(Vec *out, const Vec *in, float a);

#pragma exceptions on
void TaruItem_OnGroundDriftTick_25(TaruItem *self, TaruTimers *timers)
{
    Vec normal;
    int landed;
    float groundY;

    switch (self->subState) {
    case 0:
        if (self->hitType != 5) {
            timers->linger = 10;
        } else {
            timers->linger = 0;
        }
        self->subState++;
    case 1:
        break;
    }

    if (timers->linger == 0) {
        self->alpha -= 0.05f;
        if (self->alpha < 0.0f) {
            self->visible = 0;
            self->state = 3;
            self->subState = 0;
            return;
        }
    }

    self->vel.y += -0.2f;
    Item_AccelClampVelocity(self, g_ccClass == 0 ? 12.0f : 17.0f, g_ccClass == 0 ? 1.0f : 2.0f);
    self->spin = BuildOrientationFromYaw(0.2617994f + self->spin);
    self->yaw = AngleStepTowards_Shortest(self->yaw, Vec3_ToYaw(&self->vel), 0.17453289f);
    Item_DecayVelocityScalar(self, 5.0f);
    if (Item_CheckWallCollision(self, &normal, 0)) {
        Item_BounceOffWall(self, normal, 0, 0, 0.8f, 0.0f);
    }
    if (Item_AdvanceFallingDrop(self, &landed, &groundY, 1.6f) && landed != 0) {
        self->vel.y *= -0.2f;
        self->pitch = Item_ProbeLateralGroundPitch(self->pos, self->yaw, 5.0f, self->pos.y - groundY);
        if (0.2617994f < FAbs_FloatAsDouble(self->pitch)) {
            if (0.0f < self->pitch) {
                Vec2_RotateY(&self->vel, &self->vel, 0.1f * -(self->pitch - 0.2617994f));
            } else {
                Vec2_RotateY(&self->vel, &self->vel, 0.1f * -(0.2617994f + self->pitch));
            }
        }
    }
}
#pragma exceptions reset
