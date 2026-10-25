typedef struct Vec3 { float x, y, z; } Vec3;

extern signed char ItemObject_GetGroundTypeAt(Vec3 *pos, float *outY, int a);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern float BuildOrientationFromYaw(float a);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern const float lbl_806D6A74;
extern const float lbl_806D6A78;
extern const float lbl_806D6A68;
extern const float lbl_806D6A7C;
extern const float lbl_806D6A80;
extern const float lbl_806D6A6C;

void fn_80115474(unsigned char *self, unsigned char *ctx)
{
    Vec3 pos;
    float groundY;
    float h;

    switch ((signed char)self[0xC9]) {
    case 0:
        self[0xC9]++;
    case 1:
        *(float *)(self + 0xBC) += lbl_806D6A74;
        pos = *(Vec3 *)(self + 0xA0);
        if (ItemObject_GetGroundTypeAt(&pos, &groundY, 0)) {
            if (*(float *)(self + 0xA4) - lbl_806D6A78 * *(float *)(self + 0xC4) < groundY) {
                *(float *)(self + 0xA4) = groundY + lbl_806D6A78 * *(float *)(self + 0xC4);
                GetSpawnPosition(self + 0xB8, lbl_806D6A68, lbl_806D6A68, lbl_806D6A68);
                *(unsigned int *)(ctx + 0x4) = 10;
                self[0xC9]++;
            }
        } else {
            self[0xC9] = 3;
        }
        break;
    case 2:
        *(float *)(self + 0xB0) = BuildOrientationFromYaw(lbl_806D6A7C + *(float *)(self + 0xB0));
        if (*(unsigned int *)(ctx + 0x4) == 0) {
            *(float *)(self + 0x2C) = *(float *)(self + 0x2C) - lbl_806D6A80;
            if (*(float *)(self + 0x2C) < lbl_806D6A68) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
                return;
            }
        }
        break;
    case 3:
        *(float *)(self + 0xBC) += lbl_806D6A74;
        *(float *)(self + 0x2C) = *(float *)(self + 0x2C) - lbl_806D6A80;
        if (*(float *)(self + 0x2C) < lbl_806D6A68) {
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
            return;
        }
        break;
    }
    Item_DecayVelocityScalar(self, lbl_806D6A6C);
}
