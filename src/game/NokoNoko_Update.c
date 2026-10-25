/* NokoNoko_Update (0x80187D2C): walks / turns / falls one NokoNoko, makes it
 * turn back on contact with another NokoNoko, the player or a wall, and keeps
 * it on the ground. */

typedef struct { float x, y, z; } Vec;

typedef struct NokoKind {
    int state;
    int model;
    int timer;
    float speed;
    float turn;
} NokoKind;

typedef struct NokoNoko {
    struct NokoNoko *next;
    int kindTable;
    int kindIndex;
    int state;
    int model;
    float frame;
    int timer;
    Vec pos;
    float yaw;
    float speed;
    float turn;
    int model2;
    float blend;
    float frame2;
} NokoNoko;

extern NokoNoko *g_nokonokoHead;
typedef struct { Vec v[4]; } Quad;

extern const Quad lbl_80377664;
extern const Quad lbl_80377694;
extern NokoKind *lbl_80495D28[];
extern Vec lbl_80677ED8;
extern const float lbl_806CFBD8;
extern float lbl_806D168C;
extern const float lbl_806D931C;
extern const float lbl_806D9320;
extern const float lbl_806D9324;
extern const float lbl_806D9328;
extern const float lbl_806D932C;
extern const float lbl_806D9330;
extern const float lbl_806D9334;
extern const float lbl_806D9338;
extern const float lbl_806D933C;
extern const float lbl_806D9340;
extern const float lbl_806D9344;
extern const float lbl_806D9348;
extern float LookupSin(float a);
extern float LookupCos(float a);
extern void PSVECAdd(Vec *a, Vec *b, Vec *out);
extern unsigned char Terrain_GetGroundHeight(Vec *pos, float *height, int a, int b);
extern unsigned char Terrain_RaycastWall(Vec *from, Vec *to, Vec *hit, Vec *normal);
extern float Vec3_Dot(Vec *a, Vec *b);
extern float Vec3_Magnitude(Vec *v);
extern void Vec3_Normalize(Vec *src, Vec *dst);
extern void Vec3_Subtract(Vec *a, Vec *b, Vec *out);

static inline void NokoNoko_SetModel(NokoNoko *n, int model) {
    if (n->model != model) {
        n->model2 = n->model;
        n->blend = lbl_806D9324;
        n->frame2 = n->frame;
    }
}

static inline void NokoNoko_TurnBack(NokoNoko *n) {
    NokoNoko_SetModel(n, 1);
    n->kindIndex = -1;
    n->state = 1;
    n->model = 1;
    n->timer = 0x78;
    n->speed = lbl_806D9324;
    n->turn = lbl_806D9334;
}

