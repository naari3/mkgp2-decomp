/*
 * clItemBox step functions for the respawn timer and debris burst,
 * 0x8005E788..0x8005E924.
 */

typedef struct DebrisPiece {
    float pos[3]; /* 0x00 */
    float vel[3]; /* 0x0C */
    float accel; /* 0x18 */
    float life; /* 0x1C */
    unsigned char pad20[4];
    float spinA; /* 0x24 */
    float spinB; /* 0x28 */
} DebrisPiece;

typedef struct DebrisSet {
    unsigned char active;
    unsigned char pad01[3];
    DebrisPiece pieces[15];
} DebrisSet;

typedef struct ItemBoxStep {
    unsigned char pad00[4];
    DebrisSet *debris; /* 0x04 */
    unsigned char pad08[0x14 - 0x08];
    float field14;
    unsigned char pad18[4];
    float field1C;
    unsigned char pad20[4];
    int field24;
    float field28;
    float field2C;
    float field30;
} ItemBoxStep;

extern const float lbl_806D29A8;
extern const float lbl_806D29AC;
extern const float lbl_806D29B0;
extern const float lbl_806D29B4;
extern const float lbl_806D29B8;
extern const float lbl_806D29BC;
extern const float lbl_806D29C0;
extern const float lbl_806D29E8;

void fn_8005E788(ItemBoxStep *box) {
    box->field1C = lbl_806D29A8;
}

int fn_8005E794(ItemBoxStep *box) {
    box->field2C += (1.0f / 180.0f);
    if (box->field2C < 1.0f) {
        box->field2C = 1.0f;
        return 3;
    }
    box->field14 = lbl_806D29A8;
    box->field28 = lbl_806D29A8;
    box->field2C = lbl_806D29A8;
    box->field30 = lbl_806D29A8;
    box->field24 = 0;
    return 0;
}

static inline unsigned char DebrisSet_Update(DebrisSet *set) {
    unsigned char alive;
    int count;
    int i;

    if (set->active == 0) {
        return 0;
    }
    count = 0;
    for (i = 0; i < 15; i++) {
        set->pieces[i].life -= (1.0f / 60.0f);
        if (set->pieces[i].life < 0.0f) {
            alive = 0;
        } else {
            set->pieces[i].accel -= 0.11f;
            if (set->pieces[i].accel < -0.75f) {
                set->pieces[i].accel = -0.75f;
            }
            alive = 1;
            set->pieces[i].vel[1] += set->pieces[i].accel;
            set->pieces[i].pos[0] += set->pieces[i].vel[0];
            set->pieces[i].pos[1] += set->pieces[i].vel[1];
            set->pieces[i].pos[2] += set->pieces[i].vel[2];
            set->pieces[i].vel[0] *= 0.999f;
            set->pieces[i].vel[1] *= 0.999f;
            set->pieces[i].vel[2] *= 0.999f;
            set->pieces[i].spinA += 0.10471976f;
            set->pieces[i].spinB += 0.10471976f;
        }
        if (alive == 1) {
            count++;
        }
    }
    if (count <= 0) {
        set->active = 0;
        return 0;
    }
    return 1;
}

int fn_8005E7E4(ItemBoxStep *box) {
    return (DebrisSet_Update(box->debris) == 0) + 2;
}
