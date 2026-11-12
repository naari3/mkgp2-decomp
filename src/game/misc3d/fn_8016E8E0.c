#include "game/types/clKPCharaData.h"
#include "game/types/Vec3.h"
typedef float Mtx[3][4];

#include "game/types/KartDriver.h"

extern "C" {
extern KartDriver *GetKartSlotKartVariant(int slot);
extern Mtx *KartDriver_GetKartRootMtx(KartDriver *k);
extern void Vec3_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern float PSVECSquareMag(const Vec3 *v);
extern const float lbl_806D8BA8;
extern const float lbl_806D8BAC;
extern const float lbl_806D8BB0;
extern const float lbl_806D8BB4;
extern const float lbl_806D8BB8;
extern const float lbl_806D8BBC;
extern const float lbl_806D8BC0;
extern const float lbl_806D8BC4;
extern const float lbl_806D8BC8;
extern const float lbl_806D8BCC;

}

void clKPCharaData_NokoPata::Update() {
    KartDriver *k;
    unsigned char near = 0;
    int i;
    Vec3 v;
    float nt;
    for (i = 0; i < 8; i++) {
        k = GetKartSlotKartVariant(i);
        if (k != 0 && k->chara == 4) {
            v.x = (*KartDriver_GetKartRootMtx(k))[0][3];
            v.y = (*KartDriver_GetKartRootMtx(k))[1][3];
            v.z = (*KartDriver_GetKartRootMtx(k))[2][3];
            Vec3_Subtract(&v, (const Vec3 *)data, &v);
            if (PSVECSquareMag(&v) < lbl_806D8BB4) near = 1;
            break;
        }
    }
    switch (reserved) {
    case 0:
        if (near) {
            reserved = 1;
            frame = lbl_806D8BB8;
        } else {
            nt = frame + lbl_806D8BAC; frame = nt;
            if (nt > lbl_806D8BBC) frame = lbl_806D8BA8;
        }
        break;
    case 1:
        nt = frame + lbl_806D8BAC; frame = nt;
        if (nt > lbl_806D8BB0) {
            reserved = 2;
            frame = lbl_806D8BC0;
        }
        break;
    case 2:
        if (!near) {
            reserved = 3;
            frame = lbl_806D8BC4;
        } else {
            nt = frame + lbl_806D8BAC; frame = nt;
            if (nt > lbl_806D8BC8) frame = lbl_806D8BC0;
        }
        break;
    case 3:
        nt = frame + lbl_806D8BAC; frame = nt;
        if (nt > lbl_806D8BCC) {
            reserved = 0;
            frame = lbl_806D8BA8;
        }
        break;
    default:
        reserved = 0;
        frame = lbl_806D8BA8;
        break;
    }
}