#pragma exceptions on
void NokoNoko_Update(NokoNoko *self) {
    Quad from;
    Quad to;
    Vec d;
    Vec fwd;
    Vec normal;
    float h;
    float f;
    float x0, y0, z0;
    NokoNoko *n;
    int i;
    int j;
    unsigned char hitWall;

    x0 = self->pos.x;
    y0 = self->pos.y;
    z0 = self->pos.z;
    if (self->state < 4) {
        self->yaw += self->turn;
        if (self->yaw < lbl_806D9324) {
            self->yaw += lbl_806D9328;
        }
        f = self->yaw;
        if (f >= lbl_806D9328) {
            self->yaw = f - lbl_806D9328;
        }
        self->pos.x += lbl_806CFBD8 * (self->speed * LookupSin(self->yaw));
        self->pos.y -= lbl_806D931C;
        self->pos.z += lbl_806CFBD8 * (self->speed * LookupCos(self->yaw));
        if (self->timer > 0) {
            self->timer--;
        }
        f = self->frame + lbl_806D931C;
        self->frame = f;
        if (f >= lbl_806D9320) {
            self->frame = lbl_806D9324;
        }
        if (self->timer == 0 && self->kindTable >= 0) {
            self->kindIndex++;
            if (self->kindIndex < 0) {
                self->kindIndex = 0;
            }
            if (lbl_80495D28[self->kindTable][self->kindIndex].state == -1) {
                self->kindIndex = 0;
            }
            NokoNoko_SetModel(self, lbl_80495D28[self->kindTable][self->kindIndex].model);
            self->state = lbl_80495D28[self->kindTable][self->kindIndex].state;
            self->model = lbl_80495D28[self->kindTable][self->kindIndex].model;
            self->timer = lbl_80495D28[self->kindTable][self->kindIndex].timer;
            self->speed = lbl_80495D28[self->kindTable][self->kindIndex].speed;
            self->turn = lbl_80495D28[self->kindTable][self->kindIndex].turn;
        }
        if (self->speed > lbl_806D9324) {
            for (n = g_nokonokoHead; n != 0; n = n->next) {
                if (n != self) {
                    Vec3_Subtract(&n->pos, &self->pos, &d);
                    if (Vec3_Magnitude(&d) < lbl_806D932C) {
                        Vec3_Normalize(&d, &d);
                        fwd.x = LookupSin(self->yaw);
                        fwd.y = lbl_806D9324;
                        fwd.z = LookupCos(self->yaw);
                        if (Vec3_Dot(&d, &fwd) > lbl_806D9330) {
                            NokoNoko_TurnBack(self);
                        }
                    }
                }
            }
            if (lbl_806D168C > lbl_806D9324 && (self->state == 2 || self->state == 3)) {
                Vec3_Subtract(&lbl_80677ED8, &self->pos, &d);
                if (Vec3_Magnitude(&d) < lbl_806D9338 * (lbl_806D933C + lbl_806D168C)) {
                    Vec3_Normalize(&d, &d);
                    fwd.x = LookupSin(self->yaw);
                    fwd.y = lbl_806D9324;
                    fwd.z = LookupCos(self->yaw);
                    if (Vec3_Dot(&d, &fwd) > lbl_806D9330) {
                        NokoNoko_TurnBack(self);
                    }
                }
            }
        }
    } else if (self->state == 4) {
        self->pos.x -= lbl_806D9340 * LookupSin(self->yaw);
        self->pos.y += lbl_806D9338 - lbl_806D9344 * self->frame;
        self->pos.z -= lbl_806D9340 * LookupCos(self->yaw);
        f = self->frame + lbl_806D931C;
        self->frame = f;
        if (f >= lbl_806D9320) {
            self->state = 5;
            self->model = -1;
        }
    }
    from = lbl_80377664;
    from.v[0].x = lbl_806D933C + x0;
    from.v[0].y = y0;
    from.v[0].z = z0;
    from.v[1].x = x0 - lbl_806D933C;
    from.v[1].y = y0;
    from.v[1].z = z0;
    from.v[2].x = x0;
    from.v[2].y = y0;
    from.v[2].z = lbl_806D933C + z0;
    from.v[3].x = x0;
    from.v[3].y = y0;
    from.v[3].z = z0 - lbl_806D933C;
    to = lbl_80377694;
    to.v[0].x = lbl_806D933C + self->pos.x;
    to.v[0].y = self->pos.y;
    to.v[0].z = self->pos.z;
    to.v[1].x = self->pos.x - lbl_806D933C;
    to.v[1].y = self->pos.y;
    to.v[1].z = self->pos.z;
    to.v[2].x = self->pos.x;
    to.v[2].y = self->pos.y;
    to.v[2].z = lbl_806D933C + self->pos.z;
    to.v[3].x = self->pos.x;
    to.v[3].y = self->pos.y;
    to.v[3].z = self->pos.z - lbl_806D933C;
    hitWall = 0;
    for (i = 0; i < 4; i++) {
        if (Terrain_RaycastWall(&from.v[i], &to.v[i], &fwd, &normal)) {
            Vec3_Subtract(&fwd, &to.v[i], &d);
            d.y = lbl_806D9324;
            PSVECAdd(&self->pos, &d, &self->pos);
            for (j = i; j < 4; j++) {
                PSVECAdd(&to.v[j], &d, &to.v[j]);
            }
            hitWall = 1;
        }
    }
    if (hitWall && self->state < 4) {
        NokoNoko_TurnBack(self);
    }
    if (Terrain_GetGroundHeight(&self->pos, &h, 0, 0) && self->pos.y < h) {
        self->pos.y = h;
    }
    if (self->model2 != -1) {
        self->blend += lbl_806D9348;
        if (self->blend >= lbl_806D931C) {
            self->model2 = -1;
            self->blend = lbl_806D9324;
            self->frame2 = lbl_806D9324;
        }
    }
}
#pragma exceptions reset
