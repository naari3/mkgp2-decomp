#include "game/types/c_region.h"
C_REGION_BEGIN
/* TornadoEffect_Ctor @ 0x80056EC0 (size 0x5C): C++ ctor. The three Vec3
 * members have an empty dtor (dtor_80036E40), which gives the extab its
 * destroy-member actions. */

extern const float lbl_806D28E0;

C_REGION_END
#pragma cplusplus on
struct TEVec3 {
    float x, y, z;
    TEVec3() {}
    ~TEVec3() {}
};

struct TornadoEffect {
    unsigned char x0;
    int x4;
    unsigned char x8;
    int xC;
    int x10;
    int x14;
    float x18;
    char pad1C[0x5C - 0x1C];
    TEVec3 v5C;
    char pad68[0xA8 - 0x68];
    int xA8;
    char padAC[0xE0 - 0xAC];
    TEVec3 vE0;
    TEVec3 vEC;
    TornadoEffect(unsigned char a, int b, int c, unsigned char d, float x, float y, float z);
};

#pragma exceptions on
TornadoEffect::TornadoEffect(unsigned char a, int b, int c, unsigned char d, float x, float y, float z)
{
    x0 = a;
    x4 = c;
    x8 = d;
    xC = b;
    x10 = 0;
    x14 = 0;
    x18 = lbl_806D28E0;
    xA8 = 0;
    TornadoEffect_InitDetails(this, b, x, y, z);
}
#pragma exceptions reset
#pragma cplusplus reset
