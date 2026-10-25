/* JumpDistanceMode_PredictLanding (0x80210A50): simulates a copy of the kart movement until it
 * lands and places the landing marker/camera target accordingly. */

typedef struct { float x, y, z; } Vec;
typedef struct {
    char pad00[0x8];
    void *car;
    char pad0C[0x40 - 0xC];
    float *marker;
    char pad44[0x70 - 0x44];
    char *sim;
    float launchTimer;
} JumpDistanceMode;

extern const float lbl_806DAD70;
extern const float lbl_806DAD74;
extern const float lbl_806DAD78;
extern const float lbl_806DAD7C;
extern const float lbl_806DAD80;
extern const float lbl_806DAD84;
extern const float lbl_806DAD88;
extern const float lbl_806DAD8C;
extern void *CarObject_GetKartMovementPtr(void *car);
extern void *CarObject_GetRenderObj(void *car);
extern float *KartDriver_GetKartRootMtx(void *obj);
extern void KartMovement_PhysicsStep(void *km, int flag, float a, float b, float c);
extern unsigned char Terrain_RaycastWall(Vec *from, Vec *to, Vec *hitPos, Vec *hitNormal);
extern void Vec3_Subtract(Vec *a, Vec *b, Vec *out);
extern void Vec3_Normalize(Vec *src, Vec *dst);
extern void *memcpy(void *dst, const void *src, unsigned long n);

#pragma exceptions on
void JumpDistanceMode_PredictLanding(JumpDistanceMode *self) {
    Vec land;
    Vec root;
    Vec dir;
    Vec tgt;
    Vec hitPos;
    Vec hitN;
    float *m;
    unsigned char grounded;
    int i;
    float camX;
    float camZ;
    float camY;

    memcpy(self->sim, CarObject_GetKartMovementPtr(self->car), 0x324);
    grounded = 0;
    for (i = 0; i < 0xFFFF; i++) {
        if (self->launchTimer < lbl_806DAD70) {
            self->launchTimer += lbl_806DAD74;
            if (self->launchTimer >= lbl_806DAD70) {
                *(float *)(self->sim + 0x2D4) = lbl_806DAD78;
            }
        }
        KartMovement_PhysicsStep(self->sim, 1, 0.0f, 0.0f, 0.0f);
        if (*(unsigned char *)(self->sim + 0x244) == 1) {
            grounded = 1;
        }
        if (*(unsigned char *)(self->sim + 0x2BD) == 0) {
            break;
        }
    }
    land.x = *(float *)(self->sim + 0x40);
    land.y = *(float *)(self->sim + 0x44);
    land.z = *(float *)(self->sim + 0x48);
    m = KartDriver_GetKartRootMtx(CarObject_GetRenderObj(self->car));
    root.x = m[3];
    root.y = m[7];
    root.z = m[11];
    Vec3_Subtract(&land, &root, &dir);
    dir.y = lbl_806DAD7C;
    Vec3_Normalize(&dir, &dir);
    tgt.x = lbl_806DAD80 * dir.z + land.x;
    tgt.z = lbl_806DAD80 * dir.x + land.z;
    tgt.y = lbl_806DAD84 + land.y;
    if (grounded == 1) {
        tgt.z = lbl_806DAD80 * -dir.x + land.z;
    }
    if (Terrain_RaycastWall(&root, &tgt, &hitPos, &hitN) == 1 || Terrain_RaycastWall(&land, &tgt, &hitPos, &hitN) == 1) {
        tgt.x = lbl_806DAD80 * -dir.z + land.x;
    }
    if (!grounded) {
        camX = lbl_806DAD88 * (land.x - tgt.x);
        camY = lbl_806DAD8C;
        camZ = lbl_806DAD88 * (land.z - tgt.z);
    } else {
        camX = lbl_806DAD88 * (land.x - tgt.x);
        camY = lbl_806DAD8C;
        camZ = lbl_806DAD88 * (land.z - tgt.z);
    }
    m = self->marker;
    m[2] = tgt.x;
    m[3] = tgt.y;
    m[4] = tgt.z;
    m[5] = camX;
    m[6] = camY;
    m[7] = camZ;
}
#pragma exceptions reset
