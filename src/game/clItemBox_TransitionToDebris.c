/* clItemBox_TransitionToDebris (0x8005EA94): the item box was hit.  Switch to
 * the debris step (state 2) and burst all 15 debris pieces out of the box:
 * each flies in a random direction (flipped to the hit's side), biased by
 * 1.5x the hit direction, with a random scale and spin. */
typedef struct ItemBoxStepFn {
    int thisDelta;
    int vtblOffset;
    void (*fn)(void *self);
} ItemBoxStepFn;

typedef struct DebrisPiece {
    float pos[3];  /* 0x00 */
    float vel[3];  /* 0x0C */
    float accel;   /* 0x18 */
    float life;    /* 0x1C */
    float scale;   /* 0x20 */
    float spinA;   /* 0x24 */
    float spinB;   /* 0x28 */
} DebrisPiece;

typedef struct DebrisSet {
    unsigned char active;
    unsigned char pad01[3];
    DebrisPiece pieces[15]; /* 0x04 */
} DebrisSet;

typedef struct clItemBox {
    unsigned char pad00[0x4];
    DebrisSet *debris;  /* 0x04 */
    float pos[3];       /* 0x08 */
    unsigned char pad14[0x18 - 0x14];
    ItemBoxStepFn step; /* 0x18 */
    int state;          /* 0x24 */
    unsigned char pad28[0x2C - 0x28];
    float timer;        /* 0x2C */
} clItemBox;

extern ItemBoxStepFn lbl_803F9CA8[];

extern float HSD_Randf(void);
extern float Saturate_Double(float v, float lo, float hi);

static inline void DebrisSet_Burst(DebrisSet *debris, const float *pos, float dx, float dy, float dz)
{
    unsigned int i;
    float rx;
    float ry;
    float rz;

    debris->active = 1;
    for (i = 0; i < 15; i++) {
        debris->pieces[i].pos[0] = pos[0];
        debris->pieces[i].pos[1] = pos[1];
        debris->pieces[i].pos[2] = pos[2];
        rx = 6.0f * (2.0f * (HSD_Randf() - 0.5f));
        ry = 6.0f * (2.0f * (HSD_Randf() - 0.5f));
        rz = 6.0f * (2.0f * (HSD_Randf() - 0.5f));
        if (dx * rx + dy * ry + dz * rz < 0.0f) {
            rx = -rx;
            ry = -ry;
            rz = -rz;
        }
        debris->pieces[i].vel[0] = rx + 1.5f * dx;
        debris->pieces[i].vel[1] = ry + 1.5f * dy;
        debris->pieces[i].vel[2] = rz + 1.5f * dz;
        debris->pieces[i].accel = 0.75f;
        debris->pieces[i].scale = Saturate_Double(3.0f * HSD_Randf(), 0.2f, 3.0f);
        debris->pieces[i].spinA = 360.0f * HSD_Randf();
        debris->pieces[i].spinB = 360.0f * HSD_Randf();
        debris->pieces[i].life = 0.3f;
    }
}

#pragma exceptions on
void clItemBox_TransitionToDebris(clItemBox *self, float hx, float hy, float hz)
{
    self->state = 2;
    self->step = lbl_803F9CA8[self->state];
    self->timer = 0.0f;
    DebrisSet_Burst(self->debris, self->pos, hx, hy, hz);
}
#pragma exceptions reset
