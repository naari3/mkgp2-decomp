#include "game/types/c_region.h"
C_REGION_BEGIN
/* === extracted from auto_TornadoEffect_InitDe_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* TornadoEffect_InitDetails @ 0x80056CB0 (size 0x210). The spawn position
 * comes in f1..f3, passed straight through from TornadoEffect_Ctor. */

extern void *DrawEffect_SetU32CC(void *eff, int v);
extern void Object_SetColorAlphaOnly(void *obj, int idx, float a);
extern void Object_SetJObjScaleXYZ(void *obj, float x, float y, float z);
extern const float lbl_806D28D4;
extern const float lbl_806D28D8;
extern const float lbl_806D28DC;
extern unsigned int TornadoEffect_InitDetails_rodata_802EDC54[];
extern unsigned int lbl_802EDC60[];

C_REGION_END
#pragma cplusplus on
struct TENormal3D {
    char data[0x5C];
    TENormal3D(void *desc, int arg);
};

#pragma exceptions on
extern "C" void TornadoEffect_InitDetails(void *self, int arg, float x, float y, float z)
{
    TornadoSpawnPos pos = *(const TornadoSpawnPos *)TornadoEffect_InitDetails_rodata_802EDC54;
    pos.x = x;
    pos.y = y;
    pos.z = z;
    TE_PTR(self, 0x10) = DrawEffect_SpawnWithDescriptor(1, pos);
    DrawEffect_SetU32CC(TE_PTR(self, 0x10), arg);
    TE_F(self, 0x5C) = lbl_806D28C8;
    TE_F(self, 0x60) = lbl_806D28C8;
    TE_F(self, 0x64) = lbl_806D28C8;
    TE_F(self, 0x68) = lbl_806D28C8;
    TE_F(self, 0x6C) = lbl_806D28C8;
    TE_F(self, 0x70) = lbl_806D28C8;
    TE_F(self, 0x74) = lbl_806D28C8;
    TE_F(self, 0x78) = lbl_806D28C8;
    TE_F(self, 0x7C) = lbl_806D28C8;
    TE_F(self, 0x80) = lbl_806D28C8;
    TE_F(self, 0x84) = lbl_806D28C8;
    TE_F(self, 0x88) = lbl_806D28C8;
    TE_F(self, 0x8C) = lbl_806D28C8;
    TE_F(self, 0x90) = lbl_806D28C8;
    TE_F(self, 0x94) = lbl_806D28C8;
    TE_F(self, 0x98) = lbl_806D28C8;
    TE_F(self, 0x9C) = lbl_806D28C8;
    TE_F(self, 0xA0) = lbl_806D28C8;
    TE_F(self, 0xA4) = lbl_806D28C8;
    TE_F(self, 0xA4) = lbl_806D28CC;
    TE_F(self, 0x90) = lbl_806D28CC;
    TE_F(self, 0x7C) = lbl_806D28CC;
    TE_F(self, 0x68) = lbl_806D28CC;
    TE_F(self, 0xAC) = lbl_806D28C8;
    TE_F(self, 0xB0) = lbl_806D28C8;
    TE_U8(self, 0xB4) = 0;
    TE_F(self, 0xB8) = lbl_806D28C8;
    TE_F(self, 0xBC) = lbl_806D28C8;
    TE_U8(self, 0xC0) = 0;
    TE_F(self, 0xC4) = lbl_806D28C8;
    TE_S32(self, 0xC8) = 0;
    TE_S32(self, 0xCC) = 0;
    TE_U8(self, 0xD0) = 0;
    TE_U8(self, 0xD1) = 0;
    TE_U8(self, 0xD2) = 0;
    TE_S32(self, 0x13C) = 0;
    TE_S32(self, 0xD4) = 0;
    TE_F(self, 0xEC) = lbl_806D28CC;
    TE_F(self, 0xF0) = lbl_806D28CC;
    TE_F(self, 0xF4) = lbl_806D28CC;
    TE_F(self, 0xE0) = lbl_806D28CC;
    TE_F(self, 0xE4) = lbl_806D28CC;
    TE_F(self, 0xE8) = lbl_806D28CC;
    TE_U8(self, 0xF8) = 0;
    TE_F(self, 0xFC) = lbl_806D28C8;
    TE_S32(self, 0x104) = 0;
    TE_F(self, 0x10C) = lbl_806D28CC;
    TE_F(self, 0x110) = lbl_806D28D0;
    TE_F(self, 0x118) = lbl_806D28C8;
    TE_F(self, 0x114) = lbl_806D28C8;
    TE_S32(self, 0x100) = -1;
    TE_F(self, 0x11C) = lbl_806D28C8;
    TE_F(self, 0x120) = lbl_806D28C8;
    TE_S32(self, 0x124) = 0;
    TE_S32(self, 0x128) = 0;
    TE_U8(self, 0x12C) = 0;
    TE_S32(self, 0x130) = 0;
    TE_S32(self, 0x134) = 0;
    TE_S32(self, 0x138) = 0;
    TE_S32(self, 0x140) = 0;
    TE_S32(self, 0x144) = 0;
    TE_S32(self, 0x148) = 0;
    TE_S32(self, 0x14C) = -1;
    TE_S32(self, 0x150) = -1;
    TE_PTR(self, 0xA8) = new TENormal3D(lbl_802EDC60, 1);
    if (TE_U8(self, 0x8) == 1) {
        Object_SetColorAlphaOnly(TE_PTR(self, 0xA8), 0, lbl_806D28D4);
    } else {
        Object_SetColorAlphaOnly(TE_PTR(self, 0xA8), 0, lbl_806D28D8);
    }
    Object_SetJObjScaleXYZ(TE_PTR(self, 0xA8), lbl_806D28CC, lbl_806D28DC, lbl_806D28CC);
}
#pragma exceptions reset
#pragma cplusplus reset
