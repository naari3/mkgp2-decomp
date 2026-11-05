/* Advance all 15 item-box debris particles; deactivate the burst once every
 * particle has expired. Returns nonzero when the burst is (now) inactive. */
typedef struct DebrisParticle {
    float pos[3];   /* 0x00 */
    float vel[3];   /* 0x0C */
    float fallVel;  /* 0x18 */
    float life;     /* 0x1C */
    float pad20;    /* 0x20 */
    float rotX;     /* 0x24 */
    float rotY;     /* 0x28 */
} DebrisParticle;

typedef struct DebrisBurst {
    unsigned char active;          /* 0x00 */
    unsigned char pad01[0x3];
    DebrisParticle particles[15];  /* 0x04 */
} DebrisBurst;

typedef struct clItemBoxResponder {
    DebrisBurst *debris;           /* 0x00 */
} clItemBoxResponder;

static inline unsigned char DebrisParticle_Tick(DebrisParticle *p)
{
    p->life -= 0.016666668f;
    if (p->life < 0.0f) {
        return 0;
    }
    p->fallVel -= 0.11f;
    if (p->fallVel < -0.75f) {
        p->fallVel = -0.75f;
    }
    p->vel[1] += p->fallVel;
    p->pos[0] += p->vel[0];
    p->pos[1] += p->vel[1];
    p->pos[2] += p->vel[2];
    p->vel[0] *= 0.999f;
    p->vel[1] *= 0.999f;
    p->vel[2] *= 0.999f;
    p->rotX += 0.10471976f;
    p->rotY += 0.10471976f;
    return 1;
}

static inline unsigned char DebrisBurst_Tick(DebrisBurst *self)
{
    int alive;
    int i;

    if (self->active == 0) {
        return 0;
    }
    alive = 0;
    for (i = 0; i < 15; i++) {
        if (DebrisParticle_Tick(&self->particles[i]) == 1) {
            alive++;
        }
    }
    if (alive <= 0) {
        self->active = 0;
        return 0;
    }
    return 1;
}

unsigned char clItemBoxResponder_TickDebris(clItemBoxResponder *self)
{
    return DebrisBurst_Tick(self->debris) == 0;
}
