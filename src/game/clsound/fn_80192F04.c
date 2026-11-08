/* 0x80192F04..0x801933D0: listener-relative volume/pan, the per-voice attribute
 * refresh, the weather variant picker and the fog/listener basis update. The
 * unit owns the listener vectors (.data 0x80495F20..0x80495F48). */
#define lbl_80495F20 lbl_80495F20_hdr
#include "game/clsound_spatial_private.h"
#undef lbl_80495F20

typedef struct FogEye {
    ClSoundVec pos;
    float w;
} FogEye;

ClSoundVec lbl_80495F20 = {0.0f, 0.0f, 0.0f};
ClSoundVec lbl_80495F2C = {0.0f, 0.0f, 0.0f};
FogEye lbl_80495F38 = {{0.0f, 0.0f, 0.0f}, 0.0f};

int fn_80192F04(unsigned int id, const ClSoundVec* position, unsigned char* volume, unsigned char* pan, unsigned char* surround) {
    ClSoundVec delta;
    float near_distance, far_distance, distance;
    if (!ClSound_Initialized) return 0;
    if (!position) return 0;
    id &= ~0x78000000;
    if (id >= 490) return 0;
    near_distance = lbl_80379554[id].near_distance;
    far_distance = lbl_80379554[id].far_distance;
    Vec3_Subtract(position, &lbl_80495F38.pos, &delta);
    distance = Vec3_Magnitude(&delta);
    if (distance >= far_distance) {
        if (volume) *volume = 0;
        if (pan) *pan = 64;
        if (surround) *surround = 64;
    } else {
        if (volume) {
            if (distance <= near_distance) *volume = 127;
            else *volume = (int)(lbl_806D9514 - lbl_806D9514 * ((distance-near_distance)/(far_distance-near_distance)));
        }
        if (pan) {
            distance = Vec3_Dot(&delta, &lbl_80495F20);
            if (distance >= near_distance) *pan = 0;
            else if (distance <= -near_distance) *pan = 127;
            else *pan = (int)(lbl_806D9518 - lbl_806D951C*(distance/near_distance));
        }
        if (surround) {
            distance = Vec3_Dot(&delta, &lbl_80495F2C);
            if (distance >= near_distance) *surround = 127;
            else if (distance <= -near_distance) *surround = 0;
            else *surround = (int)(lbl_806D9518 + lbl_806D951C*(distance/near_distance));
        }
    }
    return 1;
}

extern unsigned char lbl_806D16C0;

#pragma exceptions off
void fn_80193134(unsigned char v) {
    int i;
    if (lbl_806D16C0 == v) {
        return;
    }
    lbl_806D16C0 = v;
    for (i = 0; i < 32; i++) {
        if (lbl_80678378[i].id != -1) {
            lbl_80678378[i].flags |= (lbl_80379554[lbl_80678378[i].id & ~0x78000000].attributes & 2) ? 0 : 0x200;
        }
    }
}
#pragma exceptions reset

/* WeatherSystem_PickVariant: forced id -1 consults the card flag and the
 * player data, 0..4 pick clear/cloudy/overcast/rain/thunder. */
extern unsigned char Sci2Card_GetByteFlag1224(void);
extern unsigned char g_playerData[0x1DC];

#pragma exceptions on
unsigned char WeatherSystem_PickVariant(int forcedId) {
    if (forcedId < 0) {
        if ((Sci2Card_GetByteFlag1224() & 0xFF) == 0) {
            return 0x5F;
        }
        forcedId = g_playerData[0xC];
    }
    switch (forcedId) {
    case 0:
        return 0x00;
    case 1:
        return 0x50;
    case 3:
        return 0x73;
    case 4:
        return 0x7F;
    case 2:
    default:
        return 0x5F;
    }
}
#pragma exceptions reset

#pragma exceptions off
int fn_801932F8(void) {
    return 90;
}
#pragma exceptions reset

extern void *GetCourseScene3D(void);
extern float *CObj_GetViewMatrix_Cached(void *cobj);
extern void CObj_LoadProjMatrix(void *cobj, ClSoundVec *pos);
void Fog_UpdateFromCourseScene3D(void) {
    if (GetCourseScene3D()) {
        float *m = CObj_GetViewMatrix_Cached(GetCourseScene3D());
        lbl_80495F20.x = m[0];
        lbl_80495F20.y = m[4];
        lbl_80495F20.z = m[8];
        lbl_80495F2C.x = m[2];
        lbl_80495F2C.y = m[6];
        lbl_80495F2C.z = m[10];
        CObj_LoadProjMatrix(GetCourseScene3D(), &lbl_80495F38.pos);
        lbl_80495F38.pos.x += 50.0f * lbl_80495F2C.x;
        lbl_80495F38.pos.y += 50.0f * lbl_80495F2C.y;
        lbl_80495F38.pos.z += 50.0f * lbl_80495F2C.z;
    }
}
