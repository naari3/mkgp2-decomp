typedef struct Vec3 { float x, y, z; } Vec3;

extern signed char ItemObject_GetGroundTypeAt(Vec3 *pos, float *outY, int a);
extern void *KartDriver_GetKartRootMtx(void *kart);
extern void Mtx44_GetTranslation_RowMajor(void *dst, void *src);
extern void Vec3_Subtract_DestFirst(void *dst, void *a, void *b);
extern void Vec3_Copy(void *dst, void *src);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern float BuildOrientationFromYaw(float a);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern const float lbl_806D6788;
extern const float lbl_806D679C;
extern const float lbl_806D67BC;
extern const float lbl_806D67AC;
extern const float lbl_806D678C;

void fn_8010AA54(unsigned char *self, unsigned char *ctx)
{
    Vec3 kpos;
    Vec3 root;
    Vec3 pos0;
    float groundY;
    Vec3 pos;

    switch ((signed char)self[0xC9]) {
    case 0:
        pos0 = *(Vec3 *)(self + 0xA0);
        ItemObject_GetGroundTypeAt(&pos0, (float *)(ctx + 0x14), 0);
        if (*(char *)(self + 0xCB) != 5) {
            *(unsigned int *)(ctx + 0x4) = 10;
        } else {
            *(unsigned int *)(ctx + 0x4) = 0;
        }
        if (*(char *)(self + 0xCB) == 5) {
            *(float *)(self + 0xBC) = lbl_806D6788;
        }
        if (*(void **)(ctx + 0x9C)) {
            Mtx44_GetTranslation_RowMajor(&kpos, KartDriver_GetKartRootMtx(*(void **)(ctx + 0x9C)));
            Vec3_Subtract_DestFirst(ctx + 0x34, self + 0xA0, &kpos);
            Vec3_Copy(ctx + 0x40, self + 0xB8);
            GetSpawnPosition(self + 0xB8, lbl_806D6788, lbl_806D6788, lbl_806D6788);
        }
        self[0xC9]++;
    case 1:
        break;
    }
    if (*(unsigned int *)(ctx + 0x4) == 0) {
        *(float *)(self + 0x2C) = *(float *)(self + 0x2C) - lbl_806D679C;
        if (*(float *)(self + 0x2C) < lbl_806D6788) {
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
            return;
        }
    }
    if (*(void **)(ctx + 0x9C) == 0) {
        if (*(char *)(self + 0xCB) != 5) {
            *(float *)(self + 0xBC) += lbl_806D67BC;
        }
        pos = *(Vec3 *)(self + 0xA0);
        if (ItemObject_GetGroundTypeAt(&pos, &groundY, 0)) {
            *(float *)(self + 0xA4) = *(float *)(self + 0xA4) + (groundY - *(float *)(ctx + 0x14));
            *(float *)(ctx + 0x14) = groundY;
        }
    } else {
        *(float *)(ctx + 0x44) += lbl_806D67BC;
        Vec3_Add_DestFirst(ctx + 0x34, ctx + 0x34, ctx + 0x40);
        Mtx44_GetTranslation_RowMajor(&root, KartDriver_GetKartRootMtx(*(void **)(ctx + 0x9C)));
        Vec3_Add_DestFirst(self + 0xA0, &root, ctx + 0x34);
    }
    switch ((signed char)self[0xCB]) {
    case 1:
        *(float *)(self + 0xAC) = BuildOrientationFromYaw(*(float *)(self + 0xAC) - lbl_806D67AC);
        break;
    case 4:
        *(float *)(self + 0xAC) = BuildOrientationFromYaw(*(float *)(self + 0xAC) - lbl_806D67AC);
        break;
    case 7:
        *(float *)(self + 0xAC) = BuildOrientationFromYaw(*(float *)(self + 0xAC) - lbl_806D67AC);
        break;
    case 9:
        *(float *)(self + 0xAC) = BuildOrientationFromYaw(lbl_806D67AC + *(float *)(self + 0xAC));
        break;
    }
    Item_DecayVelocityScalar(self, lbl_806D678C);
}
